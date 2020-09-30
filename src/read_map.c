#include "mtl.h"

t_mtl_error read_material_map(t_mtl_reader *r, t_mtl_material *material)
{
    char c;
    t_mtl_error err;
    
    if (reader_cmp(r, "ap_") == false)
        return (Wrong_Illum);
    reader_next(r);
    if((c = reader_peek(r)) == 'K')
    {
        reader_next(r);
        if ((c = reader_peek(r)) == 'a')
        {
            if ((err = read_str(r, &material->ka_map)) != No_Error)
                return (err);
        }
        else if (c == 's')
        {
            if ((err = read_str(r, &material->ks_map)) != No_Error)
                return (err);
        }
        else if (c == 'd')
        {
            if ((err = read_str(r, &material->kd_map)) != No_Error)
                return (err);
        }
        else
            while ((c = reader_peek(r)) != -1 && c != '\n')
                reader_next(r);
    }
    else if (c == 'N')
    {
        reader_next(r);
        if ((c = reader_peek(r)) == 's')
        {
            if ((err = read_str(r, &material->ns_map)) != No_Error)
                return (err);
        }
        else if (c == 'i')
        {
            if ((err = read_str(r, &material->ni_map)) != No_Error)
                return (err);
        }
        else
            while ((c = reader_peek(r)) != -1 && c != '\n')
                reader_next(r);
    }
    else
        while ((c = reader_peek(r)) != -1 && c != '\n')
            reader_next(r);
    return (No_Error);
}