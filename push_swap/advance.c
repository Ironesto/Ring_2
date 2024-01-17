/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:30:19 by gpaez-ga          #+#    #+#             */
/*   Updated: 2023/12/21 19:48:38 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	summov(t_stk *stack_a, t_stk *stack_b, int i)
{
	int	temp;

	if (stack_a->num[stack_b->num[i].pair].up
		< stack_a->num[stack_b->num[i].pair].down)
		temp = stack_a->num[stack_b->num[i].pair].up;
	else
		temp = stack_a->num[stack_b->num[i].pair].down;
	if (stack_b->num[i].up < stack_b->num[i].down)
		temp += stack_b->num[i].up;
	else
		temp += stack_b->num[i].down;
	return (temp);
}

int	choice(t_stk *stack_a, t_stk *stack_b)
{
	int	i;
	int	temp;
	int	res;
	int	temp2;

	i = -1;
	res = 0;
	while (i++ < stack_b->targ - 1)
	{
		temp2 = summov(stack_a, stack_b, i);
		if (temp2 < temp && i + 1 < stack_b->targ)
		{
			temp = temp2;
			res = i;
		}
	}
	return (res);
}

void	ft_if(int mova, int movb, t_stk *stack_a, t_stk *stack_b)
{
	if (movb == 0 && mova == 0)
		return (ft_printf("pa\n"), push(stack_a, stack_b));
	if (movb > 0 && mova > 0)
		return (ft_printf("rr\n"), rotate(stack_a), rotate(stack_b),
			ft_if(mova - 1, movb - 1, stack_a, stack_b));
	if (movb < 0 && mova < 0)
		return (ft_printf("rrr\n"), rotinv(stack_a), rotinv(stack_b),
			ft_if(mova + 1, movb + 1, stack_a, stack_b));
	if (movb > 0)
		return (ft_printf("rb\n"), rotate(stack_b),
			ft_if(mova, movb - 1, stack_a, stack_b));
	if (movb < 0)
		return (ft_printf("rrb\n"), rotinv(stack_b),
			ft_if(mova, movb + 1, stack_a, stack_b));
	if (mova > 0)
		return (ft_printf("ra\n"), rotate(stack_a),
			ft_if(mova - 1, movb, stack_a, stack_b));
	if (mova < 0)
		return (ft_printf("rra\n"), rotinv(stack_a),
			ft_if(mova + 1, movb, stack_a, stack_b));
}

void	push_swap(t_stk *stack_a, t_stk *stack_b)
{
	int	i;
	int	mova;
	int	movb;

	if (stack_b->targ > 0)
	{
		position(stack_b);
		position(stack_a);
		findpair(stack_a, stack_b);
		i = choice(stack_a, stack_b);
		if (stack_b->num[i].up > stack_b->num[i].down)
			movb = -stack_b->num[i].down;
		else
			movb = stack_b->num[i].up;
		if (stack_a->num[stack_b->num[i].pair].up
			> stack_a->num[stack_b->num[i].pair].down)
			mova = -stack_a->num[stack_b->num[i].pair].down;
		else
			mova = stack_a->num[stack_b->num[i].pair].up;
		ft_if(mova, movb, stack_a, stack_b);
	}
	return ;
}
