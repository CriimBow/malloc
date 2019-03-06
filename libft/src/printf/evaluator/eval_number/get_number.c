/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_number.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/28 10:05:21 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/14 13:45:45 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_number(t_formatter *t, va_list lst)
{
	intmax_t	val;
	char		*str;

	get_val(t, &val, lst);
	ft_memdel((void **)&(t->to_replace));
	str = ft_memalloc(sizeof(char) * 256);
	str_intmax(str, val, 10, BASE);
	t->to_replace = str;
	number_compute(t);
}

void	get_unumber(t_formatter *t, va_list lst)
{
	uintmax_t	val;
	char		*str;

	get_uval(t, &val, lst);
	ft_memdel((void **)&(t->to_replace));
	str = ft_memalloc(sizeof(char) * 256);
	str_uintmax(str, val, 10, BASE);
	t->to_replace = str;
	number_compute(t);
}
