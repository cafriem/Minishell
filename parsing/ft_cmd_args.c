
#include "parsing.h"

char	*filename_skip(char *string, int start)
{
	int	counter;

	counter = start;
	while (string[counter] == ' ')
		counter++;
	while (string[counter])
	{
		if (string[counter] == '"' || string[counter] == '\'')
			counter += ft_skip_spmark(string, counter);
		else if (ft_strchr(" <>|", string[counter]) != NULL)
			return (filename2(string, start, counter - start));
		else
			counter++;
	}
	return (filename2(string, start, counter - start));
}

int	skip_redirect(char *string, int start)
{
	int	counter;

	counter = start;
	if (string[counter] == '>' && string[counter + 1] == '>')
	{
		counter += 2;
		counter += ft_strlen(filename_skip(string, counter));
	}
	else if (string[counter] == '<' && string[counter + 1] == '<')
	{
		counter += 2;
		counter += ft_strlen(filename_skip(string, counter));
	}
	else if (string[counter] == '>')
	{
		counter += 1;
		counter += ft_strlen(filename_skip(string, counter));
	}
	else if (string[counter] == '<')
	{
		counter += 1;
		counter += ft_strlen(filename_skip(string, counter));
	}
	return(counter - start);
}

void	ft_cmd_args(t_command *command, char *string)
{
	char	*temp;
	int		counter;

	counter = 0;
	command->int_temp = 0;
	while (string[counter])
	{
		while (string[counter] == ' ')
			counter++;
		if (string[counter] == '<' || string[counter] == '>')
			counter += skip_redirect(string, counter);
		else if (string[counter])
		{
			if (command->int_temp == 0)
				temp = ft_strdup(sp_remover(word(string, counter)));
			else
			{
				temp = ft_strjoinfree(temp, " ", 1);
				temp = ft_strjoinfree(temp, sp_remover(word(string, counter)), 1);
			}
			command->int_temp++;
			printf("word = %s\n", word(string, counter));
			counter += ft_strlen(word(string, counter));
		}
		else
			counter++;
	}
	command->cmd_args = ft_splitmini(temp, ' ');
}
