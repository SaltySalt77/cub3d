/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:18:01 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 11:47:50 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_filename(char	*filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		perror_exit("Invalid File Name");
	if (ft_strncmp(filename + (len - 4), ".cub", 5))
		perror_exit("Invalid File Name");
}

char	**read_file(char	*arg)
{
	int		fd;
	char	*line;
	char	*file;
	char	**file_splited;

	file = NULL;
	fd = open(arg, O_RDONLY, 0666);
	if (fd < 0)
		perror_exit(NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		file = ft_strjoin_free(file, line);
	}
	file_splited = ft_split(file, '\n');
	free(file);
	if (!file_splited)
		perror_exit(NULL);
	close(fd);
	return (file_splited);
}

int	validate_arguments(char	**argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (j == 0)
			{
				if (ft_isdigit(argv[i][j]) == 0 && argv[i][j] != '+')
					return (0);
				else if (argv[i][j] == '+' && argv[i][j + 1] == 0)
					return (0);
			}
			else if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	save_rgb(int	*rgb, char	**line)
{
	int	temp;
	int	i;

	i = 1;
	if (!validate_arguments(line))
		return (0);
	while (i < 4)
	{
		temp = ft_atoi(line[i]);
		if (temp < 0 || temp > 255)
			return (0);
		rgb[i - 1] = temp;
		i++;
	}
	return (1);
}

void	parser(t_textures	*textures, t_info	*info, char	*arg)
{
	char	*std[6];
	char	**file;
	int		i;

	i = 0;
	validate_filename(arg);
	file = read_file(arg);
	assort_textures(file, textures, std);
	check_fc(file);
	cut_map(file, info);
	if (!info->map)
	{
		while (i < 4)
			free(textures->filename[i++]);
		perror_exit(NULL);
	}
}
