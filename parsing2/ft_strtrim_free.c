/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:01:21 by smokashi          #+#    #+#             */
/*   Updated: 2023/09/04 14:30:45 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static char	*ft_null(char *ptr)
{
	ptr[0] = '\0';
	return (ptr);
}

char	*ft_strtrim_free(char *s1, char const *set)
{
	int		left;
	int		right;
	int		c;
	char	*ptr;

	left = 0;
	c = 0;
	right = (ft_strlen(s1) - 1);
	while (ft_strchr(set, s1[left]) != NULL)
		if (s1[left++] == '\0')
			return (ft_null(ptr = malloc(1)));
	while (ft_strchr(set, s1[right]) != NULL)
		right--;
	ptr = ft_calloc(sizeof(char), (right - left) + 2);
	if (ptr == NULL)
		return (NULL);
	right++;
	while (left != right)
		ptr[c++] = s1[left++];
	free(s1);
	return (ptr);
}
