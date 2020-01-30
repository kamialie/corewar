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


typedef struct      s_oper
{
    t_label         *label;
    int             op_num;
    t_arg           args[3];
    size_t          size;
    size_t          rel_size;
    t_oper          *next;
}                   t_oper;
typedef struct      s_chain
{
    t_oper          *oper;
    struct s_chain  *next;
}                   t_chain;

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