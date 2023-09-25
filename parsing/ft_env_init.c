/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:01:09 by smokashi          #+#    #+#             */
/*   Updated: 2023/09/25 16:42:48 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	ft_env_val_long(t_env *nenv, char **string)
{
	int	i;

	i = 2;
	while (string[i])
	{
		nenv->val = ft_strjoinfree(nenv->val, "=", 1);
		nenv->val = ft_strjoinfree(nenv->val, string[i], 1);
		i++;
	}
}

void	ft_env_loop(t_env *env, char *tenv[], int c)
{
	char	**string;
	t_env	*nenv;

	if (tenv[c])
	{
		nenv = ft_calloc(1, sizeof(t_env));
		env->next = nenv;
		string = ft_split(tenv[c], '=');
		nenv->cmd = ft_strdup(string[0]);
		if (ft_strcmp(string[0], "SHLVL") == 0)
		{
			string[1][0] += 1;
		}
		if (string[1])
		{
			printf("%s=", string[0]);
			printf("%s\n", string[1]);
			nenv->val = ft_strdup(string[1]);
		}
		if (ft_double_pointer_counter2(string) > 1)
			ft_env_val_long(nenv, string);
		ft_freesplit(string);
		c++;
		if (tenv[c])
			ft_env_loop(nenv, tenv, c);
		else
			nenv->next = NULL;
	}
}

void	ft_env_init(t_shell *shell, char *tenv[])
{
	char	**string;

	shell->exit_code = 0;
	shell->env = ft_calloc(1, sizeof(t_env));
	shell->dec_env = ft_calloc(1, sizeof(t_env));
	if (tenv[0])
	{
		string = ft_split(tenv[0], '=');
		shell->env->cmd = ft_strdup(string[0]);
		shell->env->val = ft_strdup(string[1]);
		shell->dec_env->cmd = ft_strdup(string[0]);
		shell->dec_env->val = ft_strdup(string[1]);
		ft_freesplit(string);
		ft_env_loop(shell->env, tenv, 1);
		ft_env_loop(shell->dec_env, tenv, 1);
	}
}

void	ft_env_free_loop(t_env *env)
{
	if (!env)
		return ;
	free(env->cmd);
	if (env->val != NULL)
		free(env->val);
	if (env->next != NULL)
		ft_env_free_loop(env->next);
	free (env);
}

void	ft_env_free(t_shell *shell)
{
	if (shell->env == NULL)
		return ;
	free(shell->env->cmd);
	free(shell->env->val);
	ft_env_free_loop(shell->env->next);
	free(shell->env);
	free(shell->dec_env->cmd);
	if (shell->dec_env->val)
		free(shell->dec_env->val);
	ft_env_free_loop(shell->dec_env->next);
	free(shell->dec_env);
}
