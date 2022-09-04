#include "minishell.h"

void	plug_first_cmd(t_master *master, int i, int infile, int outfile)
{
	if (infile)
		if (dup2(infile, STDIN_FILENO) == -1)
			exit(err_msg("dup2 failed [plug_first_command()][1]", 1, master)
				&& free_master(master, 1));
	if (outfile)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
			exit(err_msg("dup2 failed [plug_first_command()][2]", 1, master)
				&& free_master(master, 1));
	}
	else
		if (master->cmd_count > 1)
			if (dup2(master->pipes[i][1], STDOUT_FILENO) == -1)
				exit(err_msg("dup2 failed [plug_first_ccommand()][3]",
						1, master) && free_master(master, 1));
}

void	plug_middle_cmd(t_master *master, int i, int infile, int outfile)
{
	if (infile)
	{
		if (dup2(infile, STDIN_FILENO) == -1)
			exit(err_msg("dup2 failed [plug_middle_command()][1]", 1, master)
				&& free_master(master, 1));
	}
	else
		if (dup2(master->pipes[i - 1][0], STDIN_FILENO) == -1)
			exit(err_msg("dup2 failed [plug_middle_command()][2]", 1, master)
				&& free_master(master, 1));
	if (outfile)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
			exit(err_msg("dup2 failed [plug_middle_command()][3]", 1, master)
				&& free_master(master, 1));
	}
	else
		if (dup2(master->pipes[i][1], STDOUT_FILENO) == -1)
			exit(err_msg("dup2 failed [plug_middle_command()][4]", 1, master)
				&& free_master(master, 1));
}

void	plug_last_cmd(t_master *master, int i, int infile, int outfile)
{
	if (infile)
	{
		if (dup2(infile, STDIN_FILENO) == -1)
			exit(err_msg("dup2 failed [plug_last_command()][1]", 1, master)
				&& free_master(master, 1));
	}
	else
		if (dup2(master->pipes[i - 1][0], STDIN_FILENO) == -1)
			exit(err_msg("dup2 failed [plug_last_command()][2]", 1, master)
				&& free_master(master, 1));
	if (outfile)
		if (dup2(outfile, STDOUT_FILENO) == -1)
			exit(err_msg("dup2 failed [plug_last_command()][3]", 1, master)
				&& free_master(master, 1));
}
