<h1 align="center">mini(s)hell 🔥</h1>
<p align="center">
<img src="img/hell.gif" width="200px" alt="elmo hell gif"><br />
Our work on the 42Born2Code <b>minishell</b> project.<br /><br />
</p>

> This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.

# To-do

- [ ] Apprendre à utiliser un repo git en collaboration

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

* https://www.gnu.org/software/bash/manual/bash.html
* https://pubs.opengroup.org/onlinepubs/9699919799/
* https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
* https://catonmat.net/bash-one-liners-explained-part-three
* https://brennan.io/2015/01/16/write-a-shell-in-c/

# Resources

- @vietdu91's [project](https://github.com/vietdu91/42_minishell)  
    - And his [minishell bible](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit#gid=0) ✝
- @bboisset's [checklist](https://docs.google.com/spreadsheets/d/1ssdLRjY8lJu4GK5IuoA3nf5Plkt7Kx-dNfc5KxvIcXg/edit?usp=sharing) ✅

# Contributors

<p align="center"><br />
<a href="http://github.com/n1kito" alt="n1kito github profile"><img src="https://github.com/n1kito.png?size=60" style="border-radius:50%"/></a>
<a href="http://github.com/vrigaudy" alt="vrigaudy github profile"><img width=60px src="https://media-exp1.licdn.com/dms/image/C4D03AQF3MD862fGCDg/profile-displayphoto-shrink_200_200/0/1597936821648?e=1660176000&v=beta&t=vD5wz5JMTEK5t-LHa2Yfm_T7M41UNDn8F8xKQ8SNRRw" style="border-radius:50%"/></a>

</p>
