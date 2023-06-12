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
	else if (flag == 3)
	{
		free(str1);
		free(str2);
	}
	return(str3);
}

void	ft_env3(char *string, int start, int end)
{
	printf("string = %s\n", string);
	end = start + end;
}

void	ft_env2(char *string, int start)
{
	size_t		counter;
	char	*begining;
	char	*end;

	counter = start;
	while (ft_isalnum_mini(string[counter]) == 1)
		counter++;
	if (start > 0)
		begining = ft_substr(string, 0, start);
	if (counter != ft_strlen(string))
		end = ft_substr(string, counter, ft_strlen(string));
	ft_env3(ft_substr(string, start, counter - start), start, counter);
	
}

void	ft_env(t_shell *shell, char *string)
{
	int	counter;

	counter = 0;
	shell->exit_code = 0;
	while (string[counter])
	{
		if (string[counter] == '$')
			ft_env2(string, counter);
		counter++;
	}
}
