/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:45:28 by mjallada          #+#    #+#             */
/*   Updated: 2022/08/19 16:17:51 by mjallada         ###   ########.fr       */
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
		|| !expander(&master->tokens, master->env)
		|| !syntax_checker(master->tokens))
			return (0);
	return (1);
}

//int	main(int argc, char **argv, char **env)
int	main(int argc, char **argv)
{
	t_master	master;

	t_env		*env;
	t_env		variable1;
	t_env		variable2;
	char		name1[5]="USER";
	char		name2[6]="SHELL";
	char		value1[7]="nikito";
	char		value2[5]="bash";
	
	// temporary env setup
	env = &variable1;
	variable1.name = name1;
	variable1.variable = value1;
	variable1.next = &variable2;
	variable2.name = name2;
	variable2.variable = value2;
	variable2.next = NULL;

	// this is for the final program. I'm using argv[1] to read command lines for now.
	//if (argc > 1)
		//return (write(2, "Error: too many arguments.\n", 27)); // TODO code proper error printing function that returns code.
	(void)argc;
	init_master_structure(&master, env);
	if (!execute_command(argv[1], &master))
	{
		return (free_master(&master, 1));
	}
	printf("Everything went OK.\n");
	return (free_master(&master, 0));
}
