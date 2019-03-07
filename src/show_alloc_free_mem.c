/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   show_alloc_free_mem.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <ggranjon@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 19:30:28 by ggranjon     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 19:30:28 by ggranjon    ###    #+. /#+    ###.fr     */
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
		ft_putstr("0x");
		print_hex((long)((void*)(b + 1)));
		ft_putstr(" - ");
		print_hex((long)((void*)(b + 1) + b->size));
		ft_putstr(" : ");
		ft_putnbr(b->size);
		if (!(b->free))
			ft_putstr(" octets alloués\n");
		else
			ft_putstr(" octets libres\n");
		total += b->size;
		b = b->next;
	}
	return (total);
}

void						show_alloc_free_mem(void)
{
	unsigned long long	total;

	total = 0;
	thread_protection(0);
	if (!(init_n_ret(0)))
		return ;
	ft_putstr("TINY : 0x");
	print_hex((long)(init_n_ret(0)->tiny));
	ft_putstr("\n");
	total += count_print_alloc(init_n_ret(0)->tiny);
	ft_putstr("SMALL : 0x");
	print_hex((long)(init_n_ret(0)->small));
	ft_putstr("\n");
	total += count_print_alloc(init_n_ret(0)->small);
	ft_putstr("LARGE : 0x");
	print_hex((long)(init_n_ret(0)->large));
	ft_putstr("\n");
	total += count_print_alloc(init_n_ret(0)->large);
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
	thread_protection(1);
}
