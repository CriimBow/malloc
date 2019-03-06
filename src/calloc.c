/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   calloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 19:33:04 by ggranjon     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 19:33:09 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t num, size_t size)
{
	void	*ret_ptr;

	if (!(ret_ptr = malloc(num * size)))
		return (NULL);
	ft_bzero(ret_ptr, num * size);
	return (ret_ptr);
}
