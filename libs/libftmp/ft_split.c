/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:14:09 by hyna              #+#    #+#             */
/*   Updated: 2021/12/22 11:03:50 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const	*s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] && (s[i] == c))
		i++;
	while (s[i])
	{
		while (s[i] && (s[i] != c))
			i++;
		count++;
		while (s[i] && (s[i] == c))
			i++;
	}
	return (count);
}

static char	*word_split(char const	*s, char c, int *j)
{
	int	i;

	while (s[*j] && (s[*j] == c))
		(*j)++;
	i = *j;
	while (s[*j] && (s[*j] != c))
		(*j)++;
	return (ft_substr(s, i, (*j) - i));
}

static void	free_everything(char	**result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

char	**ft_split(char const	*s, char c)
{
	char	**result;
	int		j;
	int		k;
	int		count;

	j = 0;
	k = 0;
	if (!s)
		return (NULL);
	count = word_count(s, c);
	result = (char **) malloc((count + 1) * sizeof(char *));
	if (!(result))
		return (NULL);
	while (k < count)
	{
		result[k] = word_split(s, c, &j);
		if (!result[k])
		{
			free_everything(result);
			return (NULL);
		}
		k++;
	}
	result[k] = NULL;
	return (result);
}
