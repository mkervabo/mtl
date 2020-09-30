#include "mtl.h"

t_mtl_error read_material_color(t_mtl_reader *r, t_mtl_color *color)
{
    t_mtl_error err;
    
    skip_ws(r, false);
    if ((err = read_digit(r, &color->a)) != No_Error)
        return (err);
    skip_ws(r, false);
    if ((err = read_digit(r, &color->b)) != No_Error)
        return (err);
    skip_ws(r, false);
    if ((err = read_digit(r, &color->c)) != No_Error)
        return (err);
    if (color->a > 1 || color->a < 0 || color->b > 1 || color->b < 0 || color->c > 1 || color->c < 0)
        return(Invalid_Color);
    return (No_Error);
}

t_mtl_error read_material_k(t_mtl_reader *r, t_mtl_material *material)
{
    char c;
    t_mtl_error err;
    
    reader_next(r);
    c = reader_peek(r);
    if (c == 'a')
    {
        if ((err = read_material_color(r, &material->ka)) != No_Error)
            return (err);
    }
    else if (c == 's')
    {
        if ((err = read_material_color(r, &material->ks)) != No_Error)
            return (err);
    }
    else if (c == 'd')
    {
        if ((err = read_material_color(r, &material->kd)) != No_Error)
            return (err);
    }
    else
        while ((c = reader_peek(r)) != -1 && c != '\n')
            reader_next(r);
    return (No_Error);
}