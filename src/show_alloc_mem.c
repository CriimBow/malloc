/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   show_alloc_mem.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <ggranjon@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 19:30:43 by ggranjon     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 19:30:43 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static unsigned long long	count_print_alloc(t_alloc_block *b)
{
	unsigned long long	total;

	total = 0;
	while (b)
	{
		if (!(b->free))
		{
			ft_printf("0x");
			print_hex((long)((void*)(b + 1)));
			ft_printf(" - ");
			print_hex((long)((void*)(b + 1) + b->size));
			ft_printf(" : %li octets alloués\n", b->size);
			total += b->size;
		}
		b = b->next;
	}
	return (total);
}

void						show_alloc_mem(void)
{
	unsigned long long	total;

	total = 0;
	thread_protection(0);
	ft_printf("TINY : 0x");
	print_hex((long)(init_n_ret(0)->tiny));
	ft_printf("\n");
	total += count_print_alloc(init_n_ret(0)->tiny);
	ft_printf("SMALL : 0x");
	print_hex((long)(init_n_ret(0)->small));
	ft_printf("\n");
	total += count_print_alloc(init_n_ret(0)->small);
	ft_printf("LARGE : 0x");
	print_hex((long)(init_n_ret(0)->large));
	ft_printf("\n");
	total += count_print_alloc(init_n_ret(0)->large);
	ft_printf("Total : %i octets\n", total);
	thread_protection(1);
}
