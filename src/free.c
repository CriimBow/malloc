/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <ggranjon@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 19:30:22 by ggranjon     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 19:30:22 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
**  if we have to free the first large block
**  we need to put g_alloc large to NULL
*/

static char		free_large(t_alloc_block *b, void *ptr)
{
	t_alloc_block	*find;
	t_alloc_block	*save;

	find = b;
	if ((void*)(find + 1) == ptr)
	{
		save = find->next;
		munmap((void*)find, find->size + sizeof(t_alloc_block));
		init_n_ret(0)->large = save;
		return (1);
	}
	while (find && find->next)
	{
		if ((void*)(find->next + 1) == ptr)
		{
			save = find->next->next;
			munmap((void*)find->next, find->next->size + sizeof(t_alloc_block));
			find->next = save;
			return (1);
		}
		find = find->next;
	}
	return (0);
}

/*
** first merge previous is here to merge previous
** second merge previous is here to merge with the next node
*/

static char		free_small_tiny(t_alloc_block *b, void *ptr)
{
	t_alloc_block	*find;
	t_alloc_block	*prev;

	find = b;
	prev = NULL;
	while (find)
	{
		if ((void*)(find + 1) == ptr)
		{
			if (find->free)
				return (1);
			find->free = 1;
			ft_bzero((void*)(find + 1), find->size);
			merge_previous(find->next, find);
			merge_previous(find, prev);
			return (1);
		}
		prev = find;
		find = find->next;
	}
	return (0);
}

/*
** we have to find where the ptr is so :
**      first free tiny if ok return
**      else free small
**      else free large
** then return because we have test everything
*/

void			free(void *ptr)
{
	thread_protection(0);
	if (ptr == NULL)
		;
	else if (free_small_tiny(init_n_ret(0)->tiny, ptr))
		;
	else if (free_small_tiny(init_n_ret(0)->small, ptr))
		;
	else
		free_large(init_n_ret(0)->large, ptr);
	thread_protection(1);
}
