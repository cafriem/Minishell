#include "parsing.h"

int	redirect_counter(char *string)
{
	int	redirector;
	int	c;

	c = 0;
	redirector = 0;
	while (string[c])
	{
		if ((string[c] == '>' && string[c + 1] == '>') 
			|| (string[c] == '<' && string[c + 1] == '<'))
		{
			c += 2;
			redirector++;
		}
		else if (string[c] == '>' || string[c] == '<')
		{
			c++;
			redirector++;
		}
		else if (string[c] == '\'' || string[c] == '\"')
			c += ft_skip_spmark(string, c);
		else
			c++;
	}
	return (redirector);
}

// char	*filefinder(char *string, int start)
// {
// 	int	ending;

// 	ending = start;
// 	while string
// }

void	ft_red(char *string, int start, struct s_command *command, int pos)
{
	int	counter;

	counter = start;
	while (string[counter])
	{
		if (string[counter] == '>' || string[counter] == '<')
		{
			command->redir[pos].file = ft_strtrim(ft_substr(string, start, counter), " ");
			break;
		}
		else if (string[counter] == '\'' || string[counter] == '\"')
			counter += ft_skip_spmark(string, counter);
		else
			counter++;
	}
}

void	ft_redirectin(char *string, struct s_command *command, int pos)
{
	int	c;

	c = 0;
	while(string[c])
	{
		if ((string[c] == '>' && string[c + 1] == '>')
			|| (string[c] == '<' && string[c + 1] == '<'))
		{
			if (string[c] == '>')
				command->redir[pos].direct = 3;
			else
				command->redir[pos].direct = 2;
			ft_red(string, c + 2, command, pos);
			pos++;
			c += 2;
		}
		else if (string[c] == '>' || string[c] == '<')
		{
			if (string[c] == '>')
				command->redir[pos].direct = 1;
			else
				command->redir[pos].direct = 0;
			ft_red(string, c + 1, command, pos);
			pos++;
			c++;
		}
		else
			c++;
	}
}

void	ft_redirect(struct s_command *command)
{
	int	counter;
	int	c;

	counter = 0;
	printf("entered \n");
	c = redirect_counter(&command->temp);
	printf("counter = %d \n", c);
	command->redir = ft_calloc(c, sizeof(t_direct));
	printf("calloc \n");
	ft_redirectin(&command->temp, &command, counter);
	printf("finished \n");
}
