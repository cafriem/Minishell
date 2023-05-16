#include "parsing.h"

int	ft_skip_spmark(const char *string, int start)
{
	int	s_mark;
	int	counter;
	int	sp_mark;

	s_mark = 0;
	sp_mark = 0;
	counter = start;
	if (string[counter] == '\'')
		s_mark++;
	if (string[counter] == '"')
		sp_mark++;
	counter++;
	while ((sp_mark % 2 != 0))
	{
		if (string[counter] == '"')
			sp_mark++;
		counter++;
	}
	while ((s_mark % 2 != 0))
	{
		if (string[counter] == '\'')
			s_mark++;
		counter++;
	}
	return (counter - start);
}

int	splitcount(const char *string, char separator)
{
	int	counter;
	int	sep;

	sep = 0;
	counter = 0;
	while (string[counter])
	{
		if (string[counter] == '\'' || string[counter] == '\"')
			counter += ft_skip_spmark(string, counter);
		if (string[counter] == separator)
			sep++;
		counter++;
	}
	return (sep + 1);
}

char	**ft_splitmini(const char *string, char separator)
{
	char	**main;
	int		counter;
	int		start;
	int		word_counter;

	counter = 0;
	word_counter = 0;
	start = 0;
	main = ft_calloc(splitcount(string, separator) + 1, sizeof(char*));
	if (main == NULL)
		return (NULL);
	while (string[counter] != '\0')
	{
		if (string[counter] == '\'' || string[counter] == '"')
			counter += ft_skip_spmark(string, counter);
		if (string[counter] == separator)
		{
			main[word_counter] = ft_strtrim(ft_substr(string, start, (counter - start)), " ");
			start = counter + 1;
			word_counter++;
		}
		counter++;
	}
	main[word_counter] = ft_strtrim(ft_substr(string, start, (counter - start)), " ");
	return(main);
}

// int	main(void)
// {
// 	char	**string;

// 	string = ft_splitmini("Testings yes | antoherdw\"fs|f'd\" ysesir | nono", '|');
// 	// string = ft_splitmini("Testings yes|antohe ysesir|nono", '|');
// 	printf("%s\n", string[0]);
// 	printf("%s\n", string[1]);
// 	printf("%s\n", string[2]);
// 	printf("%s\n", string[3]);
// }
