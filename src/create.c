/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:34:14 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/15 14:11:59 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtl.h"

t_mtl		create_mtl(size_t capacity)
{
	return ((t_mtl) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_material))
	});
}

t_material	create_material(size_t capacity)
{
	return ((t_material) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_material_value))
	});
}