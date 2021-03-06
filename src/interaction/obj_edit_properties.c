/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_edit_properties.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:17:42 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:17:43 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	obj_move(t_vec3 pos, t_data *my_mlx)
{
	t_vec3	mult_r;
	t_vec3	mult_up;
	t_vec3	mult_fw;

	mult_r = vec3_mult(my_mlx->cam->c2w.r, my_mlx->click->dist_r *
	my_mlx->click->distance
	/ my_mlx->scene->width);
	mult_up = vec3_mult(my_mlx->cam->c2w.up, my_mlx->click->dist_up *
	my_mlx->click->distance
	/ my_mlx->scene->height);
	mult_fw = vec3_mult(my_mlx->cam->c2w.fw, my_mlx->click->dist_fw);
	pos = vec3_sub(pos, mult_r);
	pos = vec3_sub(pos, mult_up);
	pos = vec3_sub(pos, mult_fw);
	return (pos);
}

int		object_edit_properties(t_data *my_mlx)
{
	if (my_mlx->click->identifier == 's')
		sphere_edit_properties(my_mlx);
	else if (my_mlx->click->identifier == 't')
		triangle_edit_properties(my_mlx);
	else if (my_mlx->click->identifier == 'q')
		square_edit_properties(my_mlx);
	else if (my_mlx->click->identifier == 'c')
		cylinder_edit_properties(my_mlx);
	else if (my_mlx->click->identifier == 'p')
		plane_edit_properties(my_mlx);
	return (1);
}

void	object_sizemult(int keycode, t_data *my_mlx)
{
	if (keycode == NUMPLUS)
		my_mlx->click->sizemult *= 1.2;
	if (keycode == NUMMINUS)
		my_mlx->click->sizemult /= 1.2;
	if (keycode == NUMSLASH)
		my_mlx->click->heightmult /= 1.2;
	if (keycode == NUMSTAR)
		my_mlx->click->heightmult *= 1.2;
}

void	object_change_rotsize(int keycode, t_data *my_mlx)
{
	t_vec3	angle;

	object_sizemult(keycode, my_mlx);
	angle = vec3_new(0.0, 0.0, 0.0);
	if (keycode >= NUMTWO && keycode <= NUMNINE)
	{
		if (keycode == NUMFOUR)
			angle = vec3_sub(angle, vec3_new(0.0, 3 * CAM_ROT_SPEED, 0.0));
		if (keycode == NUMSIX)
			angle = vec3_add(angle, vec3_new(0.0, 3 * CAM_ROT_SPEED, 0.0));
		if (keycode == NUMTWO)
			angle = vec3_sub(angle, vec3_new(3 * CAM_ROT_SPEED, 0.0, 0.0));
		if (keycode == NUMEIGHT)
			angle = vec3_add(angle, vec3_new(3 * CAM_ROT_SPEED, 0.0, 0.0));
		if (keycode == NUMSEVEN)
			angle = vec3_sub(angle, vec3_new(0.0, 0.0, 3 * CAM_ROT_SPEED));
		if (keycode == NUMNINE)
			angle = vec3_add(angle, vec3_new(0.0, 0.0, 3 * CAM_ROT_SPEED));
		my_mlx->click->rotation = addrotation(my_mlx->click->rotation, angle);
		object_edit_properties(my_mlx);
	}
}
