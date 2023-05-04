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
		if ((c[i] == '>' && c[i + 1] == '>') || (c[i] == '<' && c[i + 1] == '<') || (c[i] == '|' && c[i + 1] == '|'))
		{
			op_counter++;
			i += 2;
		}
		else if (c[i] == '>' || c[i] == '<')
		{
			op_counter++;
			i++;
		}
		else
			i++;
	}
	return (op_counter);
}

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*t;
	size_t	i;
	size_t	j;
	size_t	size;

	i = start;
	j = 0;
	size = ft_strlen(s);
	if (!s)
		return (0);
	if (len > size)
		len = size;
	if (start + len > size)
		len = size - start;
	if (start >= size)
		len = 0;
	t = (char *)malloc(sizeof(char) * (len + 1));
	if (!t)
		return (0);
	while (i < size && j < len)
		t[j++] = s[i++];
	t[j] = '\0';
	return (t);
}

static void	assigns(const char *s, char **str, char c, int count)
{
	int	start_index;
	int	sp_counter;
	int	s_counter;
	int	j;
	int	i;

	i = 0;
	j = 0;
	sp_counter = 0;
	s_counter = 0;
	while (i < count && s[j])
	{
		if (s[j] == c && (sp_counter % 2 == 0 && s_counter % 2 == 0))
			j++;
		else
		{
			start_index = j;
			while (s[j] && (s[j] != c && (sp_counter % 2 == 0 || s_counter % 2 == 0)))
			{
				while (sp_counter % 2 != 0 || s_counter % 2 != 0)
				{
					if (s[j] == '\'')
						s_counter++;
					if (s[j] == '"')
						sp_counter++;
					j++;
					printf("yessrir\n");
				}
				while (s[j])
				{
					if (s[j] == '\'')
					{
						s_counter++;
						j++;
						break ;
					}
					if (s[j] == '"')
					{
						sp_counter++;
						j++;
						break ;
					}
					j++;
				}
			}
			while (s[j] == c && (sp_counter % 2 != 0 || s_counter % 2 != 0))
			{
				if (s[j] == '\'')
				{
					s_counter++;
					j++;
					break ;
				}
				if (s[j] == '"')
				{
					sp_counter++;
					j++;
					break ;
				}
				j++;
			}
			str[i] = ft_strtrim(ft_substr(s, start_index, j - start_index), " ");
			i++;
		}
	}
	str[i] = 0;
}

// static int	getwordcount(const char *s, char c)
// {
// 	int	sp_counter;
// 	int	s_counter;
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	sp_counter = 0;
// 	s_counter = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'')
// 			s_counter++;
// 		if (s[i] == '\"')
// 			sp_counter++;
// 		if (s[i] == c)
// 		{
// 			i++;
// 			if (s[i] == c && (sp_counter % 2 == 0 && s_counter % 2 == 0))
// 			{
// 				printf("fail\n");
// 				exit (0);
// 				//fix men
// 			}
// 		}
// 		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
// 		{
// 			if (sp_counter % 2 == 0 && s_counter % 2 == 0)
// 				j++;
// 			i++;
// 		}
// 		else if (s[i] != c && s[i + 1] != c)
// 			i++;
// 	}
// 	return (j);
// }

char	**ft_splitps(const char *s, char c)
{
	size_t		count;
	char		**str;

	if (!s)
		return (NULL);
	count = ft_opr_counter(s);
	printf("count = %zu\n",count);
	if (count == 0)
		return (NULL);
	str = (char **)malloc((count + 1) * sizeof(char *));
	if (str == NULL)
		return (str);
	assigns(s, str, c, count);
	return (str);
}

int	main(void)
{
	char	**string;

	string = ft_splitps("grepp gyg \"|| \"monomo yessi >> r", '|');
	printf("0. %s\n", string[0]);
	printf("1. %s\n", string[1]);
	printf("2. %s\n", string[2]);

}
