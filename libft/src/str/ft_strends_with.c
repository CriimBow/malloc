/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strends_with.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/10 17:55:55 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/14 13:45:45 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strends_with(const char *s, char c)
{
	if (ft_strlen(s) > 0)
		return (s[ft_strlen(s) - 1] == c);
	return (0);
}

int		ft_strends_with_str(const char *s, char *str)
{
	int64_t i;
	int64_t j;

	i = (int64_t)ft_strlen(s) - 1;
	j = (int64_t)ft_strlen(str) - 1;
	while (j >= 0 && i >= 0 && s[i] == str[j])
	{
		i--;
		j--;
	}
	return (j == -1);
}
