#include "libft.h"

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strnum(char	*str, char	*charset)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_charset(str[i], charset))
			i++;
		if (str[i])
			num++;
		while (str[i] && !(is_charset(str[i], charset)))
			i++;
	}
	return (num);
}

int	ft_str_len(char *str, char *charset, int *i)
{
	int	len;

	len = 0;
	*i = 0;
	while (str[*i] && is_charset(str[*i], charset))
		(*i)++;
	while (str[*i] && !(is_charset(str[*i], charset)))
	{
		len++;
		(*i)++;
	}
	return (len);
}

char	**ft_split(char	*str, char	*charset)
{
	char	**result;
	int		num;
	int		len;
	int		i;
	int		j;

	if ((*str == 0) || (*charset == 0))
		return (0);
	num = ft_strnum(str, charset);
	i = 0;
	result = 0;
	result = (char **)malloc(sizeof(char *) * (num + 1));
	if (result == 0)
		return (NULL);
	while ((i < num) && *str)
	{
		len = ft_str_len(str, charset, &j);
		result[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (result[i] == 0) ///for 문 돌면서 free 처리하기
			return (NULL);
		ft_strncpy(result[i++], (str + j - len), len);
		str += j;
	}
	result[num] = 0;
	return (result);
}
