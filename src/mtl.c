#include "mtl.h"

void			skip_ws(t_mtl_reader *r, bool newline)
{
	int16_t	c;

	while ((c = reader_peek(r)) != -1 && (c == ' ' || c == '\t' || c == '#'
				|| (newline && c == '\n')))
	{
		if (c == '#')
		{
			while ((c = reader_peek(r)) != -1 && c != '\n')
				reader_next(r);
		}
		reader_next(r);
	}
}

bool			reader_cmp(t_mtl_reader *r, char *str)
{
	char c;
	size_t i;

	i = 0;
	while ((c = reader_peek(r)) != -1 && str[i] != '\0' && c == str[i])
	{
		reader_next(r);
		i++;
	}
	if (str[i] != '\0')
		return (false);
	return true;
}

t_mtl_error		read_mtl(t_mtl_reader *r, t_mtl *mtl)
{
	t_mtl_error	    err;
    t_mtl_material  material;
	char		c;

	skip_ws(r, true);
	*mtl = create_mtl(10);
	while ((c = reader_peek(r))!= -1 && c == 'n')
	{
		reader_next(r);
		if (reader_cmp(r, "ewmtl") == false)
			return (Wrong_Newmtl);
		skip_ws(r, false);
		if ((err = read_material(r, &material)) != No_Error)
			return (err);
		if (append_material(mtl, material) == false)
			return (Error_Malloc);
	}
	return (No_Error);
}
