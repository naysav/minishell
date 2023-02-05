# minishell

Minishell is a minimum viable version of a real shell.

## Project requirements
- Shell should implement the buildins:
  - `echo` with option -n
  
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options

- Not interpret unclosed quotes or unspecified special characters like `\` or `;`
- Have a working History
- Search and launch the right executable
- `’`  and  `"`  inhibit all interpretation of a sequence of characters
- Redirections:
   - `<`   should redirect input
   - `>`   should redirect output
   - `<<` read input from the current source until a line containing only the delimiter is seen
   - `>>` should redirect output with append mode
- Pipes `|` The output of each command in the pipeline is connected via a pipe to the
input of the next command
- Environment variables ($ followed by characters) should expand to their values
- `$?` should expand to the exit status of the most recently executed foreground pipeline
- `ctrl-C` `ctrl-D` `ctrl-\` should work like in bash
- When interactive:
   - `ctrl-C` print a new prompt on a newline
   - `ctrl-D` exit the shell
   - `ctrl-\` do nothing
