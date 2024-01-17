/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:41:53 by gpaez-ga          #+#    #+#             */
/*   Updated: 2023/12/23 18:22:45 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	threenums(t_stk *stack)
{
	int	zero;
	int	one;
	int	two;

	zero = stack->num[0].nbr;
	one = stack->num[1].nbr;
	two = stack->num[2].nbr;
	if (zero > one && zero > two)
	{
		ft_printf("ra\n");
		rotate(stack);
	}
	if (one > zero && one > two)
	{
		ft_printf("rra\n");
		rotinv(stack);
	}
	if (two > one && zero < two && one < zero)
	{
		ft_printf("sa\n");
		swap(stack);
	}
	if (zero > one || zero > two || one > two)
		threenums(stack);
}

void	movemid(t_stk *stack_b, t_stk *stack_a)
{
	int	tot;
	int	i;

	i = 0;
	tot = stack_a->targ / 2;
	while (i < tot * 2)
	{
		if (stack_a->num[0].nbr > tot)
		{
			ft_printf("pb\n");
			push(stack_b, stack_a);
		}
		else
		{
			ft_printf("ra\n");
			rotate(stack_a);
		}
		i++;
	}
	while (stack_a->targ > 3)
	{
		ft_printf("pb\n");
		push(stack_b, stack_a);
	}
	threenums(stack_a);
}

void	primorder(t_stk *stack_b, t_stk *stack)
{
	int	i;

	i = 0;
	while (i < stack->targ && stack->num[i].nbr == i)
		i++;
	if (stack->targ == 2 && i != stack->targ)
	{
		ft_printf("sa\n");
		swap(stack);
		return ;
	}
	if (i == stack->targ)
		return ;
	if (stack->targ == 3 && i != stack->targ)
		threenums(stack);
	if (stack->targ > 3)
		movemid(stack_b, stack);
	return ;
}

static void	findpair2(t_stk *stk_a, t_stk *stk_b, int i, int j)
{
	int	temp;

	temp = stk_a->targ + stk_b->targ;
	stk_b->num[j].pair = temp + 1;
	while (i < stk_a->targ)
	{
		if (stk_a->num[i].nbr < temp && stk_a->num[i].nbr > stk_b->num[j].nbr)
		{
			stk_b->num[j].pair = stk_a->num[i].pos;
			temp = stk_a->num[i].nbr;
		}
		i++;
	}
	temp = stk_a->targ + stk_b->targ;
	if (stk_b->num[j].pair == temp + 1)
	{
		while (i-- > 0)
		{
			if (stk_a->num[i].nbr < temp)
			{
				stk_b->num[j].pair = stk_a->num[i].pos;
				temp = stk_a->num[i].nbr;
			}
		}
	}
}

void	findpair(t_stk *stk_a, t_stk *stk_b)
{
	int	i;
	int	j;
	int	temp;

	j = 0;
	while (j < stk_b->targ)
	{
		i = 0;
		findpair2(stk_a, stk_b, i, j);
		j++;
	}
}
