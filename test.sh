#!/bin/bash

# this is a fast build-run bash file specific for program tests
# to turn this on, type:
#
# $ chmod u+x test.sh
#
# and to run, just type:
#
# # ./test.sh
#
# Unfortunately, this will work only for unix-like pc's or machines
# that contains the bash tool

# getting values from cmd line/cur dir
all_sources=$(ls src/*.c)
final_file="./out/exe.tic-tac-low-test"
args_count=$#
arg=$1

# clear terminal and prepare to print content
clear

# if invalid argc
if [ 1 -ne $args_count ]; then
  echo
  echo "  Invalid arg count: (received $args_count, expected: 1)"
  echo "  Exiting program..."
  echo
  exit 0
fi

# else, continue
echo
echo "  Preparing for test..."
echo "  Let's compile: "

# show each file being compiled
for fl in $all_sources; do
  echo "      > $fl"
done

# if test file already exists
if [ -f $final_file ]; then \
  rm $final_file
fi

# compile
gcc $all_sources -o $final_file;

# echo separator
echo
echo "  --------------------------------------------------------------------"

# if test file exists (successfuly compiled)
if [ -f $final_file ]; then
  $final_file $arg
fi

echo
