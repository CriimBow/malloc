/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <ggranjon@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 19:30:26 by ggranjon     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 19:30:26 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Create new alloc + cpy old data if can't reallocate
** ---
** if old size is >, to avoid segfault we cpy only new size
*/

static void	*create_new(void *ptr, size_t size, size_t old_size)
{
	void	*ret_ptr;

	if (!(ret_ptr = malloc(size)))
		return (NULL);
	if (size < old_size)
		ft_memcpy(ret_ptr, ptr, size);
	else
		ft_memcpy(ret_ptr, ptr, old_size);
	free(ptr);
	return (ret_ptr);
}

/*
** Same merge as merge in utils except there is no condition
*/

static void	local_merge_previous(t_alloc_block *b, t_alloc_block *prev)
{
	prev->next = b->next;
	prev->size = prev->size + b->size + sizeof(t_alloc_block);
}

/*
** Try to merge blocks in a zone according new size
** ---
** find block, if next free -> split to not use to much space.
** merge with next block -> recursive while old_size < size
** ---
** Here I choose if size < old_size to return the same ptr if there is no place
** for a new t_alloc_block structure.
** This choice is justified by the fact that I don't want to end up with a
** memory block where t_alloc_block structure cant fit. In this case, I would
** have a lost memory area.
*/

static void	*find_merge(t_alloc_block *b, void *ptr, size_t size,
		size_t old_size)
{
	t_alloc_block	*find;

	find = b;
	while (find && (void*)(find + 1) != ptr)
		find = find->next;
	if (!(find))
		return (NULL);
	if (size > old_size)
	{
		if (find->next && find->next->free)
		{
			if (find->next->size + find->size > size)
				split_block(find->next, size - old_size);
			local_merge_previous(find->next, find);
			return (realloc((void *)(find + 1), size));
		}
		else
			return (create_new(ptr, size, old_size));
	}
	if (find->size <= size + sizeof(t_alloc_block))
		return ((void*)(find + 1));
	return (split_block(find, size + sizeof(t_alloc_block)));
}

/*
** BIG IF is here to alloc new block if the new size can't be in the same zone
*/

void		*realloc(void *ptr, size_t size)
{
	void		*ret_ptr;
	size_t		old_size;

	thread_protection(0);
	old_size = size_block(ptr);
	if (size <= 0)
		ret_ptr = NULL;
	else if (size == old_size)
		return (ptr);
	else if (ptr == NULL)
		ret_ptr = malloc(size);
	else if (size > SMALL_SIZE || old_size > SMALL_SIZE || (size <= TINY_SIZE
	&& old_size > TINY_SIZE) || (size > TINY_SIZE && old_size <= TINY_SIZE))
		ret_ptr = create_new(ptr, size, old_size);
	else
	{
		if (size <= TINY_SIZE)
			ret_ptr = find_merge(init_n_ret(0)->tiny, ptr, size, old_size);
		else
			ret_ptr = find_merge(init_n_ret(0)->small, ptr, size, old_size);
	}
	thread_protection(1);
	return (ret_ptr);
}
