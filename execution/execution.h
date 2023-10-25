/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 08:51:51 by cmrabet           #+#    #+#             */
/*   Updated: 2023/10/25 10:57:34 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing.h"
# include <signal.h>

/*----------------------------- BUILTIN ---------------------------------
|																		 |
------------------------------- BUILTIN --------------------------------*/

///////////////////////// env ///////////////////////

int		ft_env_exc(t_shell *shell, int cmd_num);
void	update_environment_variable(t_env *env,
			char *variable, char *new_value);
void	add_environment_variable(t_env **env, char *variable, char *value);
int		environment_variable_exists(t_env *env, char *variable);
char	*find_env(t_env *env, char *variable);

///////////////////////// pwd ///////////////////////

int		ft_pwd(t_shell *shell, int cmd_num, int flag);
void	change_path(t_shell *shell);

///////////////////////// cd ///////////////////////

void	update_env(t_shell *shell, char *old_pwd, char *new_pwd);
void	absolute_pathcase(t_shell *shell, int cmd_num);
int		err_msg(t_shell *shell, int flag, int cmd_num);
int		ft_cd(t_shell *shell, int cmd_num);
int		ft_cd2(t_shell *shell, int cmd_num);

///////////////////////// unset ///////////////////////

int		ft_unset(t_shell *shell, int cmd_num);
void	remove_environment_variable(t_env **env, char *variable);
void	unset_utils(t_shell *shell, char *var);

///////////////////////// exit ///////////////////////

int		ft_exit(t_shell *shell, int cmd_num);
int		ft_str_isnum(char *c);
void	free_exit(t_shell *shell);
void	exit_utils2(t_shell *shell, char *arg);
void	exit_utils(t_shell *shell, int cmd_num);

///////////////////////// echo ///////////////////////

int		ft_echo(t_shell *shell, int cmd_num);
void	ft_echo_2(t_shell *shell, int cmd_num);

///////////////////////// export ///////////////////////

int		ft_export(t_shell *shell, int cmd_num);
void	sorting_env(t_env *env);
void	print_export(t_env *env);
int		check_var(char *str);
void	swap_var(t_env *env, t_env	*tmp);

///////////////////////// export_utils ///////////////////////

void	export_utils(t_shell *shell, char *var);
char	**split_export(char *str);
char	*ft_strncpy(char *s1, char *s2, int n);
void	free_export(char **str);

///////////////////////// signal ///////////////////////

void	signal_handler(int sig);
void	check_signal(void);
void	set_signal(void);
void	signal_handler2(int sig_num);

/*----------------------------- EXECUTION -------------------------------
|																		 |
------------------------------- EXECUTION--------------------------------*/

/////////////////////// redirection /////////////////////

int		redirection_dup(t_shell *shell, int cmd_num, int i, int flag);
int		here_doc_redi2(t_shell *shell, int cmd_num, int lst_redi_pos);
int		here_doc_redi(t_shell *shell, int cmd_num);
void	is_heredoc(t_shell *shell, int cmd_num, int i);
int		redirection(t_shell *shell, int cmd_num);

//////////////////// open files ////////////////////////

int		ft_open(t_shell *shell, char *str, int flag);
void	first_cmd(t_shell *shell, int cmd_num);
void	last_cmd(t_shell *shell, int cmd_num);
void	middle_cmd(t_shell *shell, int cmd_num);
void	ft_dup2(t_shell *shell, int cmd_num);

///////////////// find path ///////////////////////////

void	check_stat(t_shell *shell, char *command);
char	*find_path3_2(t_shell *shell, char *command);
char	*find_path3(t_shell *shell, char *command);
char	*find_path2(t_shell *shell, char *command);
char	*find_path(t_shell *shell, char *command);

////////////////// excute ////////////////////////////

int		execute(t_shell *shell);
void	start_executing(t_shell *shell);
void	start_executing2(t_shell *shell, int cmd_num, int flag);
void	forked_child(t_shell *shell, int cmd_num);
void	exc_cmd(t_shell *shell, int cmd_num);

////////////////// excute2 ////////////////////////////

void	forked_builtin(t_shell *shell, int cmd_num);
int		builtin_pipe(t_shell *shell, int cmd_num);
int		is_builtin(t_shell *shell, int cmd_num);
void	check_infile_exc(t_shell *shell, int cmd_num);
void	free_exit_child(t_shell *shell);

////////////////// excute3 ////////////////////////////

int		builtin_1(t_shell *shell, int cmd_num);
int		check_red(t_shell *shell);

////////////////// excute2_utils//////////////////////////

int		env_len(t_shell *shell);
char	**joind_env(t_shell *shell);
char	*find_variable_val(t_env *env, char *variable);
void	close_all_fd(t_shell *shell);
void	fd_herdoc_closer(int *fd);

////////////////// here_doc//////////////////////////

void	get_readstr(char **str, int fd, int flag);
int		heredoc_pos(t_shell *shell, int cmd_num);
int		heredoc_exc2(t_shell *shell, int p_fd[2], int cmd_num, int redi_num);
int		here_doc3(t_shell *shell, int cmd_num, int redi_num);
int		heredoc_exc(t_shell *shell, int cmd_num, int i);

#endif
