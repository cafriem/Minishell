/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:36:21 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/10 12:37:19 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	get_readstr(char **str, int fd)
{
	ft_putendl_fd(*str, fd);
	free(*str);
	*str = readline("> ");
}

void	get_readstr2(char **str)
{
	free(*str);
	*str = readline("> ");
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
		get_readstr(&str, p_fd[1]);
	}
	if (str)
		free(str);
	close(fd);
	if (is_builtin(shell, cmd_num) == 0)
		fd_herdoc_closer(p_fd);
	return (0);
}

int	here_doc3(t_shell *shell, int cmd_num, int redi_num)
{
	char	*str;

	str = readline("> ");
	while (str && ft_strcmp(str, shell->command[cmd_num].redir[redi_num].file))
		get_readstr2(&str);
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
