#!/usr/bin/env python3

import os

def to_bytes(s):
  return ["0x%02X" % c for c in s]

os.system("nasm -f bin bootcode.asm -o bootcode.bin")

with open("bootcode.bin", "rb") as f:
  boot_jump = f.read(3)
  f.seek(62)
  boot_code = f.read(510 - 62)

assert boot_jump == b"\xEB\x3C\x90"

print("// This file is automatically generated by firmware/bootcode/bake.py.")
print("// Edit that file instead!")
print()
print("#ifndef __TPC_BOOT_CODE_HPP")
print("#define __TPC_BOOT_CODE_HPP")
print()
print("#define TPC_BOOT_CODE_LEN %d" % len(boot_code))
print()
print("#define TPC_BOOT_CODE { \\")
boot_code_bytes = to_bytes(boot_code)
while len(boot_code_bytes) > 16:
  print("  %s, \\" % ",".join(boot_code_bytes[:16]))
  boot_code_bytes = boot_code_bytes[16:]
print("  %s \\" % ",".join(boot_code_bytes))
print("}")
print()
print("#endif")
