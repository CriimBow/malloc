/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ht_new.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <ggranjon@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/23 13:17:41 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/14 13:45:45 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_hashtable	*ht_new(size_t size)
{
	t_hashtable *hasht;

	hasht = ft_memalloc(sizeof(t_hashtable));
	if (hasht)
	{
		hasht->size = size;
		hasht->heaps = ft_memalloc(size);
		hasht->free_func = free;
	}
	return (hasht);
}
