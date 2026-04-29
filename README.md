*This project has been created as part of the 42 curriculum by lucinguy, ccauderl.*

# Minishell

## Description

The **Minishell** project is about writing our own shell, based on bash posix.
It must contain the following features :
- Display of a prompt when waiting for a new command
- Have a working history
- Search and launch the right executable (based on the PATH or using a relative/absolute path)
- Indicate a received signal.
- Handle single and double quotes
- Handle the following redirections:
	- < to redirect input
	- \> to redirect output
	- << and >>
- pipes
- Handle environment variables
- Handle ctrl-C, ctrl-D and ctrl-\
- The following built-in :
	- echo (and its flag -n)
	- cd with only a relative or absolute path
	- pwd
	- export
	- unset
	- env (with no argument)
	- exit

## Instructions



## Resources
A pretty precise description of Bash and Shell : Bash Reference Manual
https://www.gnu.org/software/bash/manual/bash.html#What-is-Bash_003f

A tutorial to start the tokenizer :
https://mvsrgc.xyz/posts/Write-a-Shell-Tokenizer-in-C/

GNU Readline Library :
https://tiswww.cwru.edu/php/chet/readline/readline.html

A tutorial about signals :
https://www.geeksforgeeks.org/c/signals-c-language/

Another tutorial about enumerations:
https://www.w3schools.com/c/c_enums.php

A project subject about writing a shell from the Northeatern University:
https://course.ccs.neu.edu/cs3650sp23/p1.html

A site used to have the manual to the authorized functions:
https://man7.org/linux/man-pages/