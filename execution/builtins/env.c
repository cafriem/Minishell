/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:48:59 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/12 16:26:25 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_env_exc(t_shell *shell, int cmd_num)
{
	t_env	*env;

	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "env") == 0)
	{
		env = shell->env;
		while (env)
		{
			if (ft_strlen(env->val) != 0)
			{
				ft_putstr_fd(env->cmd, STDOUT_FILENO);
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putstr_fd(env->val, STDOUT_FILENO);
				ft_putchar_fd('\n', STDOUT_FILENO);
			}
			env = env->next;
		}
		return (1);
	}
	return (0);
}

void	update_environment_variable(t_env *env, char *variable, char *new_value)
{
	if (ft_strlen(new_value) != 0)
	{
		while (env != NULL)
		{
			if (strcmp(env->cmd, variable) == 0)
			{
				free(env->val);
				env->val = strdup(new_value); 
				return ;
			}
			env = env->next;
		}
	}
}

void	add_environment_variable(t_env **env, char *variable, char *value)
{
	t_env	*new_env;
	t_env	*current;

	if (environment_variable_exists(*env, variable))
	{
		update_environment_variable(*env, variable, value);
		return ;
	}
	else
	{
		new_env = (t_env *)malloc(sizeof(t_env));
		new_env->cmd = ft_strdup(variable);
		new_env->val = ft_strdup(value);
		new_env->next = NULL;
		if (*env == NULL)
			*env = new_env;
		else
		{
			current = *env;
			while (current->next != NULL)
				current = current->next;
			current->next = new_env;
		}
	}
}

int	environment_variable_exists(t_env *env, char *variable)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (strcmp(current->cmd, variable) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

char	*find_env(t_env *env, char *variable)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (strcmp(current->cmd, variable) == 0)
		{
			return (current->val);
		}
		current = current->next;
	}
	return (NULL);
}
