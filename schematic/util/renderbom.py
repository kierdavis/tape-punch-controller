import contextlib
import sys
import subprocess

ATTRIBS = [
  "device",
  "footprint",
  "value",
  "x-dielectric",
  "x-led-colour",
  "x-led-current",
  "x-led-voltage",
  "x-voltage-rating",
  "x-power-rating",
]

IC_SUMMARIES = {
  "ATXMEGA192C3": "Atmel AVR microcontroller",
  "TSR_1-24150": "15V switched-mode regulator",
  "TSR_1-2433": "3.3V switched-mode regulator",
  "USBLC6-2": "ESD protection IC",
}

def help(file):
  print("usage:", file=file)
  print("  renderbom.py file1.sch file2.sch > bom.tex", file=file)

class Quantity(object):
  AMPERE = "\\ampere"
  FARAD = "\\farad"
  OHM = "\\ohm"
  VOLT = "\\volt"
  WATT = "\\watt"

  PREFIXES = [
    ("G", "\\giga", 1e9),
    ("M", "\\mega", 1e6),
    ("k", "\\kilo", 1e3),
    ("m", "\\milli", 1e-3),
    ("u", "\\micro", 1e-6),
    ("n", "\\nano", 1e-9),
    ("p", "\\pico", 1e-12),
  ]

  @staticmethod
  def split_prefix(text):
    for prefix, tex_prefix, multiplier in Quantity.PREFIXES:
      if text.endswith(prefix):
        return text[:-1], tex_prefix, multiplier
    return text, "", 1.0

  def __init__(self, text, tex_unit):
    if text[0].isdigit():
      text, tex_prefix, multiplier = Quantity.split_prefix(text)
      self.text = text
      self.value = float(text) * multiplier
      self.tex_unit = tex_prefix + tex_unit
    else:
      self.text = text
      self.value = None
      self.tex_unit = None

  def __lt__(self, other):
    if self.value is None: return False
    if other.value is None: return True
    return self.value < other.value

  def __str__(self):
    if self.tex_unit is None:
      return self.text
    else:
      return "\\SI{%s}{%s}" % (self.text, self.tex_unit)

@contextlib.contextmanager
def run_gnetlist(filenames):
  options = [
    # Send output to stdout.
    "-o", "-",
    # Set output format to 'bom'.
    "-g", "bom",
    # Specify which attributes to include in the output.
    "-O", "attribs=%s" % ",".join(ATTRIBS),
  ]
  command = ["gnetlist"] + options + ["--"] + filenames
  child_process = subprocess.Popen(command, stdout=subprocess.PIPE)
  yield child_process
  child_process.wait()

def parse_bom(stream):
  header_row = stream.readline().decode("utf8").rstrip("\r\n").split("\t")
  for line in stream:
    row = line.decode("utf8").rstrip("\r\n").split("\t")
    yield dict(zip(header_row, row))

