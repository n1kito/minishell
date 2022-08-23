#ifndef EXECUTION_H
# define EXECUTION_H

// execution_utils.c

// execution_array_exports.c
int			convert_to_array(t_master *master);
int			convert_commands_to_array(t_master *master);
int			create_command_array(t_master *master, int cmd_count);
int			create_command_subarrays(t_master *master, int cmd_count);
void		populate_nth_command_array(t_master	*master, int command_index);

// execution_array_exports_utils.c
t_tokens	*go_to_nth_segment(int i, t_tokens *token);
int			count_words_in_segment(t_master *master);
int			count_commands(t_tokens	*tokens);

#endif
