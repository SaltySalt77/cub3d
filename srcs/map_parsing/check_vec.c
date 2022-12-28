#include "cub3d.h"

int check_vec(t_info *info)
{
	int	y;
	int	x;
	int idx;
	int	ny[4];
	int nx[4];
	int dy;
	int dx;

	ny[0] = 1;
	ny[1] = -1;
	ny[2] = 0;
	ny[3] = 0;

	nx[0] = 0;
	nx[1] = 0;
	nx[2] = 1;
	nx[3] = -1;

	y = 0;
	while(info->map[y])
	{
		x = 0;
		while(info->map[y][x])
		{
			idx = 0;
			if (info->map[y][x]!='0')
			{
				x++;
				continue;
			}
			while(idx < 4)
			{
				dy = ny[idx]+y;
				dx = nx[idx]+x;
				if (dy<0 || dx < 0 || dy >= info->max_hei || dx >= info->max_wid)
				{
					printf("%d , %d out\n",dy,dx);///
					return (0);
				}
				if (info->map[dy][dx] == ' ')
				{
					printf("%d , %d space\n",dy,dx);///
					return (0);
				}
				idx++;
			}
			x++;
		}
		y++;
	}
	printf("validate map!\n");///
	return (1);
}
