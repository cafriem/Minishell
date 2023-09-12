/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmrabet <cmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 08:51:51 by cmrabet           #+#    #+#             */
/*   Updated: 2023/09/12 17:59:53 by cmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing.h"

void print_environment(t_env *env);
void update_environment_variable(t_env *env, const char *variable, const char *new_value);
void add_environment_variable(t_env **env, const char *variable, const char *value);
void remove_environment_variable(t_env **env, const char *variable);
int environment_variable_exists(t_env *env, const char *variable);
int	ft_env_exc(t_shell *shell, int cmd_num);
void	sorting_env(t_env *env);
char *find_env(t_env *env, const char *variable);


int	ft_pwd(t_shell *shell, int cmd_num);


void	update_env(t_shell *shell, const char *old_pwd, const char *new_pwd);
void	change_path(t_shell *shell);
int	ft_cd(t_shell *shell, int cmd_num);



#endif