def annotate(components):
  for component in components:
    device = component["device"]
    footprint = component["footprint"]
    if device == "TESTPOINT":
      continue # skip
    elif device == "RESISTOR":
      resistance = Quantity(component["value"], Quantity.OHM)
      power_rating = Quantity(component["x-power-rating"], Quantity.WATT)
      component["summary"] = "Resistor"
      component["specification"] = "%s, %s" % (resistance, power_rating)
      component["sortkey"] = (10, resistance, power_rating, footprint)
    elif device == "VARIABLE_RESISTOR":
      resistance = Quantity(component["value"], Quantity.OHM)
      component["summary"] = "Variable resistor"
      component["specification"] = "%s" % resistance
      component["sortkey"] = (12, resistance, footprint)
    elif device == "CAPACITOR":
      capacitance = Quantity(component["value"], Quantity.FARAD)
      voltage_rating = Quantity(component["x-voltage-rating"], Quantity.VOLT)
      dielectric = component["x-dielectric"]
      component["summary"] = "Capacitor"
      component["specification"] = "%s, %s, %s" % (capacitance, voltage_rating, dielectric)
      component["sortkey"] = (20, capacitance, voltage_rating, dielectric, footprint)
    elif device == "LED":
      colour = component["x-led-colour"].lower()
      voltage = Quantity(component["x-led-voltage"], Quantity.VOLT)
      current = Quantity(component["x-led-current"], Quantity.AMPERE)
      component["summary"] = "LED"
      component["specification"] = "%s, %s, %s" % (colour, voltage, current)
      component["sortkey"] = (100, colour, voltage, current, footprint)
    elif device == "SWITCH_PUSHBUTTON_NO":
      component["summary"] = "Push button"
      component["specification"] = "SPST"
      component["sortkey"] = (1000, component["specification"], footprint)
    elif device == "FUSE":
      current_rating = Quantity(component["value"], Quantity.AMPERE)
      component["summary"] = "Fuse"
      component["specification"] = current_rating
      component["sortkey"] = (80, current_rating, footprint)
    elif device == "NMOS_TRANSISTOR":
      component["summary"] = "N-channel MOSFET"
      component["specification"] = component["value"]
      component["sortkey"] = (300, component["specification"], footprint)
    elif device in IC_SUMMARIES:
      component["summary"] = IC_SUMMARIES[device]
      component["specification"] = device.replace("_", " ")
      component["sortkey"] = (400, component["specification"], footprint)
    elif device == "OPAMP":
      component["summary"] = "Operational amplifier"
      component["specification"] = component["value"]
      component["sortkey"] = (400, component["specification"], footprint)
    elif device == "USB_CON" and footprint == "USB_B":
      component["summary"] = "Connector"
      component["specification"] = component["footprint"] = "USB, type B"
      component["footprint"] = "unknown"
      component["sortkey"] = (1600, component["specification"], footprint)
    elif device == "DB25":
      component["summary"] = "Connector"
      component["specification"] = "DB-25"
      component["footprint"] = "unknown"
      component["sortkey"] = (1600, component["specification"], footprint)
    elif device.startswith("CONNECTOR_") and footprint.startswith("JUMPER"):
      pins = footprint[6:]
      component["summary"] = "Connector"
      component["specification"] = ", ".join((
        pins + " pins",
        "1 row",
      ))
      component["footprint"] = "pin header"
      component["sortkey"] = (1500, int(pins), 1, footprint)
    elif device.startswith("CONNECTOR_") and footprint.startswith("HEADER"):
      pins, rows = footprint[6:].split("_")
      component["summary"] = "Connector"
      component["specification"] = ", ".join((
        pins + " pins",
        rows + " rows",
      ))
      component["footprint"] = "pin header"
      component["sortkey"] = (1500, int(pins), int(rows), footprint)
    else:
      print("unmatched component:", file=sys.stderr)
      print(component, file=sys.stderr)
      sys.exit(0)
    if component["footprint"].startswith("TQFP"):
      basefootprint, size = component["footprint"].split("_")
      component["footprint"] = "%s (%smm)" % (basefootprint, size)
    if "sortkey" not in component:
      component["sortkey"] = (1000000, component["specification"], component["footprint"])
    yield component

def group(components):
  indexed = {}
  for component in components:
    key = (component["summary"], component["specification"], component["footprint"])
    if key in indexed:
      indexed[key]["refdes_list"].append(component["refdes"])
    else:
      indexed[key] = dict(component, refdes_list=[component["refdes"]])
  return indexed.values()

def main():
  if len(sys.argv) < 2:
    help(sys.stderr)
    sys.exit(2)

  filenames = sys.argv[1:]

  with run_gnetlist(filenames) as child_process:
    components = parse_bom(child_process.stdout)
    components = annotate(components)
    components = group(components)
    components = sorted(components, key=lambda c: c["sortkey"])

  print("{\\small")
  print("\\begin{tabular}{lllr}")
  print("  \\toprule")
  print("  Summary & Specification & Package & Quantity \\\\")
  print("  \\midrule")
  for component in components:
    if not component.get("skip"):
      print("  %s & %s & %s & %d \\\\" % (component["summary"], component["specification"], component["footprint"], len(component["refdes_list"])))
  print("  \\bottomrule")
  print("\\end{tabular}")
  print("}")

if __name__ == "__main__":
  main()
