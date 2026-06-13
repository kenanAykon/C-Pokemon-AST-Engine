# Pokemon Go Search Query Parser

This is a custom search query parser written in C. It mimics the search bar functionality found in Pokemon Go, allowing users to filter Pokemon data using complex logical queries.

Instead of basic string matching, this project uses **Flex** and **Bison** to build a real parser. It tokenizes the input, creates an Abstract Syntax Tree (AST), and evaluates the data according to the given rules.

## Features
* **AST-Based Evaluation:** Builds a syntax tree to handle nested queries and operator precedence.
* **Logical Operators:** Supports AND (`&`), OR (`,`), and NOT (`!`), including parentheses `()` for grouping.
* **Supported Filters:**
  * Range queries: `cp10-1500`, `hp100-`, `year2023`, `age0-5`
  * IV checks: `3*`, `4*`
  * Flags: `shiny`, `shadow`, `legendary`
  * Move matching: `@bite`

## Tech Stack
* **Language:** C
* **Tools:** Flex (Lexical Analyzer), Bison/Yacc (Parser Generator)
* 
 ## 📌 Acknowledgments & Academic Context
This project was developed as part of an academic assignment. The data structures and data loading utilities (`pogo_types.h`, `data_loader.c/h`) were provided by the instructor as a base template. My core contribution and the main focus of this repository is the design and implementation of the **Query Parser and AST Evaluation Engine** (`lexer.l`, `parser.y`, `ast.c`).
