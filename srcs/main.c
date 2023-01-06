#include "cub3d.h"

void	perror_exit(char *err_msg)
{
	if (!err_msg)
	{
		perror("Error\n");
		exit(1);
	}
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err_msg, 2);
	system("leaks cub3D | grep leaks");
	exit(1);
}

int	main_loop(t_data	*m_data)
{
	ray_casting(m_data);
	key_hook(m_data->info);
	return (0);
}

int	main(int argc, char	**argv)
{
	t_info		info;
	t_data		m_data;

	if (argc != 2)
	{
		perror("Error\n");
		return (1);
	}
	parser(&(m_data.textures), &info, argv[1]);
	init_game(&m_data, &(m_data.textures));
	if (!validate_map(&info, argv[1]))
		return (1);
	padding_map(&info);
	check_vec(&info);
	m_data.info = &info;
	info.map[(int)info.pos_y][(int)info.pos_x] = '0';
	init_info(&info);
	m_data.win = mlx_new_window(m_data.mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "cub3D");
	mlx_hook(m_data.win, X_EVENT_KEY_PRESS, 0, &press_key, &m_data);
	mlx_hook(m_data.win, X_EVENT_KEY_RELEASE, 0, &release_key, &info);
	mlx_hook(m_data.win, X_EVENT_KEY_EXIT, 0, &exit_game, &m_data);
	mlx_loop_hook(m_data.mlx, &main_loop, (void *)&m_data);
	mlx_loop(m_data.mlx);
	return (0);
}
