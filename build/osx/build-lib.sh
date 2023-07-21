#!/bin/bash
set -x
# TODO: only support osx for now
proj_name=utils
start_path=$(pwd)
file_dir=`dirname "$0"`
proj_root_dir="$start_path/$file_dir/../.."

rm -f $proj_root_dir/*.o
rm -f $proj_root_dir/*.a

cd $proj_root_dir

flags=(
  -g -O -c
)
# -Os enables size optimization.
# -s strips unnecessary symbols.

# Include directories
inc=(
  -I $proj_root_dir/lib
)

# Source files
src=(
  $proj_root_dir/src/*.c
)

# Build
gcc ${src[*]} ${flags[*]} ${inc[*]}

ar rcs lib${proj_name}.a ./*.o

cd $start_path
