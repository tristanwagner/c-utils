#!/bin/bash
# TODO: only support osx for now
proj_name=utils
proj_root_dir=$(pwd)

flags=(
  -std=c99 -x objective-c -O0 -w
)

# Include directories
inc=(
  -I ./lib
)

# Source files
src=(
  ./utils.c
  ./mem.c
  ./test.c
)

# Build
gcc ${src[*]} ${flags[*]} ${inc[*]} -o ${proj_name}
