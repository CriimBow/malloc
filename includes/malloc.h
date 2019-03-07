/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/05 11:25:35 by ggranjon     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/05 11:27:46 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/mman.h>
# include <pthread.h>
# include "libft.h"

# define TINY_SIZE		(size_t)(getpagesize() / 32)
# define SMALL_SIZE		(size_t)(TINY_SIZE * 8)
# define TINY_F_MAP		(size_t)(25 * getpagesize())
# define SMALL_F_MAP	(size_t)(100 * getpagesize())

typedef struct		s_alloc_block
{
	size_t					size;
	char					free;
	struct s_alloc_block	*next;
}					t_alloc_block;

typedef struct		s_allocations
{
	t_alloc_block			*tiny;
	t_alloc_block			*small;
	t_alloc_block			*large;
}					t_allocations;

typedef struct		s_safe
{
	char			init;
	pthread_mutex_t	safe;
}					t_safe;

t_allocations		*init_n_ret(size_t size);
void				thread_protection(char status);
void				merge_previous(t_alloc_block *b, t_alloc_block *prev);
void				print_hex(long nb);
void    			ft_putnbr(unsigned long long nb);

size_t				size_block(void *ptr);
void				*split_block(t_alloc_block *block, size_t size_needed);
char				is_continuous(t_alloc_block *b1, t_alloc_block *b2);

void				*general_alloc(t_alloc_block *alloc, size_t size);

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t num, size_t size);

void				show_alloc_mem(void);
void				show_alloc_free_mem(void);

void				fuck_norm(t_allocations *g_allocs);

#endif
