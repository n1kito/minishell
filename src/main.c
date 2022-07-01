/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:45:28 by mjallada          #+#    #+#             */
/*   Updated: 2022/07/01 12:38:07 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char	*line;

	line = readline("mini(s)hell -> ");
    // if (line)
    //     add_history(line);
	// free(line);
	printf("%s\n", line);
	return (0);
}
