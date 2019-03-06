/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_find.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/26 11:23:04 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/14 13:45:45 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*lst_find(t_list *list, void *data_ref, int (*cmp)())
{
	while (list)
	{
		if ((*cmp)(list->content, data_ref) == 1)
			return (list);
		list = list->next;
	}
	return (NULL);
}
