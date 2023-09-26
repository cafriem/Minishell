/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:43:11 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/26 17:47:17 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	// ft_putchar_fd('\n');
	exit(1);
}

void	set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
}

void	get_readstr(char **str, int fd)
{
	ft_putendl_fd(*str, fd);
	free(*str);
	*str = readline("> ");
	set_signal();
}

int 	here_doc2(t_shell *shell, int cmd_num, int redi_num)
{
	char	*str;
	int		fd;
	int		pid;

	dup2(shell->command[cmd_num].fd[0], STDIN_FILENO);
	dup2(shell->command[cmd_num].fd[1], STDOUT_FILENO);
	pid = fork();
	if (pid > 0)
		return (pid);
	set_signal();
	fd = open(shell->command[cmd_num].redir[redi_num].file, O_CREAT | O_WRONLY | O_TRUNC, 0622);
	str = readline("> ");
	while (str && ft_strcmp(str, shell->command[cmd_num].redir[redi_num].file))
		get_readstr(&str, fd);
	if (str)
		free(str);
	close(fd);
	if (unlink(shell->command[cmd_num].redir[redi_num].file) == -1) 
        perror("unlink");
	exit(0);
}

int	here_doc(t_shell *shell, int cmd_num, int redi_num)
{
	int		pid;
	int		status;

	pid = here_doc2(shell, cmd_num, redi_num);
	waitpid(pid, &status, 0);
	shell->exit_code = WEXITSTATUS(status);
	return (1);
}