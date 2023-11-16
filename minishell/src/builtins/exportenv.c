/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:25:31 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 10:39:10 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* This function removes an environment variable from the program
 state, it checka if the variable is the 1st one or exists, if so
 we dont perfom any further actions */
void	ft_unset(t_msh *data, char *key)
{
	if (check_exp_first_node(data, key))
		return ;
	if (check_exp_till_end(data, key))
		return ;
}
