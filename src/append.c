/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:39:27 by mkervabo          #+#    #+#             */
/*   Updated: 2019/07/15 15:33:10 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtl.c"

bool			append_material(t_mtl *mtl, t_material material)
{
	size_t		new_capacity;
	t_material	*new;

	if (mtl->len == mtl->capacity)
	{
		new_capacity = mtl->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_material))))
			return (false);
		ft_memcpy(new, mtl->inner, mtl->capacity);
		free(mtl->inner);
		mtl->inner = new;
		mtl->capacity = new_capacity;
	}
	mtl->inner[mtl->len++] = material;
	return (true);
}

bool			append_material_value(t_material *material, t_material_value value)
{
	size_t			new_capacity;
	t_material_value	*new;

	if (material->len == material->capacity)
	{
		new_capacity = material->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_material_value))))
			return (false);
		ft_memcpy(new, material->inner, material->capacity);
		free(material->inner);
		material->inner = new;
		material->capacity = new_capacity;
	}
	material->inner[material->len++] = value;
	return (true);
}