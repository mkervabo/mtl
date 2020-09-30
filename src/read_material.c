#include "mtl.h"

t_mtl_error		read_str(t_mtl_reader *r, char **str)
{
	int16_t c;
	size_t size;
	size_t i;

	size = 10;
	if (!(*str = (char*)malloc(sizeof(char) * size)))
		return (Error_Malloc);
	i = 0;
	while ((c = reader_peek(r)) != -1 && c != '\n' && c != ' ' && c != '\t')
	{
		if (append_char(str, c, &size, i) == false)
			return (Error_Malloc);
		i++;
		reader_next(r);
	}
	if (append_char(str, '\0', &size, i) == false)
			return (Error_Malloc);
	return (No_Error);
}

t_mtl_error     read_illum(t_mtl_reader *r, t_mtl_material *material)
{
    t_mtl_error err;
    double      illum;

    reader_next(r);
    if (reader_cmp(r, "llum") == false)
        return (Wrong_Illum);
    skip_ws(r, false);
    if ((err = read_digit(r, &illum)) != No_Error)
        return (err);
    if (illum != 0 & illum != 1 & illum != 2 & illum != 3 & illum != 4 & illum != 5
    & illum != 6 & illum != 7 & illum != 8 & illum != 9 & illum != 10)
        return (Invalid_Illum);
    else
        material->illum = illum;
    return (No_Error); 
}

t_mtl_error		read_sharpeness(t_mtl_reader *r, double *sharpness)
{
	read_digit(r, sharpness);
	if (*sharpness < 0.0 || *sharpness > 1000.0)
		return(Invalid_Sharpness_Value);
	return(No_Error);
}

static void     create_material(t_mtl_material *material)
{
    material->ka = (t_mtl_color){.a = 0.2, .b = 0.2, .c = 0.2};
    material->kd = (t_mtl_color){.a = 0.8, .b = 0.8, .c = 0.8};
    material->ks = (t_mtl_color){.a = 1.0, .b = 1.0, .c = 1.0};

	material->d = 1.0;
	material->sharpeness = 60;
	material->illum = 0;
	material->ni = 1.0;
	material->ns = 1000;

	material->ka_map = NULL;
	material->ks_map = NULL;
	material->kd_map = NULL;
	material->ns_map = NULL;
	material->ni_map = NULL;
}
t_mtl_error     read_material(t_mtl_reader *r, t_mtl_material *material)
{
    t_mtl_error err;
    char        c;

    if((err = read_str(r, &material->name)) != No_Error)
		return (err);
    create_material(material);
	skip_ws(r, true);
    while((c = reader_peek(r)) != -1 && c != 'n')
	{
		if (c == 'K')
		{
			if((err = read_material_k(r, material)) != No_Error)
                return(err);
		}
		else if (c == 'm')
		{
			while ((c = reader_peek(r)) != -1 && c != '\n')
				reader_next(r);
		}
		else if (c == 'd')
		{
            skip_ws(r, false);
            if((err = read_digit(r, &material->d)) != No_Error)
                return(err);
			if (material->d < 0 || material->d > 1)
				return(Invalid_D_Value);
		}
		else if (c == 'N')
		{
			if((err = read_material_n(r, material)) != No_Error)
                return(err);
		}
        else if (c == 'i')
		{
			if((err = read_illum(r, material)) != No_Error)
                return(err);
		}
		else if (c == 's')
		{
			if((err = read_sharpeness(r, &material->sharpeness)) != No_Error)
                return(err);
		}
		else
			while ((c = reader_peek(r)) != -1 && c != '\n')
				reader_next(r);
		skip_ws(r, true);
	}
    return(No_Error);
}