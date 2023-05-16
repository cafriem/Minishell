#include "parsing.h"

int	ft_opr_counter(const char *c)
{
	int	op_counter;
	int	sp_mark;
	int	s_mark;
	int	i;

	op_counter = 0;
	sp_mark = 0;
	s_mark = 0;
	i = 0;
	while (c[i])
	{
		if (c[i] == '\'')
			s_mark++;
		if (c[i] == '"')
			sp_mark++;
		while ((s_mark % 2 != 0 || sp_mark % 2 != 0) && c[i])
		{
			i++;
			if (c[i] == '\'')
				s_mark++;
			if (c[i] == '"')
				sp_mark++;
			// if (!c[i])
			// 	return (0);
		}
		if ((c[i] == '>' && c[i + 1] == '>') || (c[i] == '<' && c[i + 1] == '<'))
		{
			op_counter++;
			i += 2;
		}
		else if (c[i] == '>' || c[i] == '<' || c[i] == '|')
		{
			op_counter++;
			i++;
		}
		else
			i++;
	}
	return (op_counter);
}

int	main(void)
{
	char		*start;
	int			cmd;
	t_shell		shell;

	start = "< t1 grep yes > r | grep monomo";
	cmd = splitcount(start, '|');
	shell.command = ft_calloc(cmd, sizeof(t_command*));
	shell.temp = ft_splitmini(start, '|');
	printf("0. %s\n", shell.temp[0]);
	printf("1. %s\n", shell.temp[1]);
	printf("2. %s\n", shell.temp[2]);
	printf("seperating\n");
	ft_redirect(shell.temp[0], shell.command[0]);
	// ft_redirecter(string, command);
}
