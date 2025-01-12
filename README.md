# Wacky Trees Data System

This project, **Wacky Trees Data System**, is a compression system designed to optimize the storage of ASCII character data using binary trees and linked lists. It processes input data, encodes it into a compressed binary tree structure, and decodes it when needed. This project demonstrates core concepts of **C programming**, **data structures**, and **memory management**.

---

## Features

- **Linked List Implementation**: Constructs a sorted linked list to store ASCII character probabilities in ascending order of occurrence frequency and value.
- **Binary Tree Generation**: Merges nodes from the linked list to create a balanced binary tree, representing character weights and probabilities.
- **Efficient Memory Management**: Ensures proper allocation and deallocation of memory for nodes in both the linked list and the binary tree.
- **Tree Height Calculation**: Computes the height of the binary tree to determine its balance and depth.

---

## Files Included

- **`wackman.c`**: Contains the main implementation of functions for linked lists, binary tree creation, and compression logic.
- **`wackman.h`**: Header file defining shared structures (e.g., `WackyTreeNode`, `WackyLinkedNode`) and utility functions.
- **Starter Code**: Initial template files provided, such as test drivers or predefined constants.

---

## How It Works

1. **Calculate Character Occurrences**:
   - Takes an input string and computes the occurrence of each ASCII character.

2. **Build a Sorted Linked List**:
   - Constructs a linked list, where each node represents a tree with a single ASCII character and its probability of occurrence.

3. **Merge Nodes to Form a Binary Tree**:
   - Iteratively combines linked list nodes into a binary tree, sorting by weights to maintain an optimized structure.

4. **Tree Operations**:
   - Encode a character: Traverse the binary tree to produce a unique binary representation.
   - Decode a binary sequence: Navigate the binary tree using the sequence to retrieve the original character.

---

## Requirements

- **Compiler**: `gcc` with support for `C99`
- **Language**: C
- **Libraries Used**: 
  - `stdlib.h`
  - `stdbool.h`
  - `stdio.h`
  - `math.h`
  - `string.h`

---

## Compilation and Execution

1. **Compile**:
   Run the following command to compile the project:
   ```bash
   gcc -std=c99 -Wall -Werror -o wackman wackman.c
2. execution;
   ./wackman

Functions Overview

compute_occurrence_array: Computes the frequency of ASCII characters in the input string.

create_wacky_list: Builds a sorted linked list of ASCII characters and their probabilities.

merge_wacky_list: Merges linked list nodes to create a binary tree for compression.

get_wacky_code: Encodes an ASCII character into a binary sequence using the tree.

get_character: Decodes a binary sequence into the corresponding ASCII character.

free_tree: Frees memory associated with the binary tree.

Project Structure:

├── wackman.c   # Main implementation file with core logic for linked lists and binary trees

├── wackman.h   # Header file defining shared data structures and helper functions

└── README.md   # Documentation file explaining the project, features, and usage


This project uses: Data structures (linked lists and binary trees) and memory management in C
