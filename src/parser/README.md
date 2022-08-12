# parsing process

[The Shell Grammar explained](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_100).

## Bash Grammar Symbols

> %token  WORD  
> %token  ASSIGNMENT_WORD  
> %token  NAME  
> %token  NEWLINE  
> %token  IO_NUMBER  

The tokens are classified by their immediate context according to the following rules, applied in order.  
These rules are used to determine what a `token` is. (See the `tokenizer` README for more on how our minishell recognizes tokens. We did our best to follow the bash recognition rules.)  

1. If the token is an operator, the token identifier for that operator shall result.
2. If the string consists solely of digits and the delimiter character is `>` or `<`, the token identifier `IO_NUMBER` shall be returned.
3. Otherwise, the token identifier `TOKEN` results.

How each `TOKEN` is recognized and interpreted depends on context.  
It may be that the same `TOKEN` yields `WORD`, a `NAME`, an `ASSIGNMENT_WORD`, or a reserved word (we don't handle those), depending of the context.  

## What's next ?

At this stage, we've identified whether a token is an `OPERATOR` (and identified the actual operator), an `IO_NUMBER`, or *something else*.

~~We will now use the *shell grammar rules* below to analyse context and identify what each of the remaining tokens is.~~

<details>
<summary> <i>(+ click to see Shell Grammar Rules)</i> </summary>

## Shell grammar rules

1. `[Command Name]`
   - [ ] OK
    - When the `TOKEN` is exactly a reserved word, the token identifier for that reserved word shall result.
    - Otherwise, the token `WORD` shall be returned.
    - Also, if the parser is in any state where only a reserved word could be the next correct token, proceed as above.
    - > Rule 1 is not directly referenced in the grammar, but is referred to by other rules, or applies globally.
2. `[Redirection to or from filename]`
   - [ ] OK
    - The expansions specified in [Redirection](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07) shall occur.
      - [ ] I have no idea what this means I can't find the correct section.
    - As specified there (??), exactly one field can result (or the result is unspecified), and there are additional requirements on pathname expansion.
3. `[Redirection from here-document]`
   - [ ] OK
   - Quote removal shall be applied to the word to determine the delimiter.
4. `[Case statement termination]` (**NOT HANDLED**)
   - [ ] OK
   - When the `TOKEN` is exactly the reserved word `esac`, the token identifier for `esac` shall result. Otherwise, the token `WORD` shall be returned.
5. `[NAME in for]` (**NOT HANDLED**)
   - [ ] OK
   - When the `TOKEN` meets the requirements for a name, the token identifier `NAME` shall result. Otherwise, the token `WORD` shall be returned.
   - Name requirements: In the shell command language, a word consisting solely of underscores, digits, and alphabetics from the portable character set. The first character of a name is not a digit.
   - **We don't handle for statements.**
6. `[Third word of for and case]` (**NOT HANDLED**)
   - [ ] OK
   - We don't handle this.
7. `[Assigment preceding command name]`  
   - [ ] OK
   `a.` [When the first word]
      - If the `TOKEN` does not contain the character `=`, `Rule 1` is applied.
      - Otherwise, `Rule 7b` is applied.  
   
   `b.` [Not the first word]
      - If the `TOKEN` contains an unquoted `=` character that is not part of an embedded parameter expansion, command substitution, or arithmetic expansion construct:
        - If the `TOKEN` begins with `=`, then `Rule 1` is applied.
        - If all the characters in the `TOKEN` preceding the first such `=` form a valid [name](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_235), the token `ASSIGNMENT_WORD` shall be returned.
          - Otherwise, it is unspecified whether `Rule 1` is applied or `ASSIGNMENT_WORD` is returned. (ah bah super merci bash)
      - Otherwise, rule 1 shall be applied.
    Assignment to the name within a returned `ASSIGNMENT_WORD` token shall occur as specified in [Simple Commands](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_09_01).
8. `[NAME in function]`
   - [ ] OK
   - When the `TOKEN` is exactly a reserved word (we don't care for those), the token identifier for that reserved word shall result.
   - Otherwise, then the `TOKEN` meets the requirements for a name, the token identifier `NAME` shall result.
   - Otherwise, `Rule 7` applies.
9. `[Body of function]`
   - [ ] OK
   - We don't handle functions.
   - Word expansion and assignment shall never occur, even when required by the rules above, when this rule is being parsed.
   - Each `TOKEN` that might either be expanded or have assignment applied to it shall instead be returned as a single `WORD` consisting only of characters that are exactly the token described in [Token Recognition](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03).


</details>

Actually, **we will not**, because they treat a bunch of cases that do not concern us for this project and that complicates everything.

Instead, for each node, if it has been found that it is neither an `operator` or an `io_number` (I used this step to identify filenames as well), we will do the following:
   1. If the token being checked is not the first token and the previous token is of type `HERE_DOC`, current token is assigned `DELIMITER` type.
   2. Else if token being checked is either the first in line OR the previous token is of type `PIPE`, `IO_NUMBER`, `DELIMITER` or `FILE_NAME`, then token is assigned `COMMAND_NAME` type. 
   3. Else if token being checked is ot type `TOKEN` (meaning has not been previously asssigned), then it is assigned `WORD` type.

## Syntax Checking

Here are the syntax rules we will implement in our `syntax_checker` function.

There is an **error** if:
   - A `PIPE` token is either the first token, the last token, or is before or after another pipe.
   - A `HERE_DOC` token is not followed by a `DELIMITER` token.
   - A `REDIRECT_TO`, `REDIRECT_FROM` or `APPEND` token is not followed by either an `IO_NUMBER` or a `FILENAME` token.

## Quotes handling & variable replacement

**Quotes**
- When a `'` (single quotes) is found
   - We look for a matching one.
      - If one is found, we delete them without treating anything inside.
      - If not, we move to the next char.
- When a `"` (double quote)
   - We look for a matching one.
      - If found, we delete them but expand any variable found inside. Single quotes are not touched.
      - If not, we move on the next char.

# to-do

- [ ] Take care of syntax checker.
   - Do I populate some useful variables at this stage, like the number of pipes found in the command line ?
       - I think this should be done after, in another analyser function so it's more clear. Maybe even in the function that stores necessary arguments in arrays to be used by execve.
- [ ] Do the quote and variable replacements.
