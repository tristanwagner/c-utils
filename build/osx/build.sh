#!/bin/bash
set -x
# TODO: only support osx for now
proj_name=utils
proj_root_dir=$(pwd)
file_dir=`dirname "$0"`
l_bin_path="$proj_root_dir/$file_dir/bin"
l_bin_f_path="$l_bin_path/$proj_name"

rm -rf $l_bin_path
mkdir $l_bin_path

flags=(
  -std=c99 -x objective-c -O0 -w
)

# Include directories
inc=(
  -I ./lib
)

# Source files
src=(
  ./src/*.c
)

# Build
gcc ${src[*]} ${flags[*]} ${inc[*]} -o ${l_bin_f_path}
