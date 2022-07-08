# [Token Recognition](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03)

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
- [x] (4) If the current character is <backslash>, single-quote, or double-quote and it is not quoted, it shall affect quoting for subsequent characters up to the end of the quoted text.
    - The various quoting mechanisms are the escape character ` \ `, single-quotes `'`, and double-quotes `"`.
    - During token recognition no substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input (except for <newline> joining), unmodified, **including any embedded or enclosing quotes or substitution operators**, between the <quotation-mark> and the end of the quoted text.
    - The token shall not be delimited by the end of the quoted field.
      - -> I did not do this.
    - I don't think we need to handle the `\ `, subject says:
      - > Not interpret unclosed quotes or special characters which are not required by the suject such as \ (backslash) or ; (semicolon)..
    - Since we don't interpret unclosed quotes, I think if unclosed quote is found we need to treat it as regular text.
    - But what about when I find quotes with nothing inside ? I don't think I should add a token then.
      - [x] That's what I ended up doing.
    - [More about UNIX Shell Quoting](https://rg1-teaching.mpi-inf.mpg.de/unixffb-ss98/quoting-guide.html)
- [ ] (5) If the current character is an unquoted `$` or ``` (accent grave), the shell shall identify the start of any candidates for parameter expansion (Parameter Expansion), command substitution (Command Substitution), or arithmetic expansion (Arithmetic Expansion) from their introductory unquoted character sequences: '$' or "${", "$(" or '`', and "$((", respectively. The shell shall read sufficient input to determine the end of the unit to be expanded (as explained in the cited sections). While processing the characters, if instances of expansions or quoting are found nested within the substitution, the shell shall recursively process them in the manner specified for the construct that is found. The characters found from the beginning of the substitution to its end, allowing for any recursion necessary to recognize embedded constructs, shall be included unmodified in the result token, including any embedded or enclosing substitution operators or quotes. The token shall not be delimited by the end of the substitution.
    - I don't think we need to handle the accent grave, subject says:
    - > Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- [x] (6) If the current character is not quoted and can be used as the first character of a new operator, the current token (if any) shall be delimited. The current character shall be used as the beginning of the next (operator) token.
- [x] (7) If the current character is an unquoted `<blank>`, any token containing the previous character is delimited and the current character shall be discarded.
  - In the POSIX shell, a blank is either a tab or space. <sup>[(source)](https://www.ibm.com/docs/en/aix/7.1?topic=concepts-shells-terminology)</sup>
- [x] (8) If the previous character was part of a word, the current character shall be appended to that word.
- [x] (9) ~~If the current character is a '#', it and all subsequent characters up to, but excluding, the next <newline> shall be discarded as a comment. The <newline> that ends the line is not considered part of the comment.~~
- [x] (10) The current character is used as the start of a new word.

Once a token is delimited, it is categorized as required by the grammar in Shell Grammar.
