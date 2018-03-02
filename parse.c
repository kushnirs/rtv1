/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:13:38 by sergee            #+#    #+#             */
/*   Updated: 2018/03/02 16:22:05 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	parse_light(char *line, t_light *light)
{
	int	i;

	line[6] != '{' ? exit(ft_printf("Wrong light parameter\n")) : 0;
	i = 7;
	i += check_int(&line[i], &light->type);
	i += check_float(&line[i], &light->intensity);
	i += check_coord(&line[i], &light->direction);
	line[i] != '}' || line[i + 1] != 0 ?
		exit(ft_printf("missing parameter /0\n")) : 0;
}

static void	parse_object(char *line, t_obj *obj)
{
	int	i;

	line[7] != '{' ? exit(ft_printf("Wrong object parameter\n")) : 0;
	i = 8;
	i += check_int(&line[i], &obj->name);
	i += check_coord(&line[i], &obj->c);
	i += check_coord(&line[i], &obj->d);
	i += check_float(&line[i], &obj->radius);
	i += check_int(&line[i], &obj->color);
	i += check_float(&line[i], &obj->specular);
	i += check_float(&line[i], &obj->reflection);
	line[i] ? exit(ft_printf("missing parameter /0\n")) : 0;
}

static void	parse_scene(char *line, t_scene *scene)
{
	int	i;

	line[6] != '{' ? exit(ft_printf("Wrong object parameter\n")) : 0;
	i = 7;
	i += check_coord(&line[i], &scene->o);
	i += check_coord(&line[i], &scene->cam_rot);
	i += check_coord(&line[i], &scene->canvas);
	line[i] != '}' || line[i + 1] != 0 ?
		exit(ft_printf("missing parameter /0\n")) : 0;
	scene->d = (t_point){0, 0, 0};
	scene->t_min = 1;
	scene->t_max = INFINITY;
	scene->viewport = (t_point){100, 100, 0};
}

static void	read_param(char *filename, t_sdl *data, int *num, int fd)
{
	int		gnl;
	char	*line;

	data->scene.n_o = num[O];
	data->scene.n_l = num[L];
	num[O] ? data->obj = (t_obj*)malloc(sizeof(t_obj) * (num[O])) : 0;
	num[L] ? data->light = (t_light*)malloc(sizeof(t_light) * (num[L])) : 0;
	!data->obj || !data->light ? exit(ft_printf("malloc error\n")) : 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		exit(ft_printf("No file %s\n", filename));
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (!ft_strncmp(line, "scene\t", 6))
			parse_scene(line, &data->scene);
		else if (!ft_strncmp(line, "object\t", 7))
			parse_object(line, &data->obj[--num[O]]);
		else if (!ft_strncmp(line, "light\t", 6))
			parse_light(line, &data->light[--num[L]]);
		ft_memdel((void **)&line);
	}
	gnl == -1 ? exit(ft_printf("GNL SHIT\n")) : 0;
	close(fd);
}

void		parse_param(char *filename, t_sdl *data)
{
	int		fd;
	int		gnl;
	int		num[3];
	char	*line;

	num[0] = 0;
	num[1] = 0;
	num[2] = 0;
	line = NULL;
	if ((fd = open(filename, O_RDONLY)) == -1)
		exit(ft_printf("No file %s\n", filename));
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (!ft_strncmp(line, "scene\t", 6))
			num[S]++;
		else if (!ft_strncmp(line, "object\t", 7))
			num[O]++;
		else if (!ft_strncmp(line, "light\t", 6))
			num[L]++;
		else
			exit(ft_printf("Wrong parameter\n"));
		ft_memdel((void **)&line);
	}
	gnl == -1 ? exit(ft_printf("GNL SHIT\n")) : 0;
	num[S] != 1 ? exit(ft_printf("Wrong quantity of scenes\n")) : 0;
	close(fd);
	read_param(filename, data, num, fd);
}
