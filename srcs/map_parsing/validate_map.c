#include "cub3d.h"

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

void	save_chara_dir(char dir, t_info	*info, int	*chk_dir)
{
	if (dir == 'N')
		info->dir = 0;
	else if (dir == 'S')
		info->dir = 1;
	else if (dir == 'E')
		info->dir = 2;
	else if (dir == 'W')
		info->dir = 3;
	*chk_dir = 1;
}

int	count_map(char **map, t_info *info)
{
	int	i;
	int	j;
	int	chk_dir;

	info->max_wid = 0;
	i = 0;
	chk_dir = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_c(map[i][j], chk_dir) == 1)
				save_chara_dir(map[i][j], info, &chk_dir);
			else if (!check_c(map[i][j], chk_dir))
				return (0);
			j++;
		}
		if (j > info->max_wid)
			info->max_wid = j;
		i++;
	}
	info->max_hei = i;
	return (chk_dir);
}

int	validate_map(t_info *info, char	*filename)
{
	if (!count_map(info->map, info))
		perror_exit();
	if (!validate_newline(filename, info))
		perror_exit();
	return (1);
}
