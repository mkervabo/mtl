#include "mtl.h"

t_mtl_error read_material_n(t_mtl_reader *r, t_mtl_material *material)
{
    char c;
    t_mtl_error err;
    
    reader_next(r);
    c = reader_peek(r);
    if (c == 'i')
    {
        if ((err = read_digit(r, &material->ni)) != No_Error)
            return (err);
        if (material->ni < 0.001 || material->ni > 10)
            return(Invalid_Ni_Value);
    }
    else if (c == 's')
    {
        if ((err = read_digit(r, &material->ns)) != No_Error)
            return (err);
        if (material->ns < 0 || material->ns > 1000)
            return(Invalid_Ns_Value);
    }
    else
        while ((c = reader_peek(r)) != -1 && c != '\n')
            reader_next(r);
    return (No_Error);
}