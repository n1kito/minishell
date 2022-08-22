/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:45:28 by mjallada          #+#    #+#             */
/*   Updated: 2022/08/22 07:18:08 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* I imagine this to be the function called for each line read by the prompt. */
// TODO: after execution, the token structure should be freed. Others don't malloc so they
// will just be reinitialised.
int	execute_command(char *command_line, t_master *master)
{
	if (command_line == NULL)
		return (0);
	init_tokenizer_helpers(&master->helpers, command_line);
	if (!tokenizer(command_line, master, &master->helpers)
		|| !parser(&master->tokens)
		|| !expander(master, master->env)
		|| !syntax_checker(master))
		// TODO Here we can add !convert_to_array(master) where we will convert our tokens and env to arrays before launching actual execution;
			return (0);
	// TODO add exec loop or function
	// TODO The master structure should be freed and re-initialized after each execution, to avoid leaks and bad expansions.
	return (1);
}

//int	main(int argc, char **argv, char **env)
int	main(int argc, char **argv)
{
	t_master	master;

	t_env		*env;
	t_env		variable1;
	t_env		variable2;
	t_env		variable3;
	char		name1[5]="USER";
	char		name2[6]="SHELL";
	char		name3[6]="QUOTE";
	char		value1[7]="nikito";
	char		value2[5]="bash";
	char		value3[2]="'";
	
	// temporary env setup
	env = &variable1;
	variable1.name = name1;
	variable1.variable = value1;
	variable1.next = &variable2;
	variable2.name = name2;
	variable2.variable = value2;
	variable2.next = &variable3;
	variable3.name = name3;
	variable3.variable = value3;
	variable3.next = NULL;

	init_master_structure(&master, env);
	if (argc > 2) // TODO change to argc > 1 for the final program. This is just to test.
		return (err_msg("./minishell only needs one argument", 0, &master));
	(void)argc;
	if (!execute_command(argv[1], &master))
	{
		return (free_master(&master, 1));
	}
	printf("\n\033[1;92mSuccess\033[0;39m\n\U00002713 Tokenizer\n\U00002713 Parser\n\U00002713 Expander\n\U00002713 Syntax checker\n\n"); // TODO this will be removed once execution is set up of course.
	return (free_master(&master, 0));
}
