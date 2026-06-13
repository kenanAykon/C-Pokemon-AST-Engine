# Pokemon Go Search Query Parser ⚡

## Overview
This project is a custom search query parser and evaluator inspired by the in-game search mechanics of Pokemon Go. Built using **C, Flex (Lexical Analyzer), and Bison (Parser Generator)**, the system is designed to parse complex logical string queries, construct an Abstract Syntax Tree (AST), and efficiently evaluate structured data against these dynamic filters.

Instead of hardcoding search algorithms, this project implements a true parsing engine, demonstrating foundational concepts of compiler design and formal languages.

## 🚀 Key Features
* **Lexical Analysis & Parsing:** Utilizes `Lex/Flex` and `Yacc/Bison` to tokenize and parse search queries.
* **AST Implementation:** Dynamically builds an Abstract Syntax Tree (AST) to handle nested logic and operator precedence.
* **Complex Logical Operators:** Supports `AND (&)`, `OR (,)`, and `NOT (!)` operations along with parentheses `()` for grouping.
* **Range & Specific Filters:** * Combat Power and Health Points (`cp10-1500`, `hp100-`)
  * Catch dates and age (`year2023`, `age0-5`)
  * IV Appraisals (`3*`, `4*`)
  * Boolean flags (`shiny`, `shadow`, `legendary`)
  * Move matching (`@bite`)

## 🛠️ Technology Stack
* **Language:** C 
* **Tools:** Flex (Lexer), Bison/Yacc (Parser)
* **Architecture:** Abstract Syntax Tree (AST), Modular Struct Design

## 🧠 How It Works (Under the Hood)
1. **Tokenizer (`lexer.l`):** Reads the raw input string (e.g., `cp1000-2000 & 3*`) and converts it into meaningful tokens (`TOK_CP`, `TOK_NUM`, `TOK_AND`).
2. **Parser (`parser.y`):** Applies grammar rules to the tokens and constructs a hierarchical AST (`FilterNode`).
3. **Evaluator (`ast.c`):** Traverses the AST recursively to evaluate a specific `PokemonInstance` against the compiled logic rules, returning a final boolean result (Match / No Match).
