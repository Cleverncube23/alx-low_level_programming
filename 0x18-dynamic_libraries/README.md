# Dynamic Library Project

This project demonstrates the creation of a dynamic library containing various C functions. The functions are intended to be used in C programs and can also be accessed from Python using the `ctypes` library.

## Table of Contents

- [Introduction](#introduction)
- [Function List](#function-list)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Python Integration](#python-integration)

## Introduction

This project showcases the creation of a dynamic library (`libdynamic.so`) that encapsulates several useful C functions. The functions cover common tasks such as string manipulation, character checks, mathematical operations, and more. The library can be utilized in C programs and is also accessible from Python.

## Function List

The dynamic library `libdynamic.so` includes the following functions:

- `_putchar`
- `_islower`
- `_isalpha`
- `_abs`
- `_isupper`
- `_isdigit`
- `_strlen`
- `_puts`
- `_strcpy`
- `_atoi`
- `_strcat`
- `_strncat`
- `_strncpy`
- `_strcmp`
- `_memset`
- `_memcpy`
- `_strchr`
- `_strspn`
- `_strpbrk`
- `_strstr`

For a detailed explanation of each function, refer to the corresponding source code in the repository.

## Getting Started

To compile the dynamic library and utilize the included functions, follow these steps:

1. Clone this repository to your local machine.
2. Navigate to the repository's directory:
   ```bash
   cd Dynamic-Library-Project
ompile the dynamic library:

bash

    gcc -shared -o libdynamic.so -fPIC dynamic_library.c

    You can now use the libdynamic.so library in your C programs.

Usage

    After compiling the dynamic library, you can include the main.h header in your C programs to access the function prototypes.
    Link your C program with the dynamic library during compilation. For example:

    bash

    gcc -o my_program my_program.c -L. -ldynamic

    Run your compiled C program.

Python Integration

The dynamic library can also be accessed from Python using the ctypes library. An example script (python_example.py) is provided in the repository to demonstrate Python integration.

To run the Python script:

    Ensure that the dynamic library libdynamic.so is in the same directory.
    Run the Python script:
