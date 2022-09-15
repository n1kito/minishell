/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:32:46 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:32:48 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// STRUCTURES

typedef struct s_tokens
{
	char				*token;
	int					token_type;
	int					token_had_quotes;
	int					was_split;
	int					was_isolated;
	int					token_id;
	int					split_id;
	struct s_tokens		*next;
	struct s_tokens		*previous;
}	t_tokens;

typedef struct s_tokenizer
{
	int					token_start;
	int					position;
	int					quote_match_found;
	int					last_token_end;
	char				*line;
}	t_tokenizer_helpers;

typedef struct s_expand
{
	int					start;
	int					name_start;
	int					name_len;
	int					name_end;
	char				*name;
	char				*value;
	struct s_expand		*next;
}	t_expand;

typedef struct s_command
{
	char				**cmd_array;
	char				*cmd_path;
	int					*fds;
	int					redirections_count;
	int					error_code;
	int					heredoc_fd;
	char				*heredoc_path;
}	t_command;

typedef struct s_master
{
	int					cmd_count;
	t_tokens			*tokens;
	t_tokenizer_helpers	helpers;
	t_expand			*expansions;
	t_command			**commands;
	int					*processes;
	int					**pipes;
	t_env				*env;
	char				**env_for_exec;
	t_tokens			*next_command_start;
	int					printed_error_msg;
	int					ez_err;
	int					tmp_stdin;
	int					tmp_stdout;
	char				*exit_code;
	struct sigaction	*sa;
}	t_master;

// Operator Characters
# define PIPE 124
# define L_CHEVRON 60
# define R_CHEVRON 62
// Quote Characters
//# define BACKSLASH 92
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

// tokenizer.c && tokenizer_for_debugging.c
void		tokenizer(char *line, t_master *master, t_tokenizer_helpers *t);

// tokenizer_utils.c
void		extract_token(t_master *master,
				char *token_start, char *token_end);
void		init_token_values(t_tokens *token);
void		init_tokenizer_helpers(t_tokenizer_helpers *t, char *line);
t_tokens	*get_last_token(t_tokens *tokens_list);

// tokenizer_analysers.c
int			is_operator(char c);
int			is_quote_character(char c);
int			is_blank_char(char c);

// tokenizer_analysers_2.c
int			find_matching_quote(char *str);
int			can_form_operator(char *token_start, char *current_char);
int			follows_open_token(t_tokenizer_helpers *t);
int			follows_word(char *line, int position);

// tokenizer_handlers.c
void		handle_end_of_line(t_tokenizer_helpers *t, t_master *master);
void		handle_quotes(t_tokenizer_helpers *t);
void		handle_blank_char(t_tokenizer_helpers *t, t_master *master);

// tokenizer_handler_2.c
void		start_expansion_token(t_tokenizer_helpers *t);
void		start_operator_token(t_tokenizer_helpers *t, t_master *master);
void		close_operator_token(t_tokenizer_helpers *t, t_master *master);

#endif
