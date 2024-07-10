# Documentation

This document serves as a personal reference, helping to track notes, document learnings, and outline the functionalities and mechanisms of the compiler.

## Overview of `%union` in Bison

In Bison grammar files, the `%union` declaration is crucial for defining a set of fields that can store various types of data associated with terminal and non-terminal symbols. This flexibility is fundamental in managing the diverse data types that symbols in a grammar might need.

### `%union` Definition

The `%union` constructs the `YYSTYPE`, which is the type for the semantic values of tokens and non-terminals in Bison:

```bison
%union {
    struct expr *expr_ptr;  // Holds pointers to expression structures.
    char* expr_id;          // Holds pointers to identifier strings.
}
```

#### Fields within `%union`
- **`expr_ptr`**: This field stores pointers to `expr` structures and is used for grammar symbols that represent expressions or components thereof. These symbols are manipulated or created during parsing to build the syntax tree or to perform semantic actions.
- **`expr_id`**: This field is designated for storing identifiers such as variable names, enabling the grammar to handle symbol identification effectively.

### Specifying Types for Grammar Symbols

To appropriately assign data types to grammar symbols, I employ the `%type` and `%token` directives:

```bison
%token <expr_id> TOKEN_ID
%token <expr_ptr> TOKEN_INT TOKEN_PLUS TOKEN_MINUS TOKEN_MUL TOKEN_DIV TOKEN_SEMI TOKEN_LPAREN TOKEN_RPAREN TOKEN_ASSIGN TOKEN_ERROR
%type <expr_ptr> expr term factor
```

#### Usage of Directives
- **`%token <expr_id> TOKEN_ID`**: Specifies that the `TOKEN_ID` token will carry a semantic value of type `char*`, utilizing the `expr_id` field in the `YYSTYPE` union. This is primarily used for tokens representing identifiers.
- **`%token <expr_ptr>` and `%type <expr_ptr>`**: Indicates that the specified tokens and non-terminals will carry semantic values as pointers to `expr` structures. These are stored in the `expr_ptr` field of the `YYSTYPE` union, critical for expression manipulation and evaluation in the grammar.

This setup ensures that each symbol in the grammar is equipped with the necessary type to hold its relevant data, facilitating efficient parsing and semantic analysis.