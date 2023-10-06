/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:48:38 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/06 09:33:19 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_export(t_shell *shell, int cmd_num)
{
	int		i;
	char	**str_export;

	i = 1;
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "export") == 0)
	{
		if (shell->command[cmd_num].no_args == 1)
			print_export(shell->env);
		else
		{
			while (i < shell->command[cmd_num].no_args)
			{
				str_export = split_export(shell->command[cmd_num].cmd_args[i]);
				if (check_var(str_export[0]) == 0)
					add_environment_variable(&(shell->env), 
						str_export[0], str_export[1]);
				else
					export_utils(str_export[0]);
				i++;
				free_export(str_export);
			}
		}
		return (1);
	}
	return (0);
}

void	sorting_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	swap_var(env, tmp);
}

void	swap_var(t_env *env, t_env	*tmp)
{
	char	*temp;
	char	*temp_val;

	while (env->next)
	{
		if (ft_strncmp(env->cmd, env->next->cmd, 1) > 0)
		{
			temp = ft_strdup(env->next->cmd);
			temp_val = ft_strdup(env->next->val);
			free(env->next->cmd);
			free(env->next->val);
			env->next->cmd = ft_strdup(env->cmd);
			env->next->val = ft_strdup(env->val);
			free(env->cmd);
			free(env->val);
			env->cmd = ft_strdup(temp);
			env->val = ft_strdup(temp_val);
			free(temp);
			free(temp_val);
			env = tmp;
		}
		else 
			env = env->next;
	}
}

void	print_export(t_env *env)
{
	sorting_env(env);
	while (env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (ft_strlen(env->val) != 0)
		{
			ft_putstr_fd(env->cmd, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(env->val, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		else
			ft_putstr_fd(env->cmd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		env = env->next;
	}
}

int	check_var(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
