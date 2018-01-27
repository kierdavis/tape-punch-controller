#!/bin/sh

set -o errexit  # Exit script if any command fails...
set -o pipefail # ...include commands within a pipeline.
set -o nounset  # Exit script if an undefined variable is used.

self="$(realpath $0)"
firmware_dir="$(dirname $self)"

platform="${PLATFORM:-}"
if [ -z "$platform" ]; then
  platform="il-matto"
  echo "Note: using the default value of PLATFORM, which is $platform."
  echo "If you want to change this (or squelch this warning), set the PLATFORM environment variable."
  echo
fi

src_dir="$firmware_dir/src"
build_dir="$firmware_dir/build/$platform"

cppflags=""  # C/C++ preprocessor flags
cxxflags=""  # C++ compiler flags
ldflags=""   # Linker flags

platform_config_file="$firmware_dir/platforms/$platform"
source "$platform_config_file"

# Specify target device and clock frequency.
cxxflags="$cxxflags -mmcu=$mcuname"
ldflags="$ldflags -mmcu=$mcuname"
cppflags="$cppflags -DF_CPU=$mcufreq"

# Specify language version.
cxxflags="$cxxflags -std=c++14 -fno-threadsafe-statics"

# Enable all warnings.
cxxflags="$cxxflags -Wall"
ldflags="$ldflags -Wall"

# Enable optimisations.
cxxflags="$cxxflags -O3 -flto"
ldflags="$ldflags -O3 -flto"

# Add source directory to include search path.
cppflags="$cppflags -I$src_dir"

# Append user's flags if present.
cppflags="$cppflags ${CPPFLAGS:-}"
cxxflags="$cxxflags ${CXXFLAGS:-}"
ldflags="$ldflags ${LDFLAGS:-}"

# Compile source files.
sources="$(find $src_dir -name '*.cpp')"
objects=""
for src_file in $sources; do
  obj_file="$build_dir/$(realpath --relative-to=$src_dir $src_file | sed s/.cpp/.o/)"
  objects="$objects $obj_file"
  mkdir -p "$(dirname "$obj_file")"
  echo "Compiling $(realpath --relative-base=$PWD $src_file)"
  echo "       to $(realpath --relative-base=$PWD $obj_file)"
  echo
  avr-g++ -c $cppflags $cxxflags -o "$obj_file" "$src_file"
done

# Link.
elf_file="$build_dir/firmware.elf"
echo "Linking $(realpath --relative-base=$PWD $elf_file)"
echo
avr-g++ $ldflags -o "$elf_file" $objects

# Convert to hex.
hex_file="$build_dir/firmware.hex"
echo "Converting $(realpath --relative-base=$PWD $elf_file)"
echo "        to $(realpath --relative-base=$PWD $hex_file)"
echo
avr-objcopy -O ihex "$elf_file" "$hex_file"

# Print stats.
avr-size "$(realpath --relative-base=$PWD $elf_file)" "$(realpath --relative-base=$PWD $hex_file)"

echo
echo "Done."
