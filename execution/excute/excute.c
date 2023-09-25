/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:36 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/25 10:42:59 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute(t_shell *shell)
{
	int wstatus;

	shell->fd_tmp = dup(STDOUT_FILENO);
	start_executing(shell);
	dup2(shell->fd_tmp, STDOUT_FILENO);
	close_all_fd(shell);
	while (waitpid(-1, &wstatus, 0) > -1)
		shell->exit_code = WEXITSTATUS(wstatus);
	return (1);
}

char **joind_env(t_shell *shell)
{
	int i;
	int j;
	t_env	*current;
	t_env	*tmp;
	char	**joind;
	char	*joind2;
	char	*joind3;


	current = shell->env;
	tmp = shell->env;
	i = 0;
	j = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	joind = (char **)malloc(sizeof(char *) * (i + 1));;
	while(j < i)
	{
		joind2 = ft_strjoin(tmp->cmd, "=");
		joind3 = ft_strjoin(joind2, tmp->val);
		joind[j] = (char *)malloc(strlen(joind3) + 1);
		ft_strncpy(joind[j], joind3, ft_strlen(joind3) + 1);
		free(joind2);
		free(joind3);
		tmp = tmp->next;
		j++;
	}
	joind[j] = "\n";
	return(joind);
}

void	start_executing(t_shell *shell)
{
	int	cmd_num;
	cmd_num = 0;
	while (cmd_num < shell->number_commands)
	{
		if (cmd_num != shell->number_commands - 1)
		{
			if (pipe(shell->command[cmd_num].fd) == -1)
				exit(-1);
		}
		if (shell->number_commands > 1 && is_builtin(shell, cmd_num))
			builtin_pipe(shell, cmd_num);
		else if (shell->number_commands == 1 && is_builtin(shell, cmd_num) == 1)
		{
			redirection(shell, cmd_num);
			builtin_one(shell, cmd_num);
		}
		else
			exc_cmd(shell, cmd_num);
		cmd_num++;
	}
}

char	*find_variable_val(t_env *env, char *variable)
{

	while (env != NULL)
	{
		if (strcmp(env->cmd, variable) == 0)
		{
			free(env->val);
			return (env->val);
		}
		env = env->next;
	}
	return (NULL);
}

void check_infile_exc(t_shell *shell, int cmd_num)
{
	char **env;
	int env_val;

	if (ft_strncmp(shell->command[cmd_num].cmd_args[0], "./", 2) == 0)
	{
		// if (ft_strncmp(shell->command[cmd_num].cmd_args[0], "./minishell", ft_strlen(shell->command[cmd_num].cmd_args[0])) == 0)
		// {
		// 	env_val = ft_atoi(find_variable_val(shell->env, "SHLVL")) + 1;
		// 	// add_environment_variable(&(shell->env), "SHLVL", ft_itoa(env_val));
		// }
		env = joind_env(shell);
		if (execve(shell->command[cmd_num].cmd_args[0], shell->command[cmd_num].cmd_args, env) < 0)
		{
			perror(shell->command[cmd_num].cmd_args[0]);
		}
		close_all_fd(shell);
		shell->exit_code = errno;
		free(env);
		exit(errno);
	}
}

void	forked_child(t_shell *shell, int cmd_num)
{
	char *cmd_path;
	
	check_infile_exc(shell, cmd_num);
	cmd_path = find_path(shell, shell->command[cmd_num].cmd_args[0]);
	if (execve(cmd_path, shell->command[cmd_num].cmd_args, NULL) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->command[cmd_num].cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
		close_all_fd(shell);
		shell->exit_code = errno;
		exit(errno);

}

void	exc_cmd(t_shell *shell, int cmd_num)
{
	int	id;

	id = fork();
	if (id < 0)
		exit(-1);
	else if (id == 0)
	{
		ft_dup2(shell, cmd_num);
		redirection(shell, cmd_num);
		close_all_fd(shell);
		forked_child(shell, cmd_num);
	}
}

int	builtin_one(t_shell *shell, int cmd_num)
{
	if (ft_pwd(shell, cmd_num, 0) || ft_cd(shell, cmd_num) || 
		ft_unset(shell, cmd_num) || ft_env_exc(shell, cmd_num) || 
		ft_echo(shell, cmd_num) || ft_export(shell, cmd_num))
		return (1);
	else if (ft_exit(shell, cmd_num))
		exit (-1);
	return (0);
}

int	is_builtin(t_shell *shell, int cmd_num)
{
	if (ft_strcmp(shell->command[cmd_num].cmd_args[0], "pwd") == 0 || 
		ft_strcmp(shell->command[cmd_num].cmd_args[0], "cd") == 0 || 
		ft_strcmp(shell->command[cmd_num].cmd_args[0], "unset") == 0 || 
		ft_strcmp(shell->command[cmd_num].cmd_args[0], "env") == 0 || 
		ft_strcmp(shell->command[cmd_num].cmd_args[0], "exit") == 0 || 
		ft_strcmp(shell->command[cmd_num].cmd_args[0], "echo") == 0
		|| ft_strcmp(shell->command[cmd_num].cmd_args[0], "export") == 0)
		return (1);
	return (0);
}

void forked_builtin(t_shell *shell, int cmd_num)
{
	if (ft_pwd(shell, cmd_num, 0) || ft_cd(shell, cmd_num) || 
		ft_unset(shell, cmd_num) || ft_env_exc(shell, cmd_num) || 
		ft_echo(shell, cmd_num) || ft_export(shell, cmd_num))
		{
		close_all_fd(shell);
		exit (0);
		}
	else if (ft_exit(shell, cmd_num))
		exit(shell->exit_code);
	close_all_fd(shell);
	exit(-1);
}

int	close_all_fd(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->number_commands)
	{
		if (shell->command[i].fd[0] != 0)
		{
			close (shell->command[i].fd[0]);
			shell->command[i].fd[0] = 0;
		}
		if (shell->command[i].fd[1] != 0)
		{
			close (shell->command[i].fd[1]);
			shell->command[i].fd[1] = 0;
		}
		if (shell->command[i].fd_redi != 0)
		{
			close (shell->command[i].fd_redi);
			shell->command[i].fd_redi = 0;
		}
		i++;
	}
	if (shell->fd_tmp != 0)
	{
		close (shell->fd_tmp);
		shell->fd_tmp = 0;
	}
	return (1);
}

int	builtin_pipe(t_shell *shell, int cmd_num)
{
	int	id;

	id = fork();
	if (id < 0)
		exit(-1);
	else if (id == 0)
	{
		if (shell->number_commands != 1)
			ft_dup2(shell, cmd_num);
		redirection(shell, cmd_num);
		forked_builtin(shell, cmd_num);
		close_all_fd(shell);
	}
	return (1);
}