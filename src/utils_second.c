/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_second.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <ggranjon@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 19:46:27 by ggranjon     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 19:46:27 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** take the size needed if the is enough frees space
**   save is here if the block is between (allocated) blocks
*/

void	*split_block(t_alloc_block *block, size_t size_needed)
{
	t_alloc_block	*save_next;

	save_next = block->next;
	block->free = 0;
	block->next = (void*)block + size_needed;
	block->next->free = 1;
	block->next->size = block->size - size_needed;
	block->size = size_needed - sizeof(t_alloc_block);
	block->next->next = save_next;
	return ((void*)(block + 1));
}

/*
** is_continuous checks if addresses of b1 and b2 are consecutive
*/

char	is_continuous(t_alloc_block *b1, t_alloc_block *b2)
{
	return ((unsigned long)b2 - (unsigned long)b1
	== sizeof(t_alloc_block) + b1->size);
}