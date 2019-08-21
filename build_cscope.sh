#!/bin/bash
echo "Creating ctags database..."
ctags -R *
echo "Creating source file list..."
find . -name "*.c" -o -name "*.h" -o -name "*.hh" -o -name "*.hpp" -o -name "*.s" -o -name "*.S" -o -name "*.cpp"  -o -name "*.cc" > cscope.files
echo "Creating cscope symbols database..."
cscope -b
echo "cscope initialization Done."
