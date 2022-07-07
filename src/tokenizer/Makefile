all:
	@gcc -Wall -Wextra -Werror tokenizer*.c -I../../include -o tokenizer

test:
	@./tokenizer_tester.sh

visual:
	@gcc -Wall -Wextra -Werror -D VISUAL tokenizer*.c -I../../include -o tokenizer

.PHONY: all visual test
