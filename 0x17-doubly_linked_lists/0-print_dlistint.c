#include <stdio.h>
#include "lists.h"

size_t print_dlistint(const dlistint_t *h)
{
    size_t nodes = 0;

    while (h != NULL)
    {
        printf("%d\n", h->n);
        h = h->next;
        nodes++;
    }

    return nodes;
}
