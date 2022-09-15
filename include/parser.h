/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:33:12 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:33:13 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// PARSING TOKEN TYPES
# define TOKEN 0
# define WORD 1
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
void		check_for_invisible_tokens(t_tokens	*token);

// expander_analysers2.c
int			has_solitary_quote(char *token, t_master *master);
int			expansion_name_len(char *expansion);

// expander_quotes_handler.c
void		process_and_remove_quotes(t_tokens *token_node, t_master *master);
void		remove_quotes(t_tokens **token_node, int quot1,
				int quot2, t_master *master);

// expander_utils.c
char		*str_join(char *token1, char *token2);
void		toggle_quoting(int *quoting_status);
int			free_expansions(t_expand **expansions);
int			expand_token(t_tokens *token, t_master *master);
int			expand_line(char **line, t_master *master);

// expander_word_splitting_analyser.c
int			go_to_end_of_expand_name(t_tokens *current_ptr, int i);
int			is_unquoted_expand(t_tokens *token_ptr, int i);

// expander_word_splitting_isolater.c
void		isolate_unquoted_expands(t_tokens *token_ptr, t_master *master);
void		handle_expand_extraction(t_tokens *token_ptr, int *i, t_master *m);
int			follows_unquoted_expand(t_tokens *token_ptr, int i);
void		split_previous_token(t_tokens *token_to_split, int i, t_master *m);

// expander_word_splitting_loops.c
void		isolate_loop(t_master *master);
void		expand_loop(t_master *master);
void		quotes_removal_loop(t_master *master);
void		expanded_token_split_loop(t_master *m, t_tokens **split_tokens);
void		merge_back_loop(t_master *master);

// expander_word_splitting_merger.c
void		merge_token_with_next(t_tokens *current);

// expander_word_splitting_splitter.c
t_tokens	*split_expanded_token(t_tokens **token_ptr, t_master *master);
void		free_divided_token(char **divided_token);
void		tok_splitter(t_tokens *current, t_tokens **split_toks, t_master *m);

// expander_word_splitting_utils.c
void		add_token_ids(t_tokens *token);
void		check_for_quotes(t_tokens *tokens);
int			token_has_blank(char *token);
int			is_only_blanks(char *str);

#endif
