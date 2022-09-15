/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:50:50 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 11:57:20 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// PARSING TOKEN TYPES
# define TOKEN 0 // default type assigned to all new tokenss
# define WORD 1 // pas encore pige la difference entre word et name mais bon
# define COMMAND_NAME 2
# define PIPE_TOKEN 3
# define REDIRECT_FROM 4
# define REDIRECT_TO 5
# define APPEND 6
# define FILE_NAME 7
# define HERE_DOC 8
# define DELIMITER 9
# define INVISIBLE 10

// parser.c
void		parser(t_tokens **tokens);
int			is_file_name_token(t_tokens *token);
int			is_operator_token(t_tokens *tokens);
void		print_parsed_tokens(t_tokens *tokens);

// parser_identify_tokens.c
void		identify_token_type(t_tokens *token);

// parser_syntax_checker.c
int			syntax_checker(t_tokens *tokens, t_master *master, int err);

// expander.c
void		expander(t_master *master);

// expander_analysers.c
char		*search_env(t_env *env, char *name, int name_len);
void		log_expansions(char *token, t_master *master);
void		expand_exit_code(t_master *master, t_expand *new_expand);
int			add_exp_node(t_master *master, char *token, int i);

// expander_analysers2.c
int			has_solitary_quote(char *token, t_master *master);
int			expansion_name_len(char *expansion);

// expander_line_expander.c
int			expand_line(char **line, t_master *master);

// expander_quote_handling.c
void		quotes_remover(t_master *master);
void		check_for_quotes(t_tokens *tokens);
void		process_and_remove_quotes(t_tokens *token_node, t_master *master);
void		remove_quotes(t_tokens **token_node, int first_quote,
				int second_quote, t_master *master);

// expander_utils.c
char		*str_join(char *token1, char *token2);
void		toggle_quoting(int *quoting_status);
int			count_expands(t_expand *expansions);
int			free_expansions(t_expand **expansions);
int			expand_token(t_tokens *token, t_master *master);

// expander_utils2.c
void		check_for_invisible_tokens(t_tokens	*token);
void		add_token_ids(t_tokens *token);

// expander_word_splitting.c
void		expand_isolater(t_master *master);
void		token_expander(t_master *master);
void		expanded_token_splitter(t_master *master);
void		token_merger(t_master *master);
void		split_token(t_tokens *current, t_master *master);

// expander_word_splitting_analysers.c
int			token_has_blank(char *token);
int			is_only_blanks(char *str);
int			follows_unquoted_expand(t_tokens *token_ptr, int i);
int			is_unquoted_expand(t_tokens *token_ptr, int i);

// expander_word_splitting_handlers.c
void		merge_token_with_next(t_tokens *current, t_master *master);
void		split_previous_token(t_tokens *token_to_split,
				int position, t_master *master);
void		isolate_unquoted_expands(t_tokens *token_ptr, t_master *master);
t_tokens	*split_expanded_token(t_tokens **token_ptr, t_master *master);
void		isolate_expand(t_tokens *token_ptr, int *i, t_master *master);

// expander_word_splitting_utils.c
t_tokens	*get_next_unsplitted_token(t_tokens *current);
int			get_next_non_blank_char(char *str);
void		set_tokens_as_words(t_tokens *token);
int			go_to_end_of_expand_name(t_tokens *current_ptr, int i);
void		free_split_tokens(char **divided_token);

#endif
