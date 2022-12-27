#include "cub3d.h"

char	*find_map(int fd, t_info	*info)
{
	char	*compare;

	while (1)
	{
		compare = get_next_line(fd);
		if (!compare
			|| !ft_strncmp(compare, info->map[0], ft_strlen(info->map[0])))
			return (compare);
		free(compare);
	}
}

// 임시이름 이후에 수정
int	validate_newline(char	*filename, t_info	*info)
{
	char	*compare;
	int		i;
	int		fd;

	i = 0;
	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0)
		return (0);
	compare = find_map(fd, info);
	while (info->map[i])
	{
		if (ft_strncmp(compare, info->map[i], ft_strlen(info->map[i])))
		{
			free(compare);
			close(fd);
			return (0);
		}
		free(compare);
		compare = get_next_line(fd);
		i++;
	}
	close(fd);
	return (1);
}

int	validate_textures(t_textures *textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (textures->filename[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_c(char c, int chk_dir)
{
	if (c == '0' || c == '1' || c == ' ')
		return (2);
	if ((c == 'N') || (c == 'S') || (c == 'E') || (c == 'W'))
	{
		if (chk_dir)
			return (0);
		return (1);
	}
	return (0);
}

int	count_map(char **map, t_info *info)
{
	int	m_w;
	int	i;
	int	j;
	int	chk_dir;

	m_w = 0;
	i = 0;
	chk_dir = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_c(map[i][j], chk_dir) == 1)
			{
				if ((map[i][j]) == 'N')
					info->dir = 0;
				else if ((map[i][j]) == 'S')
					info->dir = 1;
				else if ((map[i][j]) == 'E')
					info->dir = 2;
				else if ((map[i][j]) == 'W')
					info->dir = 3;
				chk_dir = 1;
			}
			else if (!check_c(map[i][j], chk_dir))
				return (0);
			j++;
		}
		if (j > m_w)
			m_w = j;
		i++;
	}
	info->max_hei = i;
	info->max_wid = m_w;
	return (1);
	//0,1,N,S,E,W,Space >> N,S,E,W >>는 플레이어의 방향이므로 무조건 한 개
}

int	validate_map(t_info *info, t_textures *textures, char	*filename)
{
	if (!count_map(info->map, info) || !(validate_textures(textures)))
		return (0); //(main 주석 참조.) main의 init_game에서 사용하고 있는 캐릭터 프리 해줘야함.
	if (!validate_newline(filename, info))
		return (0);
	// if (!padding_map(info->map, info))
	// 	return (1);
	//padding 까지 다 된 후에 벡터 체크해야 validate가 비로소 끝난다.
	return (1);
}
