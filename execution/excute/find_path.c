/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:34:14 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/26 10:26:32 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


char *find_path(t_shell *shell, char *command)
{
	char **path_split;
	char *path;
	int i;
	char **cmd;
	char *tmp_absolute_path;
	char *absolute_path;

	path = find_env(shell->env, "PATH");
	if (ft_strrchr(command, '/'))
	{
		cmd = ft_split(command, '/');
		i = 0;
		if (path)
		{
			path_split = ft_split(path, ':');
			while(path_split[i])
			{
				tmp_absolute_path = ft_strjoin(path_split[i], "/");
				absolute_path = ft_strjoin(tmp_absolute_path, cmd[1]);
				free(tmp_absolute_path);
				if (access(absolute_path, F_OK) == 0)
					return (absolute_path);
				free(absolute_path);
				i++;
			}
		}
	}
	else
	{
		i = 0;
		if (path)
		{
			path_split = ft_split(path, ':');
			while(path_split[i])
			{
				tmp_absolute_path = ft_strjoin(path_split[i], "/");
				absolute_path = ft_strjoin(tmp_absolute_path, command);
				free(tmp_absolute_path);
				if (access(absolute_path, F_OK) == 0)
					return (absolute_path);
				free(absolute_path);
				i++;
			}
		}
	}
	return(command);
}
