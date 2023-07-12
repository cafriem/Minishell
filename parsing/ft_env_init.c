
#include "parsing.h"

void	ft_env_loop(t_env *env, char *tenv[], int c)
{
	char	**string;
	t_env	*nenv;

	nenv = calloc(1, sizeof(t_env));
	if (tenv[c])
	{
		env->next = nenv;
		string = ft_split(tenv[c], '=');
		nenv->variable = ft_strdup(string[0]);
		nenv->value = ft_strdup(string[1]);
		free(string[0]);
		free(string[1]);
		free(string);
		printf("%d variable = |%s|\n", c, nenv->variable);
		printf("%d value = |%s|\n", c, nenv->value);
		c++;
		ft_env_loop(nenv, tenv, c);
	}
	else
		env->next = NULL;
}

void	ft_env_init(t_env *env, char *tenv[])
{
	char	**string;
	t_env	*nenv;
	int	c;

	c = 0;
	nenv = calloc(1, sizeof(t_env));
	if (tenv[c])
	{
		string = ft_split(tenv[c], '=');
		env->next = nenv;
		env->variable = ft_strdup(string[0]);
		env->value = ft_strdup(string[1]);
		free(string[0]);
		free(string[1]);
		free(string);
		printf("%d variable = |%s|\n", c, env->variable);
		printf("%d value = |%s|\n", c, env->value);
		c++;
//
		string = ft_split(tenv[c], '=');
		nenv->variable = ft_strdup(string[0]);
		nenv->value = ft_strdup(string[1]);
		free(string[0]);
		free(string[1]);
		free(string);
		printf("%d variable = |%s|\n", c, nenv->variable);
		printf("%d value = |%s|\n", c, nenv->value);
		c++;
		ft_env_loop(nenv, tenv, c);
	}
}
