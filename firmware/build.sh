#!/bin/sh

set -o errexit  # Exit script if any command fails...
set -o pipefail # ...include commands within a pipeline.
set -o nounset  # Exit script if an undefined variable is used.

self="$(realpath $0)"
firmware_dir="$(dirname $self)"
components_dir="$firmware_dir/components"
build_dir="$firmware_dir/build"

device="${DEVICE:-}"
if [ -z "$device" ]; then
  device="atmega644p"
  echo "Note: using the default value of DEVICE, which is $device."
  echo "If you want to change this (or squelch this warning), set the DEVICE environment variable."
  echo
fi

f_cpu="${F_CPU:-}"
if [ -z "$f_cpu" ]; then
  f_cpu="12000000"
  echo "Note: using the default value of F_CPU (CPU frequency in Hz), which is $f_cpu."
  echo "If you want to change this (or squelch this warning), set the F_CPU environment variable."
  echo
fi

cflags="-Wall"                     # Enable all warnings
cflags="$cflags -O2"               # Enable optimisations
cflags="$cflags -mmcu=$device"     # Inform the compiler of the target device
cflags="$cflags -DF_CPU=$f_cpu"    # Inform library code of the CPU frequency
cflags="$cflags -I$components_dir" # Add components directory to include path
cflags="$cflags ${CFLAGS:-}"       # Append user's CFLAGS variable if present

ldflags="-Wall"                    # Enable all warnings
ldflags="$ldflags -O2"             # Enable optimisations
ldflags="$ldflags -mmcu=$device"   # Inform the compiler of the target device
ldflags="$ldflags ${LDFLAGS:-}"    # Append user's LDFLAGS variable if present

# Create a directory for build files / empty it if it already exists.
mkdir -p "$build_dir"
rm -rf $build_dir/*

# Compile each of the component modules.
for src_file in $(find "$components_dir" -name '*.cpp'); do
  obj_file="$build_dir/$(basename $src_file | sed s/.cpp/.o/)"
  echo "Compiling $(realpath --relative-base=$PWD $src_file)"
  echo "       to $(realpath --relative-base=$PWD $obj_file)"
  echo
  avr-g++ $cflags -c -o "$obj_file" "$src_file"
done

# Compile main file.
main_src="$firmware_dir/main.cpp"
main_obj="$build_dir/main.o"
echo "Compiling $(realpath --relative-base=$PWD $main_src)"
echo "       to $(realpath --relative-base=$PWD $main_obj)"
echo
avr-g++ $cflags -c -o "$main_obj" "$main_src"

# Link.
elf_file="$build_dir/firmware.elf"
echo "Linking $(realpath --relative-base=$PWD $elf_file)"
echo
find "$build_dir" -name '*.o' | xargs avr-g++ $ldflags -o "$elf_file"

# Convert to hex.
hex_file="$build_dir/firmware.hex"
echo "Converting $(realpath --relative-base=$PWD $elf_file)"
echo "        to $(realpath --relative-base=$PWD $hex_file)"
echo
avr-objcopy -O ihex "$elf_file" "$hex_file"

echo "Done."
