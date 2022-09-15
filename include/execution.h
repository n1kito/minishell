/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:46:28 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:46:29 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// execution.c
int			exec_loop(t_master *master);
void		launch_exec(t_master *master, int i);
int			process_open_heredoc(t_master *master, int i);

// execution_array_exports.c
void		generate_command_structure(t_master *master);
void		create_command_structures(t_master *master, int cmd_count);
void		populate_command_structures(t_master *master, int cmd_count);
void		populate_nth_command_structure(t_master	*master, int command_index);

// execution_array_exports_utils.c
t_tokens	*go_to_nth_segment(int i, t_tokens *token);
int			count_words_in_segment(t_master *master);
int			count_commands(t_tokens	*tokens);
int			count_files_in_segment(t_master *master, int segment_index);

// execution_builtins.c
int			execute_single_builtin(t_master *master);
int			run_builtin(t_master *master, int cmd_index);
void		set_builtin_redir(int infile, int outfile, t_master *master);
void		reset_builtin_redir(int infile, int outfile, t_master *master);

// execution_command_path_utils.c
int			assign_command_paths(t_master *master);
int			get_cmd_path(char **cmd_path, char *command, char **paths,
				t_master *master);
char		*get_path_variable(t_env *env);
void		free_paths(char **paths);

// execution_file_descriptors.c
void		allocate_file_descriptors(t_master *master);
int			open_file_descriptors(t_master *master, int i);
int			check_input_file(t_master *master, t_tokens *current, int i, int j);
int			check_output_file(t_master *m, t_tokens *current, int i, int j);

// execution_loop_utils.c
int			last_input_fd(t_master *master, int i);
int			last_output_fd(t_master *master, int i);
void		plug_pipes(t_master *master, int i, int infile, int outfile);

// execution_loop_utils_2.c
void		process_waiter(t_master *master);

// execution_heredoc_handling.c
int			exit_heredoc(t_master *master, char *line, int cmd_index,
				int return_code);
void		read_heredoc(t_tokens *heredoc_token, t_command *command_node,
				t_master *master, int i);
void		print_heredoc_warning(char *line, int cmd_index, char *delimiter,
				t_master *master);

// execution_heredoc_handling_2.c
int			setup_heredocs(t_master *master);
int			heredoc_process(t_master *master, t_tokens *tokens, int i);
void		expand_heredoc_line(char **line, t_master *master, int cmd_index,
				int tmp_minishexit);
int			log_heredoc_expansions(char *line, int cmd_index,
				t_master *master);

// execution_heredoc_handling_utils.c
void		set_heredoc_path(t_master *master, int i);
void		open_heredoc(t_master *master, int i);

void		check_if_heredoc_should_expand(t_tokens *delimiter,
				int *should_expand);
int			heredoc_file_access(t_master *master, int cmd_index);
int			unlink_heredocs(t_master *master);

// execution_pipe_utils.c
void		plug_first_cmd(t_master *master, int i, int infile, int outfile);
void		plug_middle_cmd(t_master *master, int i, int infile, int outfile);
void		plug_last_cmd(t_master *master, int i, int infile, int outfile);

// execution_setup.c
int			heredoc_found(t_master *master);
void		prep_execution_resources(t_master *master);
void		setup_process_array(t_master *master);
void		setup_pipes(t_master *master);

// execution_utils.c
void		close_pipes_and_files(t_master *master, int i);
void		close_pipes(t_master *master);
void		close_files(t_master *master, int i);
int			is_builtin_function(char *name);

//
int			command_error_check(t_command *command, t_master *master);

#endif
