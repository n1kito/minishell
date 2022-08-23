#ifndef EXECUTION_H
# define EXECUTION_H

// execution.c
int			execute_commands(t_master *master);

// execution_array_exports.c
int			prep_execution_resources(t_master *master);
int			generate_command_structure(t_master *master);
int			create_command_structures(t_master *master, int cmd_count);
int			populate_command_structures(t_master *master, int cmd_count);
void		populate_nth_command_structure(t_master	*master, int command_index);

// execution_array_exports_utils.c
t_tokens	*go_to_nth_segment(int i, t_tokens *token);
int			count_words_in_segment(t_master *master);
int			count_commands(t_tokens	*tokens);

#endif
