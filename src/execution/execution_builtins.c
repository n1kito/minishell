#include "minishell.h"

/* Takes care of setting up fds/redirections for builtin functions
 * that need to be executed in the parent process and outside of a
 * fork. The FDs are reset after the function has been called. */
int	execute_single_builtin(t_master *master)
{
	int	in_redir;
	int	out_redir;
	//
	// TODO check what happens if there is an error opening file descriptors with single builtin	
	if (!open_file_descriptors(master, 0))
		return (1);
	in_redir = last_input_fd(master, 0);
	out_redir = last_output_fd(master, 0);
	//TODO proteger tmp_stdin et tmp_stdout
	// et les set dans le setup_sing_builtin en passant les pointeurs sur int
	set_builtin_redir(in_redir, out_redir, master);
	run_builtin(master, 0);
	reset_builtin_redir(in_redir, out_redir, master);
	close_files(master, 0);
	return (1);
}

/* Checks the name of the builtin and launches the corresponding function. */
int	run_builtin(t_master *master, int cmd_index)
{
	char	*command;
	char	**arguments;

	command = master->commands[cmd_index]->cmd_array[0];
	arguments = master->commands[cmd_index]->cmd_array;
	if ((ft_strcmp(command, "export") == 0
			&& !ft_export(&master->env, arguments))
		|| (ft_strcmp(command, "unset") == 0
			&& !ft_unset(&master->env, arguments))
		|| (ft_strcmp(command, "echo") == 0
			&& !ft_echo(arguments))
		|| (ft_strcmp(command, "exit") == 0
			&& !ft_exit(master, cmd_index))
		|| (ft_strcmp(command, "env") == 0
			&& !ft_env(master->env))
		|| (ft_strcmp(command, "pwd") == 0
			&& !ft_pwd())
		|| (ft_strcmp(command, "cd") == 0
			&& !ft_cd(arguments, master->env)))
		return (0);
	return (1);
}

/* Sets up FDs for file/heredoc redirections with single builtins. */
void	set_builtin_redir(int infile, int outfile, t_master *master)
{
	if (infile)
	{
		master->tmp_stdin = dup(STDIN_FILENO);
		if (master->tmp_stdin == -1
			|| dup2(infile, STDIN_FILENO) == -1)
			exit(err_msg("dup/dup2 error [set_builtin_redir()[1]", 1, master)
				&& free_master(master, 1));
	}
	if (outfile)
	{
		master->tmp_stdout = dup(STDOUT_FILENO);
		if (master->tmp_stdout == -1
			|| dup2(outfile, STDOUT_FILENO) == -1)
			exit(err_msg("dup/dup2 error [set_builtin_redir()[2]", 1, master)
				&& free_master(master, 1));
	}
}

/* Resets FDs after the single builtin function has been used. */
void	reset_builtin_redir(int infile, int outfile, t_master *master)
{
	if (infile)
	{
		if (dup2(master->tmp_stdin, STDIN_FILENO) == -1
			|| close(master->tmp_stdin) == -1)
			exit(err_msg("dup/dup2 error [reset_builtin_redir()[1]", 1, master)
				&& free_master(master, 1));
	}
	if (outfile)
	{
		if (dup2(master->tmp_stdout, STDOUT_FILENO) == -1
			|| close(master->tmp_stdout) == -1)
			exit(err_msg("dup/dup2 error [reset_builtin_redir()[2]", 1, master)
				&& free_master(master, 1));
	}
}
