# Formatted Table

## Overview

This is my first C++ project, created for learning purposes only. Displays a formatted terminal table from a CSV source file containing name, age, and gender data.

## Usage

For macos/linux:

```bash
./formatted-table <csv-file> [options]
```

For Windows:

```powershell
./formatted-table.exe <csv-file> [options]
```

### Parameters

- **csv-file**: Path to the input CSV data file (required).

#### Options

- **-n**, **--name-width**: Custom width for the 'Name' column (default: 25).
- **-a**, **--age-width**: Custom width for the 'Age' column (default: 5).
- **-g**, **--gender-width**: Custom width for the 'Gender' column (default: 6).

### Examples

```bash
# Default table column width configuration.
./formatted-table data.csv

# Custom table column width configuration.
./formatted-table data.csv -n 20 -a 8 -g 8
./formatted-table data.csv --name-width 20 --age-width 8 --gender-width
```

## Features

- Validates CSV file extension.
- Enforces positive column width.
- Prints table from CSV file.

## Dependencies

- C++20 compliant compiler.
- [p-ranav/argparse](https://github.com/p-ranav/argparse) for CLI argument parsing.
- [fmt](https://github.com/fmtlib/fmt) for pretty printing table.

## Implementation

- Populates data using `people::populatePeopleListFromCSV()`.
- Generates ASCII borders and aligns columns dynamically.
- Error handling for invalid inputs.

## Build (Or Download)

Use this for building this project in the current directory:

```bash
cmake -B build -S .
cd build && make
```

There will appear a `formatted-table` (or `formatted-table.exe`) file, in the `build/` directory. Another option would be to download directly from releases tab.
