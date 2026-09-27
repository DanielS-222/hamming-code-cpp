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

The program can:

- detect a single-bit error
- correct a single-bit error
- detect an error in the additional parity bit
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

## Technologies

- C++
- bitwise operations
- error detection
- error correction
- linear error-correcting codes

## Testing

The project also includes testing of the implemented algorithms.

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
