# RomanLang

# Roman Urdu Compiler

This repository contains a compiler for a Roman Urdu programming language, developed as a term project for the Compiler Construction course (CS4031) during the spring semester of 2023.

## Overview

The Roman Urdu Compiler is designed to translate source code, written in a hypothetical programming language that uses Roman Urdu (Urdu language transliterated using the Latin script), into machine code. The compiler consists of several stages, each performing specific tasks in the compilation process.

The main components of the compiler are as follows:

1. **Lexical Analyzer**: Implemented using RE (regular expressions) and DFA (Deterministic Finite Automaton), the lexical analyzer tokenizes the Roman Urdu source code. It identifies individual tokens such as keywords, identifiers, operators, and literals.

2. **Parser**: The parser performs syntax analysis using Context-Free Grammar (CFG). It checks the order and structure of the tokens to ensure they conform to the grammar rules of the Roman Urdu programming language. This step helps to detect syntax errors and build a parse tree.

3. **Intermediate Code Generation**: After parsing the source code, the compiler generates Three-Address Code (TAC) and builds a symbol table. The TAC represents the intermediate representation of the source code, making it easier to perform further optimizations and code generation.

4. **Code Generation**: In this stage, the compiler generates machine code from the TAC representation. It translates the intermediate code into instructions that can be executed on a virtual machine. The machine code can then be executed on the virtual machine, simulating the execution of the Roman Urdu source code.

## Technologies Used

The compiler is implemented using the following technologies:

- C++: The main programming language used for the implementation of the compiler stages.
- Regular Expressions (re): Used for pattern matching and tokenization in the lexical analyzer.
- DFA (Deterministic Finite Automaton): Implemented to improve the efficiency of the lexical analyzer.
- Context-Free Grammar (CFG): Used in the parser for syntax analysis and building a parse tree.

## Getting Started

To get started with the Roman Urdu Compiler, follow these steps:

1. Clone the repository: https://github.com/Hassaan-T075/RomanLang.git
2. Navigate to the project directory: cd RomanLang
3. Run code by using following commands in terminal
  1- make
  2- ./a.out sample_code.ru
  3- make clean
  
## Contributions

This compiler was developed as a collaborative effort by Hassaan Tahir (https://github.com/Hassaan-T075) and Abdul Ali (https://github.com/itsAbdulAli) as part of the Compiler Construction course (CS4031).
