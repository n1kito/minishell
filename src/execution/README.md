# Execution

I need to add some documentation here.
[check this out](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_100)

Processing of redirections and heredocs:
- It seems like `HERE_DOCS` are all processed first, but each command segment created its own `HERE_DOC` temporary file to output to and used as input.
  - This means that several `HERE_DOCS` in the same command segment will use the lastest input, but if there were also `HERE_DOCS` in an earlier command segment, the input will be intact.
  - Since `HERE_DOCS` are processed first, a file that is `chmod 0` will not keep the `HERE_DOCS` from being processed, even if it's the first redirection in the command line.
      - When the regular redirections are processed, once an error with the files is found, the redirections for that process stop. So if a file neede to be created after that, it just won't be. If a file was to be created before accessing the error, it will be created but the command will not be ran for that segment.
