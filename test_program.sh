#!/bin/bash

g++ main.cc -o project

test_dir="./test_files"
all_tests_pass=1

for input_file in "$test_dir"/inputfile*; do
    result_file="${input_file/inputfile/result}"
    cp "$input_file" "$result_file"
    ./project < "$input_file" > "$result_file"
    output_file="${result_file/inputfile/outputfile}"
   # sleep(0.1)
    if diff -q "$test_dir/${output_file##*/}" "$result_file" > /dev/null; then
        echo "Test Passed!: $input_file"

    else
        echo "Test Failed: $input_file"
        all_tests_pass=0
	fi
    rm "$result_file"
done
	
if [ "$all_tests_pass" -eq 1 ]; then
	echo "ALL TESTS PASS"
fi
