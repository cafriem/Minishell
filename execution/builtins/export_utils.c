/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:48:38 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/08 15:00:02 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

char	**split_export(char *str)
{
	char	**out;
	int		i;
	int		j;

	i = 0;
	out = (char **)malloc(sizeof(char *) * (3));
	while (str[i] && str[i] != '=')
		i++;
	j = i;
	while (str[i])
		i++;
	out[0] = (char *)malloc(sizeof(char) * (j + 1));
	ft_strncpy(out[0], &str[0], j);
	if (!str[j])
	{
		out[1] = (char *)malloc(sizeof(char) * (1));
		out[1][0] = '\0';
	}
	else
	{
		out[1] = (char *)malloc(sizeof(char) * ((i - j) + 1));
		ft_strncpy(out[1], &str[j + 1], i - j);
	}
	out[2] = NULL;
	return (out);
}

void	free_export(char **str)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	export_utils(t_shell *shell, char *var)
{
	shell->exit_code = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
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
