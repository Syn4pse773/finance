# Secure Terminal Finance Manager

A fast, lightweight, and secure console-based personal finance manager written in C. This project features a custom x86-64 Assembly encryption engine to ensure your local financial data remains private and protected.

## Features

- **Interactive TUI**: A clean Terminal User Interface to track your total balance, manage multiple bank cards, and monitor financial goals.
- **Low-Level Encryption**: Utilizes a custom, highly optimized XOR cipher written in Flat Assembler (FASM) (`xor.asm`) to encrypt the binary database (`finance.enc`) before saving it to disk.
- **Security First**: Includes a dedicated testing suite designed to validate memory safety, check for buffer bounds (canary testing), prevent padding leaks, and ensure cryptographic symmetry.
- **Zero Dependencies**: Built entirely with standard C libraries and bare-metal assembly.

## Project Structure

```text
.
├── main.c              # Core application logic and Terminal User Interface (TUI)
├── xor.asm             # x86-64 Assembly implementation of the encryption subroutine
├── tests/              # Security validations and unit tests
│   └── test_finance.c  # Test suite (Symmetry, Boundary, Zero-size, Padding tests)
├── finance.enc         # Encrypted local database (Generated at runtime)
└── README.md           # Project documentation
```

## Prerequisites

To build and run this project, you need a Linux environment (x86-64) with the following tools installed:

- **GCC**: GNU Compiler Collection for compiling the C code.
- **FASM**: Flat Assembler for compiling the x86-64 assembly file.
- **Make**: (Optional) If you plan to set up build automation.

## Installation & Build

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/finance-manager.git
   cd finance-manager
   ```

2. Compile the Assembly encryption engine:
   ```bash
   fasm xor.asm xor.o
   ```

3. Compile the main application, linking the compiled assembly object:
   ```bash
   gcc main.c xor.o -o finance_manager
   ```

4. Run the application:
   ```bash
   ./finance_manager
   ```

## Running the Tests

Security and stability are critical for a finance application. The `tests/` directory contains unit tests that ensure the assembly code interacts safely with the C environment without causing segmentation faults or memory corruption.

To compile and run the test suite:

```bash
# Ensure the assembly object is compiled first
fasm xor.asm xor.o

# Compile the testing suite
gcc tests/test_finance.c xor.o -o run_tests

# Execute the tests
./run_tests
```

### Test Coverage Includes:
- **Symmetry Verification**: Ensures `E(E(data, key), key) == data`.
- **Buffer Boundary Constraints**: Uses memory canaries to verify the ASM routine strictly stays within allocated buffer boundaries (preventing Overflow/Underflow).
- **Edge Cases**: Validates handling of `0` byte sizes natively in ASM without infinite loops or crashes.
- **Structure Padding Security**: Ensures hidden memory padding injected by the C compiler doesn't cause out-of-bounds reads during serialization.

## Disclaimer

This project was developed for educational purposes to demonstrate the integration of C and x86-64 Assembly, system ABI compliance, and low-level memory management. The included XOR cipher is highly optimized but is a symmetric stream cipher intended for demonstration; it should not be used as a replacement for industry-standard cryptographic algorithms (like AES) in enterprise environments.

## License

This project is open-source and available under the MIT License.



Copyright 2026 Syn4pse773

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
