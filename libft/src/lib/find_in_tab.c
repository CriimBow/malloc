/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_in_tab.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <ggranjon@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 09:55:59 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/14 13:45:45 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		find_in_tab(char **t, char *arg)
{
	while (*t)
	{
		if (ft_strequ(arg, *t))
			return (1);
		t++;
	}
	return (0);
}
