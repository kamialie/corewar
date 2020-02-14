#ifndef LC_H
# define LC_H
# include <fcntl.h>
# include "../../libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "op.h"
# include "get_next_line.h"

typedef struct      s_label
{
    int             offset;
    char            *name;
}                   t_label;

typedef struct      s_arg
{
    int             arg_val;
    int             arg_type;
}                   t_arg;
typedef struct      s_com
{
    t_label         label;
    t_arg           args[3];
    int             code;
    size_t          size;
}                   t_com;
typedef struct      s_oper
{
    //label
    t_com           com;
    struct s_oper   *next; 
    struct s_oper   *last
}                   t_oper;

typedef struct      s_state
{
    int             init;
}                   t_state;

typedef struct      s_nc
{
    char            *name;
    char            *comment;
}                   t_nc;



#endif