/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_string.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/23 14:45:00 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/14 13:45:45 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_string(t_formatter *t, va_list lst)
{
	char *arg;
	char *tmp;

	if (ft_strchr(t->length, 'l') || t->type == 'S')
		return (get_wstring(t, lst));
	tmp = va_arg(lst, char *);
	arg = ft_strdup(tmp ? tmp : "(null)");
	ft_memdel((void **)&(t->to_replace));
	t->to_replace = arg;
	str_compute(t);
}
