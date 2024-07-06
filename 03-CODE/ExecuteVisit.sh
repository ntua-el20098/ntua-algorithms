#!/usr/bin/env bash

# Compile the program
g++ -std=c++11 visit.cpp

# Loop over all input files
for i in {1..22}
do
  # Run the program with input from input file and redirect output to a temporary file
  ./a.out < "lab03/visit/input$i.txt" > temp_output.txt

  # Compare the temporary file with the corresponding output file
  DIFF=$(diff -q temp_output.txt "lab03/visit/output$i.txt")

  # Print a message indicating whether the outputs match or not
  if [ "$DIFF" = "" ]
  then
    echo "Test $i PASSED"
  else
    echo "Test $i FAILED"
  fi
done

# Remove the temporary file
rm temp_output.txt
rm a.out