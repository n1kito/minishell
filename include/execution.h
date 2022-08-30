#ifndef EXECUTION_H
# define EXECUTION_H

// execution.c
int			exec_loop(t_master *master);

// execution_array_exports.c
int			generate_command_structure(t_master *master);
int			create_command_structures(t_master *master, int cmd_count);
int			populate_command_structures(t_master *master, int cmd_count);
void		populate_nth_command_structure(t_master	*master, int command_index);

// execution_array_exports_utils.c
t_tokens	*go_to_nth_segment(int i, t_tokens *token);
int			count_words_in_segment(t_master *master);
int			count_commands(t_tokens	*tokens);
int			count_files_in_segment(t_master *master, int segment_index);

// execution_command_path_utils.c
int			assign_command_paths(t_master *master);
int			get_cmd_path(char **cmd_path, char *command, char **paths, t_master *master);
char		*get_path_variable(t_env *env);

// execution_file_descriptors.c
int			setup_file_descriptors(t_master *master);
int			allocate_file_descriptors(t_master *master);
int			open_file_descriptors(t_master *master, int i);

// execution_heredoc_handling.c
int			setup_heredocs(t_master *master);
int			read_heredoc(t_tokens *heredoc_token, t_command *command_node, t_master *master);
int			expand_heredoc_line(char **line, t_master *master);
int			log_heredoc_expansions(char *line, t_master *master);

// execution_setup.c
int			prep_execution_resources(t_master *master);
int			setup_process_array(t_master *master);

// execution_utils.c
int			is_builtin_function(char *name);

#endif
