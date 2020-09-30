#include "mtl.h"

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*c_src = src;
	char		*c_dst;

	c_dst = dst;
	while (n--)
		*c_dst++ = *c_src++;
	return (dst);
}

t_mtl		create_mtl(size_t capacity)
{
	return ((t_mtl) {
		.len = 0,
		.capacity = capacity,
		.inner = malloc(capacity * sizeof(t_mtl_material))
    });
}

bool			append_material(t_mtl *mtl, t_mtl_material material)
{
	size_t			new_capacity;
	t_mtl_material	*new;

	if (mtl->len == mtl->capacity)
	{
		new_capacity = mtl->capacity * 2;
		if (!(new = malloc(new_capacity * sizeof(t_mtl_material))))
			return (false);
		ft_memcpy(new, mtl->inner, mtl->capacity);
		free(mtl->inner);
		mtl->inner = new;
		mtl->capacity = new_capacity;
	}
	mtl->inner[mtl->len++] = material;
	return (true);
}

bool			append_char(char **str, char c, size_t *size , size_t i)
{
	size_t	new_size;
	char 	*new;

	if (i == *size)
	{
		new_size = *size * 2;
		if (!(new = malloc(new_size * sizeof(char))))
			return (false);
		ft_memcpy(new, *str, *size);
		free(*str);
		*str = new;
		*size = new_size;
	}
	(*str)[i] = c;
	return (true);
}