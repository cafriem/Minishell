/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:04:53 by cafriem           #+#    #+#             */
/*   Updated: 2023/10/25 14:10:13 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

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
	return (str3);
}

char	*ft_env3(t_shell *shell, char *string)
{
	t_env	*done;

	done = shell->env;
	if (string[0] == '?')
		return (ft_strjoinfree(ft_itoa(shell->exit_code), ft_substr(string, 1,
					ft_strlen(string)), 3));
	while (done->next != NULL)
	{
		if (ft_strcmp(string, done->cmd) == 0)
			return (ft_strdup(done->val));
		done = done->next;
	}
	if (ft_strcmp(string, done->cmd) == 0)
		return (ft_strdup(done->val));
	return (ft_strdup(""));
}

void	ft_env2(t_shell *shell, int start)
{
	size_t	counter;
	char	*temp;
	char	*final;
	char	*string;

	counter = start + 1;
	if (shell->current_line[counter] == '?')
		counter++;
	while (ft_isalnum_mini(shell->current_line[counter]) == 1)
		counter++;
	final = ft_strdup(shell->current_line);
	if ((int)counter != start + 1)
	{
		temp = ft_substr(shell->current_line, start + 1, counter - start - 1);
		string = ft_env3(shell, temp);
		free(temp);
		free (shell->current_line);
		shell->current_line = ft_strjoinfree(
				ft_substr(final, 0, start), string, 3);
		shell->current_line = ft_strjoinfree(shell->current_line,
				ft_substr(final, counter, ft_strlen(final)), 3);
	}
	free(final);
}

int	ft_skip_word(t_shell *shell, int counter)
{
	counter += 2;
	while (shell->current_line[counter]
		&& shell->current_line[counter] == ' ')
		counter++;
	while (shell->current_line[counter]
		&& shell->current_line[counter] != ' ')
	{
		if (shell->current_line[counter] == '"'
			&& shell->current_line[counter + 1] == '\'')
			counter += ft_skip_spmark(shell->current_line, counter);
		else
			counter++;
	}
	return (counter);
}

void	ft_env(t_shell *shell, int counter)
{
	int	sp_counter;

	sp_counter = 0;
	while (shell->current_line[counter])
	{
		if (shell->current_line[counter] == '"')
		{
			counter++;
			sp_counter++;
		}
		else if (shell->current_line[counter] == '<'
			&& shell->current_line[counter + 1] == '<')
			counter = ft_skip_word(shell, counter);
		else if (shell->current_line[counter] == '\'' && sp_counter % 2 == 0)
			counter += ft_skip_spmark(shell->current_line, counter);
		else if (shell->current_line[counter] == '$')
		{
			ft_env2(shell, counter);
			counter++;
		}
		else
			counter++;
		if ((size_t)counter > ft_strlen(shell->current_line))
			break ;
	}
}
