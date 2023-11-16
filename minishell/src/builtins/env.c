/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:09:48 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 10:36:29 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* this goes through the list of environment variables and displays
** each variables along with the value. prints it followed by \n
** after ot exits successfully setting exit status to 0 */
void	builtin_env(t_msh *data)
{
	t_env	*node;

	node = data->ppt->list;
	while (node)
	{
		ft_putstr_fd(node->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(node->value, 1);
		ft_putstr_fd("\n", 1);
		node = node->next;
	}
	g_exit_status = 0;
}
