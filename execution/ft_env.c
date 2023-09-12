/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:48:59 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/12 18:30:45 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void update_environment_variable(t_env *env, const char *variable, const char *new_value)
{
    while (env != NULL)
    {
        if (strcmp(env->cmd, variable) == 0)
        {
            free(env->val);
            env->val = strdup(new_value); 
            return;
        }
        env = env->next;
    }
}

void add_environment_variable(t_env **env, const char *variable, const char *value)
{
	if (environment_variable_exists(*env, variable))
	{
		update_environment_variable(*env, variable, value);
		return ;
	}
	else
	{
		t_env *new_env = (t_env *)malloc(sizeof(t_env));
		new_env->cmd = ft_strdup(variable);
		new_env->val = ft_strdup(value);
		new_env->next = NULL;
		if (*env == NULL)
		{
			*env = new_env;
		}
		else
		{
			t_env *current = *env;
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = new_env;
		}
	}
}

void remove_environment_variable(t_env **env, const char *variable)
{
    t_env *current = *env;
    t_env *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->cmd, variable) == 0)
        {
            if (prev == NULL)
                *env = current->next;
             else
                prev->next = current->next;
            free(current->cmd);
            free(current->val);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int environment_variable_exists(t_env *env, const char *variable)
{
    t_env *current = env;
    while (current != NULL)
    {
        if (strcmp(current->cmd, variable) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int	ft_env_exc(t_shell *shell, int cmd_num)
{
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "env") == 0)
	{
		t_env *env = shell->env;
		// sorting_env(env);
		while (env)
		{
			ft_putstr_fd(env->cmd, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(env->val, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
        	env = env->next;
		}
		return (1);
	}
	return (0);
}

// void	sorting_env(t_env *env)
// {
// 	t_env	*tmp;
// 	char	*temp;
// 	char	*temp_val;

// 	tmp = env;
// 	while (env->next)
// 	{
// 		if (ft_strcmp(env->cmd, env->next->cmd) < 0)
// 		{
// 			temp = ft_strdup(env->next->cmd);
// 			temp_val = ft_strdup(env->next->val)
// 			free(env->next->cmd);
// 			free(env->next->val);
// 			env->next->cmd = ft_strdup(env->cmd);
// 			free(env->cmd);
// 			env->cmd = ft_strdup(temp);
// 			free(temp);
// 			env = tmp;
// 		}
// 		else 
// 			env = env->next;
// 		}
// }

char *find_env(t_env *env, const char *variable)
{
    t_env *current = env;
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