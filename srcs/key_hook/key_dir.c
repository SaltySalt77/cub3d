#include "cub3d.h"

void	key_hook_a(t_info	*info)
{
    if(info->map[(int)(info->pos_y - info->plane_y * MOVE_SPEED * 2)][(int)info->pos_x] == '0')
		info->pos_y -= info->plane_y * MOVE_SPEED;
	if(info->map[(int)info->pos_y][(int)(info->pos_x - info->plane_x * MOVE_SPEED * 2)] == '0')
		info->pos_x -= info->plane_x * MOVE_SPEED;
}
void	key_hook_d(t_info	*info)
{
	if (info->map[(int)(info->pos_y + info->plane_y * MOVE_SPEED * 2)][(int)(info->pos_x)] == '0')
		info->pos_y += info->plane_y * MOVE_SPEED;
	if (info->map[(int)(info->pos_y)][(int)(info->pos_x + info->plane_x * MOVE_SPEED * 2)] == '0')
		info->pos_x += info->plane_x * MOVE_SPEED;
}

int	key_hook(t_info *info)
{
	if (info->move.w && !info->move.s)
		key_hook_w(info);
	if (info->move.s && !info->move.w)
		key_hook_s(info);
	if (info->move.a && !info->move.d)
		key_hook_a(info);
	if (info->move.d && !info->move.a)
		key_hook_d(info);
	if (info->move.l && !info->move.r)
		key_hook_l(info);
	if (info->move.r && !info->move.l)
		key_hook_r(info);
	return (1);
}

void	key_hook_w(t_info *info)
{
	if (info->map[(int)(info->pos_y + info->dir_y * MOVE_SPEED * 2)][(int)(info->pos_x)] == '0')
		info->pos_y += info->dir_y * MOVE_SPEED;
	if (info->map[(int)(info->pos_y)][(int)(info->pos_x + info->dir_x * MOVE_SPEED * 2)] == '0')
		info->pos_x += info->dir_x * MOVE_SPEED;
}

void	key_hook_s(t_info	*info)
{
    if (info->map[(int)(info->pos_y - info->dir_y * MOVE_SPEED * 2)][(int)info->pos_x] == '0')
		info->pos_y -= info->dir_y * MOVE_SPEED;
	if (info->map[(int)info->pos_y][(int)(info->pos_x - info->dir_x * MOVE_SPEED * 2)] == '0')
		info->pos_x -= info->dir_x * MOVE_SPEED;
}
