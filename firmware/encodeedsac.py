import sys
import re

letters = {
  "A": 0b01100,
  "B": 0b01101,
  "C": 0b01110,
  "D": 0b00011,
  "E": 0b10011,
  "F": 0b00001,
  "G": 0b01011,
  "H": 0b00101,
  "I": 0b11000,
  "J": 0b11010,
  "K": 0b11110,
  "L": 0b01001,
  "M": 0b00111,
  "N": 0b00110,
  "O": 0b11001,
  "P": 0b10000,
  "Q": 0b10001,
  "R": 0b10100,
  "S": 0b11100,
  "T": 0b10101,
  "U": 0b10111,
  "V": 0b01111,
  "W": 0b10010,
  "X": 0b01010,
  "Y": 0b10110,
  "Z": 0b11101,
}

def put(row):
  print "  0x%02x," % row

with open(sys.argv[1], "r") as f:
  content = f.read()

content = re.sub("\\[.*?\\]", "", content)

for char in content:
  char = char.upper()
  if char in letters:
    put(letters[char])
  elif char.isdigit():
    put(0b10000 + (ord(char) - ord("0")))
  elif char == "@": # theta
    put(0b00010)
  elif char == "!": # phi
    put(0b00100)
  elif char == "&": # delta
    put(0b01000)
  elif char == "#": # pi
    put(0b11011)
  elif char == "+":
    put(0b00101)
  elif char == "-":
    put(0b00110)
  elif char == ".":
    put(0b00000)
  elif char == "*":
    put(0b11111)
