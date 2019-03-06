/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <ggranjon@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 19:30:47 by ggranjon     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 19:30:47 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

t_safe g_safe = {0, PTHREAD_MUTEX_INITIALIZER};

/*
** To be thread safe, we lock mutex when we act on the pointer
*/

void			thread_protection(char status)
{
	if (!g_safe.init)
	{
		if (!pthread_mutex_init(&g_safe.safe, NULL))
		{
			g_safe.init = 1;
			return ;
		}
		if (status == 0)
			pthread_mutex_lock(&(g_safe.safe));
		else
			pthread_mutex_unlock(&(g_safe.safe));
	}
}

void			print_hex(long nb)
{
	if (nb >= 16)
		print_hex(nb / 16);
	if (nb % 16 < 10)
		ft_putchar((char)(((nb % 16) + 48)));
	else
		ft_putchar((char)((nb % 16) + 55));
}

/*
** test if ptr is in a block
*/

static size_t	test_a_block(t_alloc_block *b, void *ptr)
{
	t_alloc_block	*find;

	find = b;
	while (find)
	{
		if ((void*)(find + 1) == ptr)
			return (find->size);
		find = find->next;
	}
	return (0);
}

/*
** return size of block if the block exists
*/

size_t			size_block(void *ptr)
{
	size_t	ret;

	if ((ret = test_a_block(init_n_ret(0)->tiny, ptr)))
		return (ret);
	else if ((ret = test_a_block(init_n_ret(0)->small, ptr)))
		return (ret);
	else if ((ret = test_a_block(init_n_ret(0)->large, ptr)))
		return (ret);
	return (0);
}

/*
** merge two blocks together
** just report size and next member
** we have to create two blocks because with only one we will loose a next
*/

void			merge_previous(t_alloc_block *b, t_alloc_block *prev)
{
	if (b && b->free && prev && prev->free && is_continuous(prev, b))
	{
		prev->next = b->next;
		prev->size = prev->size + b->size + sizeof(t_alloc_block);
	}
}
