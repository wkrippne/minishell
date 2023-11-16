/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:32:06 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 10:59:16 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

/* This prepares the command to read input from a specific source and write
** output to a sprecific destination*/
void	open_redir(t_msh *data)
{
	open_redir_in(data);
	open_redir_out(data);
}

void	do_redir(t_msh *data)
{
	open_redir(data);
}

/* Responsible for updating the input and output of a command in a program*/
void	redirect_updt(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}
