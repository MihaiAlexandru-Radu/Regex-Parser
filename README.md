# Regex Parser 

## Description

Regular Expression can be used for a variety of tools. This project uses it specifically for word matching, with a more limited form of regex. For its base functionalities,
the program can read regex lines, take in short lines of text, and search for potential matches.

The overall design for my program was inspired by [Thompson's Construction algorithm](https://en.wikipedia.org/wiki/Thompson%27s_construction).

---

## Installation Guide

From a terminal, once you get into the project directory there are two options for installing and erasing:

1. Typing `make all` will create an executable which will run the main program. Typing `./main` will run the program. Typing `./test` will run all tests.
2. Typing `make clean` will delete the same executable.

---

## Usage

The program will prompt you with 5 options, which can be executed by typing numbers 1-5.

1. Prompts user to write a regular expression. If the program is also given a text, the program has capability of finding matches with other prompts.
2. Prints the graph, vertex by vertex, made from the regex. Given a vertex has a *key* and a *distance*, it prints the graph's vertices line by line: \['key' distance\] -> edges.
3. Prompts user to write text. Given a regex expression, this text will be checked for matches with other prompts.
4. Finds matches in text given regex expression. It prints the regex, text, and matches one by one. Given one *match* it prints \[match\].
5. Quits the program.

Regular Expressions are very extensive. This program uses a restricted version. Below are the allowed use cases:

*Ordered top from bottom based off precedence*
| Operation | Description| 
| --------- | ---------- |
| Parentheses | `()` can be used to bypass normal precedence. |
| One Or More | `A+` will search for any instances of *A* in chains of one or more. |
| Concatenation | `AB` will search for any instances of *AB*. |
| Alternation | `A\|B` will search for any instances of *A* or *B*. |

These operations can be combined to make compound regular expressions.
- `A(B|C)D` will search for *ABD* and *ACD* in a text
- `AB+|DC` will search for *AB* with the B once or repeating or *DC*
- `(A|B)C+` will search for *AC* or *BC* with the C once or repeating.

> [!NOTE]
> Any operations of One Or More are constrained to only one character at a time. `(AB)+` will not properly search for instances of *AB* repeating once or more. Likewise, parentheses cannot be in one another.

--- 

> by Mihai-Alexandru Radu 
