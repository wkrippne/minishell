/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:39:25 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 10:53:20 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

/* Cleanups now */
void	free_all(t_msh *data)
{
	if (data->pid)
		free(data->pid);
	free_t_env(data->ppt->list);
	free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_prompt(data->ppt);
	free (data->ppt);
	close_pipes(data);
	free_fd(data);
	free_lstscom(data);
	free (data);
	unlink(".heredoc");
}

void	free_fork(t_msh *data)
{
	if (data->pid)
		free(data->pid);
	free_t_env(data->ppt->list);
	free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_prompt(data->ppt);
	free (data->ppt);
	free_fd(data);
	free_lstscom(data);
	free (data);
	unlink(".heredoc");
}

void	free_over(t_msh *data)
{
	if (data->pid)
		free(data->pid);
	free_t_env(data->ppt->list);
	free_t_exp(data->export->exp);
	free (data->export);
	free_table(data->env);
	free_prompt(data->ppt);
	free (data->ppt);
	close_pipes(data);
	free_fd(data);
	free (data);
	unlink(".heredoc");
}

void	free_prompt(t_ppt *root)
{
	free (root->prompt);
	free (root->user);
	free (root->s_manager);
	free (root->home);
	free (root->path);
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free (table[i]);
		i++;
	}
	free (table);
}
