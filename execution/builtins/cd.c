/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:01:42 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/26 11:22:35 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	update_env(t_shell *shell, char *old_pwd, char *new_pwd)
{
	add_environment_variable(&(shell->env), "OLDPWD", old_pwd);
	add_environment_variable(&(shell->env), "PWD", new_pwd);
	add_environment_variable(&(shell->dec_env), "OLDPWD", old_pwd);
	add_environment_variable(&(shell->dec_env), "PWD", new_pwd);
}

void	change_path(t_shell *shell)
{
	char	*pwd_value;
	char	*path;

	pwd_value = find_env(shell->env, "PWD");
	if (pwd_value)
	{
		path = getcwd(NULL, 0);
		update_env(shell, pwd_value, path);
		free(path);
		path = NULL;
	}
}

void absolute_pathcase(t_shell *shell, int cmd_num)
{
	char	*home;
	char	**paths;
	char 	*ab_path;

	home = getenv("HOME");
	paths = ft_split(shell->command[cmd_num].cmd_args[1], '~');
	ab_path = ft_strjoin(home, paths[0]);
	if (chdir(ab_path) < 0)
	{
		shell->exit_code = 1;
		perror(shell->command[cmd_num].cmd_args[1]);
	}
	free(paths[0]);
	free(paths);
	free(ab_path);
}

int	ft_cd(t_shell *shell, int cmd_num)
{
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "cd") == 0)
	{
		if (shell->command[cmd_num].cmd_args[1] == NULL) 
		{
				if (find_variable_val(shell->env, "HOME") == NULL)
				{
					shell->exit_code = 1;
					ft_putstr_fd("minishell: ", STDERR_FILENO);
					ft_putstr_fd("cd: ", STDERR_FILENO);
					ft_putstr_fd("HOME not set\n", STDERR_FILENO);
					return (1);
				}
			chdir(getenv("HOME"));
		}
		else if (ft_strcmp(shell->command[cmd_num].cmd_args[1], "~") == 0)
			chdir(getenv("HOME"));
		else if (ft_strcmp(shell->command[cmd_num].cmd_args[1], "-") == 0)
		{
			if (chdir(find_env(shell->env, "OLDPWD")) < 0)
			{
				shell->exit_code = 1;
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd("cd: ", STDERR_FILENO);
				ft_putstr_fd("OLDPWD not set\n", STDERR_FILENO);
				return (1);
			}
			ft_pwd(shell, 0, 1);
		}
		else if (chdir(shell->command[cmd_num].cmd_args[1]) < 0)
		{
			if (ft_strncmp(shell->command[cmd_num].cmd_args[1], "~",1 )== 0)
				absolute_pathcase(shell, cmd_num);
			else
			{	
				shell->exit_code = 1;
				perror(shell->command[cmd_num].cmd_args[1]);
			}
		}
		change_path(shell);
		return (1);
	}
	return (0);
}
