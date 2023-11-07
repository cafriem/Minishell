/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:36:21 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/07 19:31:18 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_strcmp2(const char *s1, const char *s2)
{
	size_t	c;

	c = 0;
	while (s1[c] && s2[c])
	{
		if ((unsigned char)s1[c] != (unsigned char)s2[c])
			return ((unsigned char)s1[c] - (unsigned char)s2[c]);
		if ((unsigned char)s1[c + 1] == '\n'
			|| (unsigned char)s2[c + 1] == '\n')
			break ;
		c++;
	}
	return ((unsigned char)s1[c] - (unsigned char)s2[c]);
}

int	heredoc_exc(t_shell *shell, int cmd_num, int i)
{
	char	*str;
	int		fd;
	char	*filename;

	filename = ft_strjoin("/tmp/hhdoc_",
			shell->command[cmd_num].redir[i].file);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (str == NULL
			|| !ft_strcmp2(str, shell->command[cmd_num].redir[i].file))
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	if (str)
		free(str);
	close(fd);
	return (0);
}

int	heredoc_pos(t_shell *shell, int cmd_num)
{
	int	i;

	i = shell->command[cmd_num].no_redir;
	while (i > -1)
	{
		if (shell->command[cmd_num].redir[i].direct == HERE_DOC)
			return (i);
		i--;
	}
	return (-1);
}

int	here_doc3(t_shell *shell, int cmd_num, int redi_num)
{
	char	*str;

	str = readline("> ");
	while (str && ft_strcmp(str, shell->command[cmd_num].redir[redi_num].file))
	{
		free(str);
		str = readline("> ");
	}
	if (str)
		free(str);
	if (g_exit_signal == 1)
	{
		free_exit_child(shell);
		exit (200);
	}
	return (0);
}
