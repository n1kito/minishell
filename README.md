<h1 align="center">mini(s)hell 🔥</h1>
<p align="center">
<img src="img/hell.gif" width="200px" alt="elmo hell gif"><br />
Our work on the 42Born2Code <b>minishell</b> project.<br /><br />
</p>

> This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.

# [Minishell B*tch](https://www.notion.so/Task-List-Matthieu-Victor-09bcc22ebede42a09f040a39379b5baf)

# To-do

- [ ] Implementer le prompt
	- [ ] Comprendre comment fonctionne l'historique
- [ ] Lexer / Parser
	- [ ] Discuter des structs necessaires au parsing
	- [ ] Coder une fonction print qui permet d'imprimer tous les ASTs pour visualiser que le parsing se passe correctement.

### Teamwork Guidelines

- Utilisation d'un [Trello](https://trello.com/b/2fylEX2B/mod%C3%A8le-kanban) pour faciliter le suivi de l'avancement et des choses à faire.
- Points réguliers à 11h00.
- Fonctionnement avec branches et Pull Requests.
	- Les PRs doivent être reviewed par nous deux avant d'être `merged`.
	- Tout ce qui est `merged` doit être normé.

# Project Requirement Checklist

<details><summary><i>(+ click to expand)</i></summary>

| Program name       | minishell                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
|--------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Turn in files      | Makefile, *.h, *.c                                                                                                                                                                                                                                                                                                                                                                                                                                                           |
| Makefile           | NAME, all, clean, fclean, re                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| External functions | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_dedisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |
| Libft authorized   | Yes                                                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| Description        | Write a shell                                                                                                                                                                                                                                                                                                                                                                                                                                                                |

