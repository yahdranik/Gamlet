# Onegin

A robust C program designed to read text from a file, split it into individual lines, and perform custom sorting operations - specifically sorting lines alphabetically from the beginning and from the end (ignoring punctuation).

## Features

* **File Reading & Parsing:** Safely reads text data from an input file and dynamically builds an array of lines (pointers to the text segments).
* **Forward Sorting:** Sorts the lines lexicographically from the beginning of the string.
* **End Sorting:** Sorts the lines starting from their endings (useful for rhyming dictionaries or poetic analysis), intelligently skipping non-letter characters.
* **Result Export:** Writes the original text, the forward-sorted text, and the end-sorted text back into a clean output file.

## Project Structure

* `main.c` - Entry point, buffer allocation, line pointer setup, and program cleanup.
* `all_for_sort.c` - Core sorting logic, including custom `qsort` implementation, string comparisons, and character filtering.
* `all_for_sort.h` - Header file containing function prototypes and structure definitions.

## Compilation and Usage

Make sure you have a C compiler installed (such as `gcc`).

1. Compile the project:
   ```
   .\myscript.bat
   ```

2. Run the executable:
   ``` 
   .\mimimi.exe 
   ```
