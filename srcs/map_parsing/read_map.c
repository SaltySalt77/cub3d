/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:18:01 by hyna              #+#    #+#             */
/*   Updated: 2022/12/26 16:40:55 by hyna             ###   ########.fr       */
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

void	save_textures(char	**file, t_textures	*textures)
{
	char	*std[6];
	char	**line;
	int 	cnt;
	int 	chk[6];
	int		i;
	int		j;

	std[0] = "NO";
	std[1] = "SO";
	std[2] = "WE";
	std[3] = "EA";
	std[4] = "F";
	std[5] = "C";
	ft_bzero(chk, 6 * (sizeof(int)));
	i = 0;
	cnt = 0;
	while (file[i] && cnt < 6 && cnt == i)
	{
		line = ft_split(file[i], ' ');
		if (!line || line[2])
		{
			// printf("%s\n",line[2]);
			printf("%d %d %d\n",i,j,cnt);

			ft_free_split(file);
			printf("t1\n");//
			perror_exit();
		}
		j = 0;
		while (j < 6)
		{
			if (!ft_strncmp(line[0], std[j], ft_strlen(std[j])))
			{
				if (chk[j] || ft_strlen(line[0]) != ft_strlen(std[j]))
				{
					ft_free_split(file);
					ft_free_split(line);
					printf("t2\n");//
					perror_exit();
				}
				printf("%s %d\n",line[0],j);
				chk[j] = 1;
				cnt++;
				break ;
			}
			j++;
		}
		i++;
		ft_free_split(line);
	}
	// if (cnt != 6)
	// {
	// 	ft_free_split(file);
	// 	printf("t3\n");//
	// 	perror_exit();
	// }
}

void	parser(t_textures	*textures, t_info	*info, char	*arg)
{
	char	**file;

	validate_filename(arg);
	file = read_file(arg);
	for (int i = 0; file[i]; i++)
	{
		printf("%s\n", file[i]);
	}
	save_textures(file, textures);
}