# Builtins

## `echo` with option -n

## `cd` with only a relative or absolute path

## `pwd` with no options

## `export` + `unset` with no options

Understanding these commands requires an understanding of **Shell Variables & Environment Variables**.

### Shell Variables & Environment Variables

<details><summary><i>(+ click to open)</i></summary>

There are two types of variables:
- `Shell Variables` are not part of the env or export lists, and are only available in the parent shell.
- `Environment Variables` are included in the env or export lists, and can be used in children shells.

#### export  
`export [-fn] [-p] [name[=value]] ` 
Mark each name to be passed to child processes in the environment.  
- [ ] If no names are supplied, or if the -p option is given, a list of names of all exported variables is displayed.
- [ ] If a variable name is followed by =value, the value of the variable is set to value.
- [ ] The return status is zero unless an invalid option is supplied, one of the names is not a valid shell variable name, or -f is supplied with a name that is not a shell function.

#### unset
`unset [-fnv] [name]`  
Remove each variable or function name.
- [ ] If no options are supplied, each name refers to a variable;
- [ ] If there is no variable by that name, a function with that name, if any, is unset.
- [ ] Readonly variables and functions may not be unset.  
- [ ] Some shell variables lose their special behavior if they are unset; such behavior is noted in the description of the individual variables.
- [ ] The return status is zero unless a name is readonly.

-- 

### Implementation

It makes sense to use the main `env` linked list but with an additional boolean `env_var` or `exported` that lets the program know whether each variable is a `Shell` or `Environment` variable.  
It looks like 2 booleans would help, all default variables would be `env_var = 1`, all exported variables would be `exported = 1`. This way we can identify each one to print them accordingly.

**How `export` and `unset` work from my tests**:
- `export` with no arguments prints variables list in alphabetical order; first all default variables, then user-added ones.
  - Special characters come at the end though I only have one in my list.
  - [ ] But not the last variable... Why ? (on MAC)
- I dont't understand the order in which variables are printed with `env`, check with Victor. Though we will parse them in the order in which they appear in the `*env[]` variable so maybe we don't have to worry about it.
- If I export an empty string `export ""` I get an error: ``bash: export: `': not a valid identifier``

### To-do

#### export
- [ ] Update basic env structure with env_var and exported booleans.
  - All initially parsed variables would be "env_var = 1"
- [ ] Code print function called by `export` with no options.
  - Output: `declare -x BASH_SILENCE_DEPRECATION_WARNING="1"`
    - I do not know what the `declare -x` stands for, looked but no luck.
  - If a variable has no value, the output format is: `declare -x lolilol`
- [ ] Check if the name is a correct variable name.
  - The name of a variable can contain only letters (a to z or A to Z), numbers ( 0 to 9) or the underscore character ( _).  
  -  `pou*t=lol` prints `bash: pou*t=lol: command not found` and returns `127`
  - By convention, Unix shell variables will have their names in UPPERCASE.
- [ ] Code function to add variable to linked list, dividing by name & value.
  - If there are several = signs, only the first one acts as a divider: `pouet==lopouet==lololol` will store `pouet` as name and `=lopouet==lololol` as value.
- [ ] If export is called with the += operator, the value is appended to the variable value.
  -  I don't know if I have to deal with this by hand or if this is part of the parser.
- [ ] Handle export called with empty string (returns error)
  - `export ""`

#### unset
- [ ] Code function to remove variable from linked list with `unset`.
- [ ] If `unset` is called on a variable that does not exist, nothing happens, `0` is returned.
- [ ] "The return status is zero unless a name is readonly."
  - What is a readonly variable name ?

### general
- [ ] Code a tester

</details>
