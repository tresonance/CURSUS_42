#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct     s_list
{
    int            data;
    struct s_list  *next;
}                  t_list;

int        cycle_detector(const t_list *list);

#endif
