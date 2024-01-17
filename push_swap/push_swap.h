/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:03:53 by gpaez-ga          #+#    #+#             */
/*   Updated: 2023/12/21 05:04:00 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"

typedef struct s_num
{
	int	nbr;
	int	pos;
	int	up;
	int	down;
	int	pair;
}	t_num;

typedef struct s_stk
{
	int		targ;
	t_num	*num;
	char	**spt;
}	t_stk;

		//moves.c
void	swap(t_stk *stack);
void	rotate(t_stk *stack);
void	rotinv(t_stk *stack);
void	push(t_stk *ent, t_stk *out);

		//tools.c
long	ft_atoli(const char *nptr);
int		ft_isalldigit(char *wrd);
t_stk	simp(t_stk *stack);
void	position(t_stk *stack);

		//valid.c
char	**ft_free(char **str);
int		savenums(int argc, char **argv, t_stk *stack);
int		compnums(int argc, char **argv, t_stk *stack);
int		comprep(t_stk stack, int tot);

		//basic.c
void	threenums(t_stk *stack);
void	movemid(t_stk *stack_b, t_stk *stack_a);
void	primorder(t_stk *stack_b, t_stk *stack);
void	findpair(t_stk *stk_a, t_stk *stk_b);

		//advance.c
int		summov(t_stk *stack_a, t_stk *stack_b, int i);
int		choice(t_stk *stack_a, t_stk *stack_b);
void	push_swap(t_stk *stack_a, t_stk *stack_b);

void	ft_see(t_stk stack_a, t_stk stack_b);
#endif