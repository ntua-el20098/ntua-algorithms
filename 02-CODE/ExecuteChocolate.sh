#!/usr/bin/env bash

# Compile the program
g++ -std=c++11 chocolate.cpp

# Loop over all input files
for i in {0..24}
do
  # Run the program with input from input file and redirect output to a temporary file
  { time ./a.out < "lab02/chocolate/input$i.txt" > temp_output.txt; } 2> time_output.txt

  # Compare the temporary file with the corresponding output file
  DIFF=$(diff -q temp_output.txt "lab02/chocolate/output$i.txt")

  # Print a message indicating whether the outputs match or not
  if [ "$DIFF" = "" ]
  then
    echo "Test $i PASSED"
    # Extract and print the real time from the time output file
    real_time=$(grep real time_output.txt | awk '{print $2}')
    echo "Time taken for Test $i: $real_time"
  else
    echo "Test $i FAILED"
  fi

  # Remove the temporary files
  rm temp_output.txt
  rm time_output.txt
done

# Remove the compiled executable
rm a.out
