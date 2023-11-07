/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 08:53:19 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/07 19:30:58 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_unset(t_shell *shell, int cmd_num)
{
	int	i;

	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "unset") == 0)
	{
		i = 1;
		while (i < shell->command[cmd_num].no_args)
		{
			if (ft_strchr(shell->command[cmd_num].cmd_args[i], '='))
				return (unset_utils(shell,
						shell->command[cmd_num].cmd_args[i]));
			else if (environment_variable_exists(shell->env,
					shell->command[cmd_num].cmd_args[i]))
				remove_environment_variable(&(shell->env),
					shell->command[cmd_num].cmd_args[i]);
			i++;
		}
	}
	return (0);
}

void	remove_environment_variable(t_env **env, char *variable)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->cmd, variable) == 0)
		{
			if (prev == NULL)
				*env = current->next;
			else
				prev->next = current->next;
			free(current->cmd);
			free(current->val);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	unset_utils(t_shell *shell, char *var)
{
	shell->exit_code = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("unset: ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	return (1);
}
