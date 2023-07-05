/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:52:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 22:22:13 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_help_sphere(t_data *data, t_sphere sp, int line)
{
	rt_help_label(data, line++, "SPHERE");
	line++;
	rt_help_label(data, line, "Center X");
	rt_help_value_f(data, line++, sp.center.x, GREEN);
	rt_help_label(data, line, "Center Y");
	rt_help_value_f(data, line++, sp.center.y, GREEN);
	rt_help_label(data, line, "Center Z");
	rt_help_value_f(data, line++, sp.center.z, GREEN);
	line++;
	rt_help_label(data, line, "Radius");
	rt_help_value_f(data, line++, sp.radius, GREEN);
	return (line);
}

static int	rt_help_plane(t_data *data, t_plane pl, int line)
{
	rt_help_label(data, line++, "PLANE");
	line++;
	rt_help_label(data, line, "Point X");
	rt_help_value_f(data, line++, pl.point.x, GREEN);
	rt_help_label(data, line, "Point Y");
	rt_help_value_f(data, line++, pl.point.y, GREEN);
	rt_help_label(data, line, "Point Z");
	rt_help_value_f(data, line++, pl.point.z, GREEN);
	line++;
	rt_help_label(data, line, "Normal X");
	rt_help_value_f(data, line++, pl.normal.x, GREEN);
	rt_help_label(data, line, "Normal Y");
	rt_help_value_f(data, line++, pl.normal.y, GREEN);
	rt_help_label(data, line, "Normal Z");
	rt_help_value_f(data, line++, pl.normal.z, GREEN);
	return (line);
}

static int	rt_help_cylinder(t_data *data, t_cylinder cy, int line)
{
	rt_help_label(data, line++, "CYLINDER");
	line++;
	rt_help_label(data, line, "Center X");
	rt_help_value_f(data, line++, cy.center.x, GREEN);
	rt_help_label(data, line, "Center Y");
	rt_help_value_f(data, line++, cy.center.y, GREEN);
	rt_help_label(data, line, "Center Z");
	rt_help_value_f(data, line++, cy.center.z, GREEN);
	line++;
	rt_help_label(data, line, "Axis X");
	rt_help_value_f(data, line++, cy.axis.x, GREEN);
	rt_help_label(data, line, "Axis Y");
	rt_help_value_f(data, line++, cy.axis.y, GREEN);
	rt_help_label(data, line, "Axis Z");
	rt_help_value_f(data, line++, cy.axis.z, GREEN);
	line++;
	rt_help_label(data, line, "Radius");
	rt_help_value_f(data, line++, cy.radius, GREEN);
	line++;
	rt_help_label(data, line, "Height");
	rt_help_value_f(data, line++, cy.height, GREEN);
	return (line);
}

int	rt_help_obj(t_data *data, t_obj obj, int line)
{
	if (obj.type == SPHERE)
		return (rt_help_sphere(data, obj.sphere, line));
	if (obj.type == PLANE)
		return (rt_help_plane(data, obj.plane, line));
	if (obj.type == CYLINDER)
		return (rt_help_cylinder(data, obj.cylinder, line));
	return (0);
}
