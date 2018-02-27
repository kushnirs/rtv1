/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:13:38 by sergee            #+#    #+#             */
/*   Updated: 2018/02/26 20:29:34 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1_cl.h"

static int	check_param(char *str, float *res)
{
	int		i;
	int		len;
	float	num;

	i = -1;
	while (str[i] != ',' || str[++i])
	{
		if ((str[i] >= '0' || str[i] <= '9') || str[i] == '.')
			continue;
		exit(ft_printf("Wrong floating-point number\n"));
	}
	str[i] == 0 ? i = -1 : 0;
	num = 0;
	*res = ft_atoi(str);
	len = ft_nbrlen((int)*res);
	str[len] == '.' ?  num = ft_atoi(&str[len + 1]) : 0;
	len = ft_nbrlen((int)num);
	*res += num / pow(10, i);
	return (i);
}

static void	parse_light(char *line, t_light *light, int num)
{
	int	i;
	int	a;

	line[5] != '{' ? exit(ft_printf("Wrong light parameter\n")) : 0;
	i = check_param(&line[6], &light->type);
	i += check_param(&line[i + 1], &light->intensity);
}

static void	parse_object(char *line, t_obj *obj, int num)
{
	int	i;

	line[6] != '{' ? exit(ft_printf("Wrong object parameter\n")) : 0;
	i = 0;
	while (line[i])
	{

	}
}

static void	parse_scene(char *line, t_scene *scene)
{
	int	i;

	*scene = (t_scene){.viewport = (t_point){100, 100, 0}, .deep = 2,
			.t_min = 1, .t_max = MAX_SIZE};
	line[5] != '{' ? exit(ft_printf("Wrong scene parameter\n")) : 0;
	i = 0;
	while (*line)
	{

	}
}

static void	read_param(char *filename, t_mlx *data, int *num, int fd)
{
	int		i;
	int		gnl;
	char	*line;

	num[O] ? data->obj = (t_obj*)malloc(sizeof(t_obj) * num[O]) : 0;
	num[L] ? data->light = (t_light*)malloc(sizeof(t_light) * num[L]) : 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		exit(ft_printf("No file %s\n", filename));
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (!ft_strcmp(line, "scene\t"))
			parse_scene(line, &data->scene);
		else if (!ft_strcmp(line, "object\t"))
			parse_object(line, data->obj, --num[O]);
		else if (!ft_strcmp(line, "light\t"))
			parse_light(line, data->light, --num[L]);
		free(line);
	}
	gnl == -1 ? exit(ft_printf("GNL SHIT\n")) : 0;
	close(fd);
}

void	parse_param(char *filename, t_mlx *data)
{
	int		fd;
	int		gnl;
	int		num[3];
	char	*line;

	num = {0, 0, 0};
	if ((fd = open(filename, O_RDONLY)) == -1)
		exit(ft_printf("No file %s\n", filename));
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (!ft_strcmp(line, "scene\t"))
			num[S]++;
		else if (!ft_strcmp(line, "object\t"))
			num[O]++;
		else if (!ft_strcmp(line, "light\t"))
			num[L]++;
		else
			exit(ft_printf("Wrong parameter\n"));
		free(line);
	}
	gnl == -1 ? exit(ft_printf("GNL SHIT\n")) : 0;
	num[S] != 1 ? exit(ft_printf("Wrong quantity of scenes\n")) : 0;
	close(fd);
	read_param(filename, data, num, fd);
}