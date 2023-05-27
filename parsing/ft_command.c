/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:34 by cafriem           #+#    #+#             */
/*   Updated: 2023/05/26 10:00:56 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	command_input(void)
// {
// 	int	counter;

// 	counter = 0;
// 	if (ft_strncmp(parse->pipe[counter], "cd ", 3) == 1
// 		|| ft_strncmp(parse->pipe[counter], "cd\0", 3) == 1)
// 	{
// 		shell->command[counter]->cmd_args = ft_calloc(2, sizeof(char *));
// 		shell->command[counter]->cmd_args[0] = ft_strdup("cd");
// 		shell->command[counter]->cmd_args[1] = ft_substr(parse->pipe[counter], 3, ft_operfinder(parse->pipe[counter]));
// 	}
// }