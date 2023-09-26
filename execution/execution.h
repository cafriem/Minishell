/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 08:51:51 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/25 16:37:18 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing.h"
# include <signal.h>

///////////////////////// env ///////////////////////

int		ft_env_exc(t_shell *shell, int cmd_num);
void	update_environment_variable(t_env *env, 
			char *variable, char *new_value);
void	add_environment_variable(t_env **env, char *variable, char *value);
int		environment_variable_exists(t_env *env, char *variable);
char	*find_env(t_env *env, char *variable);

///////////////////////// pwd ///////////////////////

int		ft_pwd(t_shell *shell, int cmd_num, int flag);

///////////////////////// cd ///////////////////////

void	update_env(t_shell *shell, char *old_pwd, char *new_pwd);
void	change_path(t_shell *shell);
int		ft_cd(t_shell *shell, int cmd_num);

///////////////////////// unset ///////////////////////

int		ft_unset(t_shell *shell, int cmd_num);
void	remove_environment_variable(t_env **env, char *variable);
void	unset_utils(t_shell *shell, char *var);

///////////////////////// exit ///////////////////////

int		ft_exit(t_shell *shell, int cmd_num);
int		ft_str_isnum(char *c);
void	free_exit(t_shell *shell);
void	exit_utils2(t_shell *shell, char *arg);
void	exit_utils(t_shell *shell);

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

/////////////////////// redirection /////////////////////

void	redirection_dup(t_shell *shell, int cmd_num, int i, int flag);
int		redirection(t_shell *shell, int cmd_num);



//////////////////// open files ////////////////////////

int		ft_open(char *str, int flag);
void	first_cmd(t_shell *shell, int cmd_num);
void	last_cmd(t_shell *shell, int cmd_num);
void	middle_cmd(t_shell *shell, int cmd_num);
void	ft_dup2(t_shell *shell, int cmd_num);


///////////////// find path ///////////////////////////

char *find_path(t_shell *shell, char *command);

////////////////// excute ////////////////////////////

void	start_executing(t_shell *shell);
int		is_builtin(t_shell *shell, int cmd_num);
int		builtin_one(t_shell *shell, int cmd_num);
void 	forked_builtin(t_shell *shell, int cmd_num);
int		close_all_fd(t_shell *shell);
int		builtin_pipe(t_shell *shell, int cmd_num);
int		execute(t_shell *shell);

void	exc_cmd(t_shell *shell, int cmd_num);


char	*find_variable_val(t_env *env, char *variable);
char	**joind_env(t_shell *shell);

#endif
