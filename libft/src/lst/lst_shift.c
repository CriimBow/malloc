/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_shift.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/26 11:05:15 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/14 13:45:45 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*lst_shift(t_list **l)
{
	t_list *tmp;

	if (!*l)
		return (NULL);
	tmp = *l;
	*l = tmp->next;
	return (tmp);
}