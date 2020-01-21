/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 22:12:23 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/21 22:40:31 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			ft_lstadd_back_camera(t_cam **alst, t_cam *new)
{
	t_cam *tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
	{
		new->next = *alst;
		*alst = new;
	}
}

int				find_camera(t_data *my_mlx, char *line, int *i)
{
	t_cam		*new;
	static int	headcheck = 0;

	new = malloc(sizeof(t_cam));
	if (new == NULL)
		return (0);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);

	new->v.x = ft_atof_peer(line, i);
	new->v.y = ft_atof_peer(line, i);
	new->v.z = ft_atof_peer(line, i);

	new->fov = ft_atoi_peer(line, i);
	new->next = NULL;
	new->c2w = mat4_lookat(new->s, vec3_add(new->s, new->v));
	printf("camera: coords={%f, %f, %f}, vector={%f, %f, %f}, fov=%i\nWith matrix being:\n", new->s.x, new->s.y, new->s.z, new->v.x, new->v.y, new->v.z, new->fov);
	printmatrix(new->c2w);
	new->quat = quat_init(1.0, 0.0, 0.0, 0);
	new->quat = quat_mult(quat_lookat(vec3_new(1, 0, 0),
                new->v), new->quat);
	printquat(new->quat, "we on that new quat shit");
	new->c2w = quat_to_matrix(new->quat);
	ft_lstadd_back_camera(&my_mlx->cam, new);
	if (headcheck == 0)
	{
		my_mlx->camhead = my_mlx->cam;
		headcheck++;
	}
	return (1);
}