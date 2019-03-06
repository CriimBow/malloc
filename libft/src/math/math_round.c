/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   math_round.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/16 11:08:09 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/14 13:45:45 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		math_round(double x)
{
	if (x < 0.0)
		return (int)(x - 0.5);
	else
		return (int)(x + 0.5);
}