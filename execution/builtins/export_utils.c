/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:48:38 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/06 09:33:15 by cmrabet          ###   ########.fr       */
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
	j = 0;
	out = (char **)malloc(sizeof(char *) * (3));
	while (str[i] && str[i] != '=')
		i++;
	j = i;
	while (str[i])
		i++;
	out[0] = (char *)malloc(sizeof(char) * (j + 1));
	ft_strncpy(out[0], &str[0], j);
	out[1] = (char *)malloc(sizeof(char) * ((i - j) + 1));
	ft_strncpy(out[1], &str[j + 1], i - j);
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

void	export_utils(char *var)
{
	exit_code = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}
