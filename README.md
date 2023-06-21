# pipex

pipex is a C project developed as part of the 1337/42 cursus. It aims to implement the functionality of the pipe (`|`) operator in Unix-like systems.

## Installation

To install and use pipex, follow these steps:

1. Clone the pipex repository:

   ```
   https://github.com/mberrouk/pipex.git
   ```

2. Navigate to the project directory:

   ```
   cd pipex
   ```

3. Compile the pipex program:

   ```
   make
   ```

This will generate an executable file named `pipex`.

## Usage

To use pipex, you need to provide four arguments: `infile`, `command1`, `command2`, and `outfile`. The output of `command1` will be redirected as the input to `command2`, and the final output will be written to `outfile`.

Here's the basic syntax:

```
./pipex infile command1 command2 outfile
```

- `infile`: The input file to be used as the initial input for `command1`.
- `command1`: The first command whose output will be redirected.
- `command2`: The second command that will receive the output of `command1` as input.
- `outfile`: The output file where the final output will be written.

Example usage:

```
./pipex infile.txt "ls -l" "grep example" outfile.txt
```

This will take the contents of `infile.txt`, execute the command `ls -l` on it, and then execute the command `grep example` on the output. The final output will be written to `outfile.txt`.

### Additional Notes

- If you want to use a command with arguments, enclose the command in quotes. For example: `"ls -l"`.


