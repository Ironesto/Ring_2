/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:40:47 by gpaez-ga          #+#    #+#             */
/*   Updated: 2023/12/21 18:53:01 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static long	ft_putnbr_atoi(const char *str, int i)
{
	long	num;

	num = 0;
	while (str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		num += (str[i] - '0');
		num *= 10;
		i++;
	}
	num += (str[i] - '0');
	return (num);
}

long	ft_atoli(const char *nptr)
{
	long	i;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '+' && nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
		return (ft_putnbr_atoi(nptr, i + 1));
	if (nptr[i] == '-' && nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
		return (ft_putnbr_atoi(nptr, i + 1) * -1);
	if (nptr[i] >= '0' && nptr[i] <= '9')
		return (ft_putnbr_atoi(nptr, i));
	return (0);
}

int	ft_isalldigit(char *wrd)
{
	int	i;

	i = 1;
	if (!ft_strchr("+-0123456789", wrd[0]))
		return (1);
	if ((wrd[0] == '+' || wrd[0] == '-') && wrd[1] == '\0')
		return (1);
	while (wrd[i])
	{
		if (!ft_strchr("0123456789", wrd[i]))
			return (1);
		i++;
	}
	return (0);
}

t_stk	simp(t_stk *stack)
{
	int		i;
	int		k;
	t_stk	indx;

	indx.num = malloc(sizeof(t_num) * stack->targ);
	indx.targ = stack->targ;
	i = 0;
	while (i < stack->targ)
	{
		k = 0;
		while (k < stack->targ)
		{
			if (stack->num[i].nbr > stack->num[k].nbr)
			{
				indx.num[i].nbr = indx.num[i].nbr + 1;
			}
			k++;
		}
		i++;
	}
	free(stack->num);
	return (indx);
}

void	position(t_stk *stack)
{
	int	i;

	i = stack->targ - 1;
	while (i + 1 > 0)
	{
		stack->num[i].pos = i;
		stack->num[i].up = i;
		stack->num[i].down = stack->targ - i;
		i--;
	}
}
