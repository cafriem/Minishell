/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:48:38 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/12 16:52:26 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_export(t_shell *shell, int cmd_num)
{
	int		i;
	int		valid;

	i = 0;
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "export") == 0)
	{
		if (shell->command[cmd_num].no_args == 2)
		i++;
		if (printing(envp, data, cmd_num, i) != 5)
			return (1);
		while (data[cmd_num].s_cmd[i])
		{
			valid = valid_toadd(&data[cmd_num], i);
			if (valid == 1)
				add_it(data, cmd_num, envp, i);
			else if (valid == 2)
				check_it(envp, data, cmd_num, i);
			i++;
		}
		return (1);
	}
	return (0);
}


void ft_export(t_shell *shell)
{
	t_env *env;
	
	env = shell->dec_env;
	sorting_env(env);
    while (env)
    {
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (env->val != NULL)
		{
			ft_putstr_fd(env->cmd, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(env->val, STDOUT_FILENO);
		}
		else
			ft_putstr_fd(env->cmd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
        env = env->next;  
    }
}

void	sorting_env(t_env *env)
{
	t_env	*tmp;
	char	*temp;

	tmp = env;
	while (env->next)
	{
		if (ft_strcmp(env->cmd, env->next->cmd) < 0)
		{
			temp = ft_strdup(env->next->cmd);
			free(env->next->cmd);
			env->next->cmd= ft_strdup(env->cmd);
			free(env->cmd);
			env->cmd = ft_strdup(temp);
			free(temp);
			env = tmp;
		}
		else 
			env = env->next;
		}
}
