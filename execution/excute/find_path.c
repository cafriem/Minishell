/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:34:14 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/02 13:59:44 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	check_stat(t_shell *shell, char *command)
{
	struct stat	filestat;

	if (stat(command, &filestat) == 0 && ft_strrchr(command, '/'))
	{
		if ((filestat.st_mode & 0170000) == 0040000)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(command, STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			free_exit_child(shell);
			exit (126);
		}
		else if (!((filestat.st_mode & S_IRUSR)
				&& (filestat.st_mode & S_IXUSR)))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(command, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			free_exit_child(shell);
			exit (126);
		}
	}
}

char	*find_path3_2(t_shell *shell, char *command)
{
	check_stat(shell, command);
	if (access(command, F_OK) == 0)
		return (command);
	if (ft_strrchr(command, '/'))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_exit_child(shell);
		exit (127);
	}
	return (command);
}

char	*find_path3(t_shell *shell, char *command, char **cmd)
{
	char	**path_split;
	int		i;
	char	*absolute_path;

	i = -1;
	path_split = ft_split(getenv("PATH"), ':');
	if (getenv("PATH"))
	{
		while (path_split[++i])
		{
			absolute_path
				= ft_strjoinfree(ft_strjoin(path_split[i], "/"), cmd[1], 1);
			if (absolute_path != NULL)
			{
				if (access(absolute_path, F_OK) == 0)
				{
					path_free_split(cmd, path_split);
					return (absolute_path);
				}
			}
			free(absolute_path);
		}
	}
	path_free_split(cmd, path_split);
	return (find_path3_2(shell, command));
}

char	*find_path2(t_shell *shell, char *command, char *path)
{
	int		i;
	char	**path_split;
	char	*absolute_path;

	i = 0;
	if (path)
	{
		path_split = ft_split(path, ':');
		while (path_split[i++])
		{
			absolute_path
				= ft_strjoinfree(ft_strjoin(path_split[i], "/"), command, 1);
			if (absolute_path)
			{
				if (access(absolute_path, F_OK) == 0)
				{
					ft_freesplit(path_split);
					return (absolute_path);
				}
			}
			free(absolute_path);
		}
		ft_freesplit(path_split);
	}
	return (find_path3_2(shell, command));
}

char	*find_path(t_shell *shell, char *command)
{
	char	*path;
	char	**cmd;

	if (ft_strrchr(command, '/'))
	{
		cmd = ft_split(command, '/');
		return (find_path3(shell, command, cmd));
	}
	else
	{
		path = find_variable_val(shell->env, "PATH");
		return (find_path2(shell, command, path));
	}
	return (command);
}
