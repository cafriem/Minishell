/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:34:14 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/12 17:18:33 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	check_stat(char *command)
{
	struct stat	filestat;

	if (stat(command, &filestat) == 0)
	{
		if ((filestat.st_mode & 0170000) == 0040000) 
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(command, STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			exit (127);
		}
		else if (!((filestat.st_mode & S_IRUSR) 
				&& (filestat.st_mode & S_IXUSR)))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(command, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			exit (126);
		}
	}
}

char	*find_path3_2(char *command)
{
	check_stat(command);
	if (access(command, F_OK) == 0)
		return (command);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	exit (127);
}

char	*find_path3(char *command)
{
	char	**path_split;
	int		i;
	char	**cmd;
	char	*absolute_path;

	cmd = ft_split(command, '/');
	i = -1;
	if (getenv("PATH"))
	{
		path_split = ft_split(getenv("PATH"), ':');
		while (path_split[++i])
		{
			absolute_path = 
				ft_strjoinfree(ft_strjoin(path_split[i], "/"), cmd[1], 1);
			if (access(absolute_path, F_OK) == 0)
				return (absolute_path);
			free(absolute_path);
		}
	}
	return (find_path3_2(command));
}

char	*find_path2(char *command)
{
	int		i;
	char	*path;
	char	**path_split;
	char	*tmp_absolute_path;
	char	*absolute_path;

	i = 0;
	path = getenv("PATH");
	if (path)
	{
		path_split = ft_split(path, ':');
		while (path_split[i])
		{
			tmp_absolute_path = ft_strjoin(path_split[i], "/");
			absolute_path = ft_strjoin(tmp_absolute_path, command);
			free(tmp_absolute_path);
			if (access(absolute_path, F_OK) == 0)
				return (absolute_path);
			free(absolute_path);
			i++;
		}
		check_stat(command);
	}
	return (command);
}

char	*find_path(char *command)
{
	if (ft_strrchr(command, '/'))
		return (find_path3(command));
	else
		return (find_path2(command));
	return (command);
}
