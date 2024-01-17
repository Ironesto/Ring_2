/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:42:16 by gpaez-ga          #+#    #+#             */
/*   Updated: 2023/12/23 18:21:37 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stk *stack)
{
	int	aux;

	aux = stack->num[0].nbr;
	stack->num[0].nbr = stack->num[1].nbr;
	stack->num[1].nbr = aux;
}

void	rotate(t_stk *stack)
{
	int	aux;
	int	i;
	int	k;

	aux = 0;
	i = stack->num[0].nbr;
	while (aux < stack->targ)
	{
		stack->num[aux].nbr = stack->num[aux + 1].nbr;
		aux++;
	}
	stack->num[aux - 1].nbr = i;
}

void	rotinv(t_stk *stack)
{
	int	aux;
	int	i;
	int	k;

	aux = 0;
	if (stack->num[0].nbr == 0 && stack->num[1].nbr == 0)
		return ;
	i = stack->num[stack->targ - 1].nbr;
	aux = stack->targ - 1;
	while (aux > 0)
	{
		stack->num[aux].nbr = stack->num[aux - 1].nbr;
		aux--;
	}
	stack->num[0].nbr = i;
}

void	push(t_stk *ent, t_stk *out)
{
	int	aux;
	int	k;

	if (out->num[0].nbr == 0 && out->num[1].nbr == 0)
		return ;
	aux = 0;
	rotinv(ent);
	ent->num[ent->targ].nbr = ent->num[0].nbr;
	ent->num[0].nbr = out->num[0].nbr;
	out->num[0].nbr = 0;
	rotate(out);
	out->targ -= 1;
	ent->targ += 1;
}
