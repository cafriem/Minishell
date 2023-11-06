/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:36:21 by cmrabet           #+#    #+#             */
/*   Updated: 2023/11/06 18:04:16 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	get_readstr(char **str, int fd, int flag)
{
	if (flag == 1)
	{
		free(*str);
		*str = readline("> ");
	}
	else if (flag == 2)
	{
		ft_putendl_fd(*str, fd);
		free(*str);
		*str = readline("> ");
	}
}

int	heredoc_exc2(t_shell *shell, int p_fd[2], int cmd_num, int redi_num)
{
	char	*str;
	int		fd;

	str = readline("> ");
	fd = open(shell->command[cmd_num].redir[redi_num].file,
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (str && ft_strcmp(str, shell->command[cmd_num].redir[redi_num].file))
	{
		write(fd, str, strlen(str));
		write(fd, "\n", 1);
		get_readstr(&str, p_fd[1], 2);
	}
	if (str)
		free(str);
	close(fd);
	if (is_builtin(shell, cmd_num) == 0)
		fd_herdoc_closer(p_fd);
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
		get_readstr(&str, 0, 1);
	if (str)
		free(str);
	return (0);
}

int	heredoc_exc(t_shell *shell, int cmd_num, int i)
{
	int	fd[2];
	int	status;

	pipe(fd);
	heredoc_exc2(shell, fd, cmd_num, i);
	shell->exit_code = WEXITSTATUS(status);
	if (is_builtin(shell, cmd_num) == 0)
		dup2(fd[1], 0);
	if (is_builtin(shell, cmd_num) == 1)
		fd_herdoc_closer(fd);
	return (shell->exit_code);
}
