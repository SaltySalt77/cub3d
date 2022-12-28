
#include "cub3d.h"

void	perror_exit(void)
{
	perror("Error\n");
	system("leaks cub3D | grep leaks");
	exit(1);
}

void	init_game(t_data *m_data, t_textures *textures)
{
	int	i;
	int	wid;
	int	hei;

	i = 0;
	m_data->mlx = mlx_init();
	while (i < 4)
	{
		if (i == 0)
		m_data->imgs[i].image = mlx_xpm_file_to_image(m_data->mlx,
					textures->filename[i], &wid, &hei);
		i++;
	}
	//ㄴㅏ중에 map val >> 이중 str free
}

int	main(int argc, char	**argv)
{
	t_textures	textures;
	t_info		info;
	t_data		m_data;

	if (argc != 2)
	{
		perror("Error\n");
		system("leaks cub3D");
		return (1);
	}
	parser(&textures, &info, argv[1]);
	init_game(&m_data, &textures);
	if (!validate_map(&info, &textures, argv[1]))
		return (1);
	printf("=========\n"); //
	padding_map(&info);
	for (int i = 0; info.map[i]; i++)
		printf("%s | \n",info.map[i]);
	check_vec(&info);
	system("leaks cub3D |  grep leaks");
	return (0);
}
