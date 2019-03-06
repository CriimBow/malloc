/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <ggranjon@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 19:30:25 by ggranjon     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 19:30:25 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

t_allocations	*g_allocs = NULL;

/*
**   First alloc ->
**   alloc tiny and small zones depending the input size
**   to save memory
**   return the global variable
*/

t_allocations	*init_n_ret(size_t size)
{
	if (!(g_allocs))
	{
		if ((g_allocs = mmap(0, sizeof(t_allocations), PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			exit(1);
		ft_bzero(g_allocs, sizeof(t_allocations));
	}
	if (size > 0 && size <= TINY_SIZE && !(g_allocs->tiny))
	{
		if ((g_allocs->tiny = (t_alloc_block*)mmap(NULL, TINY_F_MAP, PROT_READ
		| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			exit(1);
		g_allocs->tiny->size = TINY_F_MAP;
		g_allocs->tiny->free = 1;
		g_allocs->tiny->next = NULL;
	}
	else if (size > TINY_SIZE && size <= SMALL_SIZE && !(g_allocs->small))
	{
		if ((g_allocs->small = (t_alloc_block*)mmap(NULL, SMALL_F_MAP, PROT_READ
		| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			exit(1);
		g_allocs->small->size = SMALL_F_MAP;
		g_allocs->small->free = 1;
		g_allocs->small->next = NULL;
	}
	return (g_allocs);
}

/*
** Go to last block,
** increase space depending if it's a TINY or SMALL size
** restart malloc process
*/

static void		*increase_zone(t_alloc_block *alloc, size_t size)
{
	t_alloc_block	*to_ret;

	to_ret = alloc;
	while (to_ret && to_ret->next)
		to_ret = to_ret->next;
	if (size > 0 && size <= TINY_SIZE)
	{
		if ((to_ret->next = (t_alloc_block*)mmap(NULL, TINY_F_MAP, PROT_READ |
		PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			exit(1);
		to_ret->next->size = TINY_F_MAP;
		to_ret->next->free = 1;
		to_ret->next->next = NULL;
	}
	else if (size > TINY_SIZE && size <= SMALL_SIZE)
	{
		if ((to_ret->next = (t_alloc_block*)mmap(NULL, SMALL_F_MAP, PROT_READ
		| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			exit(1);
		to_ret->next->size = SMALL_F_MAP;
		to_ret->next->free = 1;
		to_ret->next->next = NULL;
	}
	return (general_alloc(alloc, size));
}

/*
**  if large global doesnt exist, alloc large
**  else go to last block and alloc next block
*/

void			*alloc_large(t_alloc_block *alloc, size_t size,
		size_t alloc_size)
{
	t_alloc_block	*to_ret;

	if (!(alloc))
	{
		if ((g_allocs->large = (t_alloc_block*)mmap(NULL, alloc_size, PROT_READ
		| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			return (NULL);
		bzero(g_allocs->large, sizeof(t_alloc_block));
		g_allocs->large->size = size;
		return ((void*)(g_allocs->large + 1));
	}
	to_ret = alloc;
	while (to_ret && to_ret->next)
		to_ret = to_ret->next;
	if ((to_ret->next = (t_alloc_block*)mmap(NULL, alloc_size, PROT_READ
	| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	bzero(to_ret->next, sizeof(t_alloc_block));
	to_ret->next->size = size;
	return ((void*)(to_ret->next + 1));
}

/*
** find free block which can fit to the input size + struct size
** else increse zone if size is <= to SMALL size
**         else we are in large case so alloc large block
*/

void			*general_alloc(t_alloc_block *alloc, size_t size)
{
	t_alloc_block	*b;
	size_t			size_needed;

	size_needed = size + sizeof(t_alloc_block);
	b = alloc;
	while (b && !(b->free && b->size >= size_needed))
		b = b->next;
	if (b)
		return (split_block(b, size_needed));
	else
	{
		if (size <= SMALL_SIZE)
			return (increase_zone(alloc, size));
		else
			return (alloc_large(alloc, size, size_needed));
	}
}

/*
** if size <= 0 return NULL because cant alloc <= 0 space
** else redistribute to general alloc with the good zone
** so if size <= to tiny send tiny zone, etc.
*/

void			*malloc(size_t size)
{
	void	*ptr;

	thread_protection(0);
	if (size <= 0)
		ptr = NULL;
	else if (size <= TINY_SIZE)
		ptr = general_alloc(init_n_ret(size)->tiny, size);
	else if (size <= SMALL_SIZE)
		ptr = general_alloc(init_n_ret(size)->small, size);
	else
		ptr = general_alloc(init_n_ret(size)->large, size);
	thread_protection(1);
	return (ptr);
}
