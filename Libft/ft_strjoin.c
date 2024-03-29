/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokashi <smokashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:08:17 by cafriem           #+#    #+#             */
/*   Updated: 2023/08/28 22:51:28 by smokashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		c;
	int		c1;
	int		c2;
	char	*ptr;

	c = 0;
	if (!s1 || !s2)
		return (NULL);
	c1 = ft_strlen(s1);
	c2 = ft_strlen(s2);
	ptr = (char *)malloc(c1 + c2 + 1);
	if (ptr == NULL)
		return (NULL);
	while (s1[c] != '\0')
	{
		ptr[c] = s1[c];
		c++;
	}
	c2 = 0;
	while (s2[c2] != '\0')
		ptr[c++] = s2[c2++];
	ptr[c] = '\0';
	return (ptr);
}

// int	main(void)
// {
// 	char s1[] = "Hello my";
// 	char s2[] = "friend";
// 	printf("%s", ft_strjoin(s1, s2));
// }
