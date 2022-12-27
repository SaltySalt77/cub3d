#include "cub3d.h"

int	padding_map(char **map, t_info *info)
{
	char	**temp;
	char	*temp_str;
	int		i;
	int		j;
	int		len_origin;

	temp = ft_calloc(info->max_hei+1, sizeof(char *));
	if (!temp)
		return (0);
	i = 0;
	while (map[i])
	{
		len_origin = ft_strlen(map[i]);
		temp[i] = ft_calloc(info->max_wid+1, sizeof(char));
		if (!temp[i])
		{
			ft_free_split(temp); //map에 대한 free는 일괄적으로 다른 곳에서 처리하는게 이중 free를 막을 것으로 예상되어서 하지 않았습니다.
			return (0); //호출부에서 map free
		}
		j = 0;
		while (j < info->max_wid)
		{
			if (j < len_origin)
				temp[i][j]=map[i][j];
			else
				temp[i][j] = ' ';
			j++;
		}
		temp[i][j] = 0;
		i++;
	}
	temp[i] = 0;
	ft_free_split(map);
	info->map = temp;
	return (1);
	//1.싹다 temp에 담고, 이슈가 있을때에만 처리
	//2. 붙히면ㄴ서 동시에 처리?
	// 1번으로 선택. >> 복사, 스페이스 붙히는것 까지 temp에서 처리 하고나서, 기존의 map을 다 free하고,
	// 그다음 map이 temp를 가르키게 하고 리턴 1
}

