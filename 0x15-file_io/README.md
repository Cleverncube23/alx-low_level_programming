## [C - File I/O](0x15-file_io) :file_folder:

## [Tests](./tests) Tests Folder



## [Main.h](./main.h) This Directory contains all the prototypes. 

| File                      | Prototype                                                            |
| ------------------------- | -------------------------------------------------------------------- |
| `0-read_textfile.c`       | `ssize_t read_textfile(const char *filename, size_t letters);`       |
| `1-create_file.c`         | `int create_file(const char *filename, char *text_content);`         |
| `2-append_text_to_file.c` | `int append_text_to_file(const char *filename, char *text_content);` |

## Tasks :page_with_curl:

* `0. Tread lightly, she is near`
  * [0-read_textfile.c](./0-read_textfile.c): C function that reads a text file and
  prints it to the `POSIX` standard output.
 

* `1. Under the snow`
  * [1-create_file.c](./1-create_file.c): C function that creates a file.
  * The paramter `filename` is the name of the file to create.
  

* `2. Speak gently, she can hear`
  * [2-append_text_to_file.c](./2-append_text_to_file.c): C function that appends text at
  the end of a file.
  * The parameter `filename` is the name of the file.
  

* `3. cp`
  * [3-cp.c](./3-cp.c): C program that copies the contents of a file to another file.
  * Usage: `cp file_from file_to`
  * If `file_to` already exists, it is truncated.
  * The created file has the permissions `rw-rw-r--`.
  * If the file already exists, the existing permissions are not changed.
  * If the number of arguments is incorrect, the function prints `Usage: cp file_from
  file_to`, followed by a new line on the `POSIX` standard error and exits with code `97`.
  * If `file_from` does not exist or the user lacks read permissions on it,
  the function prints `Error: Can't read from file NAME_OF_THE_FILE`, followed by a new
  line and exits with code `98`.
       

* `4. elf`
  * [100-elf_header.c](./100-elf_header.c): C program that displays the information contained
  in the `ELF` header at the start of an `ELF` file.
  * Usage `elf_header elf_filename`
  * Displayed information:
    * Magic
    * Class
    * Data
    * Version
    * OS/ABI
    * ABI Version
    * Type
    * Entry point address
  * Format is identical to `readelf -h` (version `2.26.1`).
  * If an error occurs or the file is not an `ELF` file, the function displays a
  corresponding error message to `stderr` and exits with a status value of `98`.
