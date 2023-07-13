/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:04:53 by cafriem           #+#    #+#             */
/*   Updated: 2023/06/12 17:02:35 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strjoinfree(char *str1, char *str2, int flag)
{
	char	*str3;

	str3 = ft_strjoin(str1, str2);
	if (flag == 1)
		free(str1);
	if (flag == 2)
		free(str2);
	if (flag == 3)
	{
		free(str1);
		free(str2);
	}
	return(str3);
}

void	ft_env3(t_shell *shell, char *string)
{
	while (shell->env)
	{
		if (ft_strncmp(string, shell->env->variable, ft_strlen(string)) == 0)
			shell->line = shell->env->value;
		shell->env = shell->env->next;
	}
	
}

void	ft_env2(t_shell *shell, int start)
{
	size_t		counter;
	char	*end;

	counter = start;
	while (ft_isalnum_mini(shell->current_line[counter]) == 1)
		counter++;
	
}

void	ft_env(t_shell *shell, char *env[])
{
	int	counter;

	counter = 0;
	while (shell->current_line[counter])
	{
		if (shell->current_line[counter] == '$')
			ft_env2(shell, counter);
		counter++;
	}
	printf("non = |%s|", env[0]);
}
