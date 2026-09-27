# Extended Hamming Code (8,4) — C++

This repository contains my university project for implementing and testing the extended Hamming code (8,4) in C++.

The project was developed as part of my Computer Security studies.

## Project goal

The goal of the project is to implement a complete cycle of:

```text
Input data
↓
Encoding
↓
Error simulation
↓
Decoding
↓
Error detection / correction
↓
Data recovery
```

## Hamming code (8,4)

The program works with an extended Hamming code:

```text
4 information bits
↓
8-bit code word
```

The encoded word contains:

- 4 information bits
- Hamming parity bits
- an additional parity bit

The additional parity bit helps distinguish different error cases.

## Main functions

The project contains logic for:

### Encode

```text
Input:
4 information bits

Output:
8-bit encoded word
```

The encoding function calculates parity bits and creates the final code word.

### Syndrome

The syndrome is calculated from the received code word.

It is used to identify possible errors.

### Decode

The decoder analyzes:

```text
Hamming syndrome
+
overall parity
```

and determines the result.

Possible states include:

```text
No error
Single error corrected
Parity bit error corrected
Double error detected
```

## Error handling

The improved version can:

- detect a single-bit error
- correct a single-bit error
- detect and correct an error in the additional parity bit
- detect a double-bit error

Example logic:

```text
Syndrome = 0
Parity = 0
→ No error

Syndrome ≠ 0
Parity = 1
→ Single error
→ Correction

Syndrome = 0
Parity = 1
→ Parity bit error

Syndrome ≠ 0
Parity = 0
→ Double error detected
```

## Program workflow

```text
Input message
↓
Split into 4-bit blocks
↓
Encode each block
↓
Create 8-bit code words
↓
Simulate transmission errors
↓
Calculate syndrome
↓
Decode
↓
Correct errors when possible
↓
Extract information bits
↓
Compare recovered data with original data
```
## Project versions

This repository contains two versions of the program.

### 1. Course version

File:

```text
main.cpp
```

This is the original version developed during my university course project.

It implements:

- 4-bit to 8-bit encoding
- syndrome calculation
- single-bit error correction
- information bit extraction
- multi-block data simulation
- random error generation
- result comparison

Program flow:

```text
4-bit data
↓
Encode
↓
Add simulated error
↓
Decode
↓
Extract original data
↓
Compare result
```

### 2. Improved research version

File:

```text
main_improved.cpp
```

This version is based on the later research work.

The decoder was improved to distinguish four different states:

```text
NoError
SingleErrorCorrected
ParityErrorCorrected
DoubleErrorDetected
```

The improved logic uses:

```text
Hamming syndrome
+
overall parity
```

to determine the type of error.

Possible results:

```text
Syndrome = 0
Parity = 0
→ No error

Syndrome != 0
Parity = 1
→ Single-bit error
→ Error corrected

Syndrome = 0
Parity = 1
→ Additional parity-bit error
→ Error corrected

Syndrome != 0
Parity = 0
→ Double-bit error
→ Error detected but not corrected
```

The demonstration in `main_improved.cpp` tests:

- no error
- single-bit error
- parity-bit error
- double-bit error

## Project structure

```text
hamming-code-cpp
├── README.md
├── main.cpp
└── main_improved.cpp
```

## Project development

The project shows the development from a basic implementation to a version with more detailed error classification.

```text
Course project
↓
Basic encoding and decoding
↓
Research work
↓
Improved error detection
↓
Single-error correction
+
Double-error detection
```

## Technologies

- C++
- bitwise operations
- error detection
- error correction
- linear error-correcting codes


## Testing

The university research also included testing of the implemented algorithms.

The testing was used to analyze the operation and performance of the encoding and decoding functions.

## What I practiced

During this project I practiced:

- C++ programming
- bitwise operations
- implementation of algorithms
- debugging
- testing
- working with binary data
- error detection and correction
- analyzing algorithm results

## University project

This project was developed during my studies in:

```text
10.05.01 Computer Security
```

The work was related to the study and implementation of linear error-correcting codes.

## Goal

The main goal of this repository is to demonstrate my C++ programming practice and understanding of the basic principles of error detection and correction using Hamming codes.
