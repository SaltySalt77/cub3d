#include "cub3d.h"

void	init_game(t_data *m_data, t_textures *textures)
{
	int	i;
	int	wid;
	int	hei;

	i = 0;
	m_data->mlx = mlx_init();
	while (i < 4)
	{
		m_data->imgs[i].image = mlx_xpm_file_to_image(m_data->mlx,
				textures->filename[i], &wid, &hei);
		if (!m_data->imgs[i].image)
			perror_exit("No search file or diretory");
		i++;
	}
}

int	exit_game(t_data *m_data)
{
	mlx_destroy_window(m_data->mlx, m_data->win);
	system("leaks cub3D | grep leak");
	exit(0);
}
