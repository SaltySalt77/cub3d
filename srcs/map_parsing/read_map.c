/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:18:01 by hyna              #+#    #+#             */
/*   Updated: 2022/12/28 14:43:13 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
	// 파일 .cub로 끝나는 지 확인
	// 파일 열고 -> open 함수 예외처리
	// 파일 다 읽어오기 2중 배열
	// 텍스처 저장 -> 예외처리
	// 맵 저장하면서 예외처리 + 패딩까지

void	validate_filename(char	*filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		perror_exit();
	if (ft_strncmp(filename + (len - 4), ".cub", 5))
		perror_exit();
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
		perror_exit();
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
		perror_exit();
	close(fd);
	return (file_splited);
}

	// 순서 상관 없음
	// 중복시 예외처리 -> int chk
	// count가 6미만일 때 map이 나올 경우 exit
	// 파일 오픈 mlx_xpm ~
	// free 잘하기
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

int	save_textures2(t_textures	*textures, int j, char **line)
{
	char	*temp;

	if (j < 4)
	{
		temp = ft_strdup(line[1]);
		if (!temp)
			return (0);
		textures->filename[j] = temp;
		return (1);
	}
	else if (j == FLOOR)
		return (save_rgb(textures->floor, line));
	else
		return (save_rgb(textures->ceiling, line));
}

int	ft_checkline(char **line)
{
	if (ft_strncmp(line[0], "F", 2) && ft_strncmp(line[0], "C", 2))
	{
		if (line[2])
		{
			ft_free_split(line);
			return (0);
		}
		else
			return (1);
	}
	else if (!ft_strncmp(line[0], "F", 2) && count_strs(line) == 4)
		return (1);
	else if (!ft_strncmp(line[0], "C", 2) && count_strs(line) == 4)
		return (1);
	ft_free_split(line);
	return (0);
}

void	init_vars(char	*std[6], int	chk[6])
{
	std[NORTH] = "NO";
	std[SOUTH] = "SO";
	std[WEST] = "WE";
	std[EAST] = "EA";
	std[FLOOR] = "F";
	std[CEILING] = "C";
	ft_bzero(chk, 6 * (sizeof(int)));
}

int	verify_idf(char	**file, char	**line, char	*std[6], int	*chk)
{
	int		j;

	j = -1;
	while (++j < 6)
	{
		if (!ft_strncmp(line[0], std[j], ft_strlen(std[j])))
		{
			if (chk[j] || ft_strlen(line[0]) != ft_strlen(std[j]))
			{
				ft_free_split(file);
				ft_free_split(line);
				perror_exit();
			}
			chk[j] = 1;
			break ;
		}
	}
	if (j >= 6)
	{
		ft_free_split(file);
		ft_free_split(line);
		perror_exit();
	}
	return (j);
}

void	assort_textures(char	**file, t_textures	*textures, char	*std[6])
{
	char	**line;
	int		cnt;
	int		chk[6];
	int		i;

	i = 0;
	cnt = 0;
	init_vars(std, chk);
	while (file[i] && cnt < 6 && cnt == i)
	{
		line = ft_split2(file[i], " ,");
		if (!line || !ft_checkline(line))
		{
			ft_free_split(file);
			perror_exit();
		}
		i++;
		cnt += (save_textures2(textures,
					verify_idf(file, line, std, chk), line));
		ft_free_split(line);
	}
	if (cnt != 6)
	{
		ft_free_split(file);
		perror_exit();
	}
}

void	parser(t_textures	*textures, t_info	*info, char	*arg)
{
	char	*std[6];
	char	**file;
	int		i;

	i = 0;
	validate_filename(arg);
	file = read_file(arg);
	// for (int i = 0; file[i]; i++)
	// {
	// 	printf("%s\n", file[i]);
	// }
	assort_textures(file, textures, std);
	cut_map(file, info);
	if (!info->map)
	{
		while (i < 4)
			free(textures->filename[i++]);
		perror_exit();
	}
	for (int i = 0; i < FLOOR; i++)
		printf("%s\n",textures->filename[i]);
	for (int i = 0; i < 3 ; i++ )
		printf("%d\n",textures->floor[i]);
	for (int i = 0; i < 3 ; i++ )
		printf("%d\n",textures->ceiling[i]);
	for (int i = 0; info->map[i]; i++)
		printf("%s\n", info->map[i]);
}
