#!/bin/bash

g++ main.cc -o project

for input_file in ./inputfile*; do
    result_file="${input_file/inputfile/result}"
    cp "$input_file" "$result_file"
    ./project < "$input_file" > "$result_file"
    output_file="${input_file/inputfile/outputfile}"
   # sleep(0.1)
    if diff -q "$output_file" "$result_file" > /dev/null; then
        echo "Test Passed!: $input_file"
    else
        echo "Test Failed: $input_file"
    fi
    rm "$result_file"
done