**The shell should:**
- [ ] Display a **prompt** when waiting for a new command
- [ ] Have a working history
- [ ] Search and launch the right executable (based on the `PATH` variable or using a relative or an absolute path).
- [ ] Not use more than **one global variable**. Think about it. You will have to explain its purpose.
- [ ] Not interpret unclosed quotes or special characters which are not requires by the subject such as `\` or `;`.
- [ ] Handle ' (single quote) which should prevent the shell from interpreting the meta-characters in the quotes sequence.
- [ ] Handle `"` (double quote) which should prevent the shell from interpreting the meta-characters in the quotes sequence except for $ (dollar sign).
- [ ] Implement **redirections**
  - [ ] `<` should redirect input.
  - [ ] `>` should redirect output.
  - [ ] `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn't have to update the history.
  - [ ] `>>` should redirect output in append mode.
- [ ] Implement **pipes** (`|` character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- [ ] Handle **environment variables** (`$` followed by a sequence of characters) which should expand to their values.
- [ ] Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.
- [ ] Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash.
- [ ] In interactive mode
  - [ ] `ctrl-C` displays a new prompt on a new line.
  - [ ] `ctrl-D` exits the shell.
  - [ ] `ctrl-\` does nothing.
- [ ] Your shell must implement the following **builtins**:
  - [ ] `echo` with option `-n`
  - [ ] `cd` with only a relative or absolute path
  - [ ] `pwd` with no options
  - [ ] `export` with no options
  - [ ] `unset` with no options
  - [ ] `env` with no options or arguments
  - [ ] `exit` with no options

> The `readline()` function can cause memory leaks. You don't have to fix them. But that **does not mean your own code can have memory leaks**.

> You should limit yourself to the subject description. Anything that is not asked is not required. If you have any doubt about a requirement, take bash as a reference.

</details>

# Research

## Shell operations

Shell reads and executes commands in the following way:
1. Reads its input from a file or terminal.
2. Breaks this input into words and operators, obeying the shell quoting rules.
   - Alias expansion is performed here.
3. Parses the token in to _simple_ and _compound_ commands.
4. Perfoms the various shell expansions, breaking expanded tokens into lists of filenames and commands and arguments.
5. Performs any necessary redirections and removes the redirection operators and their operands from the argument list.
6. Executes the command.
7. Optionally waits for the command to complete and collects its exit status.

## [Tokenizer](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03)

<details><summary><i>(+ click to see tokenizing process)</i></summary>

> The shell shall read its input in terms of lines. (For details about how the shell reads its input, see the description of sh.) The input lines can be of unlimited length.  
> 
> These lines shall be parsed using two major modes: ordinary token recognition and processing of here-documents.  
> 
> When an io_here token has been recognized by the grammar (see Shell Grammar), one or more of the subsequent lines immediately following the next NEWLINE token form the body of one or more here-documents and shall be parsed according to the rules of Here-Document.  
> 
> When it is not processing an io_here, the shell shall break its input into tokens by applying the first applicable rule below to the next character in its input.
> 
> The token shall be from the current position in the input until a token is delimited according to one of the rules below; the characters forming the token are exactly those in the input, including any quoting characters.
> 
> If it is indicated that a token is delimited, and no characters have been included in a token, processing shall continue until an actual token is delimited.

### Tokenizer process:

- [x] (1) If the end of input is recognized, the current token (if any) shall be delimited.
- [x] (2) If the previous character was used as part of an operator and the current character is not quoted and can be used with the previous characters to form an operator, it shall be used as part of that (operator) token.
  - [Shell operators](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_260) are:
    - Control Operators: `&` `&&` `(` `)` `;` `;;` `newline` `|` `||` _(The end-of-input indicator used internally by the shell is also considered a control operator.)_
    - Redirection Operators: `<` `>` `>|` `<<` `>>` `<&` `>&` `<<-` `<>`
  - **According to the `minishell` subject, we have to handle the following operators**: `<` `>` `<<` `>>` and `|`
- [x] (3) If the previous character was used as part of an operator and the current character cannot be used with the previous characters to form an operator, the operator containing the previous character shall be delimited.
- [ ] (4) If the current character is `<backslash>`, single-quote, or double-quote and it is not quoted, it shall affect quoting for subsequent characters up to the end of the quoted text. 
  - The rules for quoting are as described in Quoting.
  - During token recognition no substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input (except for <newline> joining), unmodified, including any embedded or enclosing quotes or substitution operators, between the <quotation-mark> and the end of the quoted text. The token shall not be delimited by the end of the quoted field.
  - The various quoting mechanisms are the escape character ` \ `, single-quotes `'`, and double-quotes `"`.
  - [More about UNIX Shell Quoting](https://rg1-teaching.mpi-inf.mpg.de/unixffb-ss98/quoting-guide.html)
- [ ] (5) If the current character is an unquoted '$' or '`', the shell shall identify the start of any candidates for parameter expansion (Parameter Expansion), command substitution (Command Substitution), or arithmetic expansion (Arithmetic Expansion) from their introductory unquoted character sequences: '$' or "${", "$(" or '`', and "$((", respectively. The shell shall read sufficient input to determine the end of the unit to be expanded (as explained in the cited sections). While processing the characters, if instances of expansions or quoting are found nested within the substitution, the shell shall recursively process them in the manner specified for the construct that is found. The characters found from the beginning of the substitution to its end, allowing for any recursion necessary to recognize embedded constructs, shall be included unmodified in the result token, including any embedded or enclosing substitution operators or quotes. The token shall not be delimited by the end of the substitution.
- [ ] (6) If the current character is not quoted and can be used as the first character of a new operator, the current token (if any) shall be delimited. The current character shall be used as the beginning of the next (operator) token.
- [x] (7) If the current character is an unquoted `<blank>`, any token containing the previous character is delimited and the current character shall be discarded.
- [x] (8) If the previous character was part of a word, the current character shall be appended to that word.
- [x] (9) ~~If the current character is a '#', it and all subsequent characters up to, but excluding, the next <newline> shall be discarded as a comment. The <newline> that ends the line is not considered part of the comment.~~
- [ ] (10) The current character is used as the start of a new word.

Once a token is delimited, it is categorized as required by the grammar in Shell Grammar.

</details>

## Simple Command Expansion

When a simple command is executed, the shell performs the following expansions, assignments, and redirections, from left to right, in the following order:
1. The words that the parser has marked as variable assignments (those preceding the command name) and redirections are saved for later processing.
2. The words that are not variable assignments or redirections are expanded. If any words remain after expansion, the first word is taken to be the name of the command and the remaining words are the arguments.
3. Redirections are performed.
4. The text after the `=` in each variable assignment undergoes tilde expansion, parameter expansion, command substitution, arithmetic expansion, and quote removal before being assigned to the variable.  

(Look at docs for details)

# Minishell Process

```mermaid
graph TD;
    A[Lexer]-->B[Parser];
    B-->C[Execution];
```

## Lexer
### Token Recognition

[See Bash Rules for Token Recognition](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03)


# Resources

## Online

- [x] 🎥 [Shell Code Explained (1/2)](https://www.youtube.com/watch?v=ubt-UjcQUYg&t=337s) ⭐⭐
- [x] 🎥 [Shell Code - More Details (2/2)](https://www.youtube.com/watch?v=ZjzMdsTWF0U&t=1614s) ⭐⭐
- [x] [Recursive Descent Parsing](https://www.youtube.com/watch?v=SToUyjAsaFk) ⭐⭐
- [ ] [How to Parse Shell Like a Programming Language](https://www.oilshell.org/blog/2019/02/07.html)
- [x] [42Docs](https://harm-smits.github.io/42docs/projects/minishell)
    - [ ] [Git with concepts explained](https://github.com/Swoorup/mysh)
    - [ ] [Understanding the shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html) ⭐
    - [ ] [lexer -> parser -> expander -> executor](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [ ] [Effective shell](https://effective-shell.com/)
- [ ] [Manuel bash](https://www.gnu.org/software/bash/manual/bash.html) ⭐
- [ ] [POSIX Docs](https://pubs.opengroup.org/onlinepubs/9699919799/)
- [ ] [Writing your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [x] [Bash one liners explained](https://catonmat.net/bash-one-liners-explained-part-three)
- [x] [Write a shell in C (Tutorial)](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [ ] [Understanding ASTs (Abstract Syntax Trees)](https://ruslanspivak.com/lsbasi-part7/)
### La syntaxe de shell :
- [ ] [Bash in Backus-Naur form](https://cmdse.github.io/pages/appendix/bash-grammar.html)

## From other 42 students

- @vietdu91's [project](https://github.com/vietdu91/42_minishell)  
    - And his [minishell bible](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit#gid=0) ✝
- @bboisset's [checklist](https://docs.google.com/spreadsheets/d/1ssdLRjY8lJu4GK5IuoA3nf5Plkt7Kx-dNfc5KxvIcXg/edit?usp=sharing) ✅

# Contributors

<p align="center"><br />
<a href="http://github.com/n1kito" alt="n1kito github profile"><img src="https://github.com/n1kito.png?size=60" style="border-radius:50%"/></a>
<a href="http://github.com/vrigaudy" alt="vrigaudy github profile"><img width=60px src="https://media-exp1.licdn.com/dms/image/C4D03AQF3MD862fGCDg/profile-displayphoto-shrink_200_200/0/1597936821648?e=1660176000&v=beta&t=vD5wz5JMTEK5t-LHa2Yfm_T7M41UNDn8F8xKQ8SNRRw" style="border-radius:50%"/></a>

</p>
