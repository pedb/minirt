/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 11:42:47 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/03/03 17:14:37 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	add_light(t_data *my_mlx, t_light *light_current, t_vec3 lightdir,
	int threadnr)
{
	double	dotnormal;
	double	intensity;
	double	r2;

	r2 = vec3_sqr(lightdir);
	lightdir.y = -1.0 * lightdir.y;
	lightdir.x = -1.0 * lightdir.x;
	dotnormal = fmax(0.0, dotproduct(my_mlx->ray[threadnr]->hitnormal,
		lightdir));
	intensity = fmin(1.0, light_current->brightness / (4.0 * M_PI * r2) *
	dotnormal * 2 * ALBEDO);
	return (colour_mul(my_mlx->ray[threadnr]->colour, light_current->colour,
			fmax(0.0, intensity)));
}

t_col	light_tracing(t_data *my_mlx, int threadnr)
{
	t_col	out;
	t_light	*tmplight;
	t_vec3	hitpos;
	t_vec3	lightdir;
	double	distance;

	tmplight = my_mlx->light;
	out = colour_mul(my_mlx->ray[threadnr]->colour,
		my_mlx->scene->amblightcolour, my_mlx->scene->ambintensity);
	hitpos = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray[threadnr]->v,
	my_mlx->ray[threadnr]->length - EPSILON));
	while (tmplight)
	{
		lightdir = vec3_sub(tmplight->s, hitpos);
		distance = find_length(tmplight->s, hitpos);
		if (obstaclecheck(my_mlx, hitpos, lightdir, distance) == 0)
			out = colour_add(out, add_light(my_mlx, tmplight,
					lightdir, threadnr));
		tmplight = tmplight->next;
	}
	out = colour_cap(out);
	return (out);
}
