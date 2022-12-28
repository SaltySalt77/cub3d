#include "cub3d.h"

int	check_vec_util(t_info *info, int y, int x)
{
	int	idx;
	int	ny[4];
	int	nx[4];
	int	dy;
	int	dx;

	ny[0] = 1;
	ny[1] = -1;
	ny[2] = 0;
	ny[3] = 0;
	nx[0] = 0;
	nx[1] = 0;
	nx[2] = 1;
	nx[3] = -1;
	idx = 0;
	while (idx < 4)
	{
		dy = ny[idx] + y;
		dx = nx[idx] + x;
		if (dy < 0 || dx < 0 || dy >= info->max_hei || dx >= info->max_wid
			|| info->map[dy][dx] == ' ')
		{
			printf("%d, %d : out \n",dy,dx);//
			return (0);
		}
		idx++;
	}
	return (1);
}

int	check_vec(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (info->map[y])
	{
		x = 0;
		while (info->map[y][x])
		{
			if (info->map[y][x] != '0')
			{
				x++;
				continue ;
			}
			if (!check_vec_util(info, y, x))
				return (0);
			x++;
		}
		y++;
	}
	printf("validate map!\n");///
	return (1);
}
