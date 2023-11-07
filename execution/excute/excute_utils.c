/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:36 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/07 19:30:58 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	env_len(t_shell *shell)
{
	t_env	*current;
	int		i;

	i = 0;
	current = shell->env;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	**joind_env(t_shell *shell)
{
	int		len;	
	int		j;
	t_env	*tmp;
	char	**joind;
	char	*joind2;

	tmp = shell->env;
	len = env_len(shell);
	j = 0;
	joind = (char **)malloc(sizeof(char *) * (len + 1));
	while (j < len)
	{
		if (tmp->val)
			joind2 = ft_strjoinfree(ft_strjoin(tmp->cmd, "="), tmp->val, 1);
		else
			joind2 = ft_strdup(tmp->cmd);
		joind[j] = ft_strdupfree(joind2);
		tmp = tmp->next;
		j++;
	}
	joind[j] = NULL;
	return (joind);
}

char	*find_variable_val(t_env *env, char *variable)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->cmd, variable) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

void	close_all_fd(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->number_commands)
	{
		if (shell->command[i].fd[0] != 0)
		{
			close (shell->command[i].fd[0]);
			shell->command[i].fd[0] = 0;
		}
		if (shell->command[i].fd[1] != 0)
		{
			close (shell->command[i].fd[1]);
			shell->command[i].fd[1] = 0;
		}
		i++;
	}
	if (shell->fd_tmp != 0)
	{
		close (shell->fd_tmp);
		shell->fd_tmp = 0;
	}
}

void	fd_herdoc_closer(int *fd)
{
	if (fd[1] != 0)
	{
		close(fd[1]);
		fd[1] = 0;
	}
	if (fd[0] != 0)
	{
		close(fd[0]);
		fd[0] = 0;
	}
}
