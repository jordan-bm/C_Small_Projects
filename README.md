# C Programming Mini Projects

A collection of small, self-contained C programs demonstrating core programming concepts, syntax, and problem-solving skills. This repo showcases practical applications of fundamental programming techniques in C.

---

## Overview

This repository contains assignments focused on different programming skills:

- **area_calculator.c** - Area calculator for rectangle, triangle, and circle with interactive user input and validation.
- **array_operations.c** - Array operations supporting printing elements, summing values, finding maximum, and identifying primes via command-line options.
- **password_validator.c** - Password validator checking length, character types, spaces, and security criteria with user feedback.
- **grade_processor.c** - Student grade processor reading CSV input, calculating weighted grades, statistics, and outputting summaries.

---

## Features

- Interactive CLI applications and batch processors
- Dynamic memory management
- File input/output with CSV parsing
- Basic algorithm implementations (prime detection, summation, max value)
- Input validation and error handling
- Structured use of `structs` and functions for modular code

---

## Usage

### Compile

Compile each program separately:

gcc -o area_calculator area_calculator.c
gcc -o array_operations array_operations.c
gcc -o password_validator password_validator.c
gcc -o grade_processor grade_processor.c

### Run

- **Area Calculator:**  
  Run `./area_calculator` and follow on-screen prompts to calculate area of shapes.

- **Array Operations:**  
  Usage pattern:  
./array_operations -p 5 1 2 3 4 5 # Print array
./array_operations -s 5 1 2 3 4 5 # Sum elements
./array_operations -m 5 1 2 3 4 5 # Maximum value
./array_operations -c 5 1 2 3 4 5 # Print primes

- **Password Validator:**  
Run `./password_validator` and enter a password; program outputs validation result and feedback.

- **Grade Processor:**  
Ensure `students.csv` is in the working directory; run `./grade_processor` to generate grade reports and statistics in `final.txt`