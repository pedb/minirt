/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:26:25 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:26:26 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_vec3	crossproduct(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

double	dotproduct(t_vec3 v1, t_vec3 v2)
{
	double	ret;

	ret = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (ret);
}

t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3 ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}
