# Parsing

The parsing system uses the [shell grammar](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10) to identify the type of each token.

Once a token is delimited, it is categorized as required by the grammar in Shell Grammar.

1. If the token is an operator, the token identifier for that operator shall result. 
2. If the string consists solely of digits and the delimiter character is one of `<` or `>`, the token identifier `IO_NUMBER` shall be returned. 
3. Otherwise, the token identifier `TOKEN` results.



