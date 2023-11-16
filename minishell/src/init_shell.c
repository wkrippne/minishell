/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkrippne <wkrippne@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:31:04 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/19 11:56:41 by wkrippne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* This creates a data structure to keep track of the environment variables and
** exported variables*/
static void	init_export_env(t_msh *data)
{
	data->export = (t_exp *)malloc(sizeof(t_exp));
	data->export->env = data->ppt->list;
	data->export->exp = NULL;
	if (!data->export)
		put_str_exit("Error: Malloc of data->export failed\n", 1);
}

/* this func prepairs the data structure called data, that stores the below
** info needed by the shell, we also set up structures to manage variables
** and creates a table for efficient access to these variables*/
t_msh	*init_data(t_msh *data, char **env)
{
	data->ppt = (t_ppt *)malloc(sizeof(t_ppt));
	data->ppt->n_exec = 0;
	data->ppt->path = NULL;
	data->ppt->prompt = NULL;
	data->npipe = 0;
	data->nscom = 0;
	data->fd = NULL;
	data->export = NULL;
	data->heredoc = 0;
	data->pid = NULL;
	env_to_list(data, env);
	init_export_env(data);
	init_env_table(data);
	return (data);
}

/* we create a table that holds all the env variables, where each
** variable represents a string with the format keky=value*/
static void	init_env_table_complement(t_msh *data, t_env *tmp)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (tmp)
	{
		j = -1;
		data->env[i] = malloc(sizeof(char) * (ft_strlen(tmp->key)
					+ ft_strlen(tmp->value) + 2));
		while (tmp->key[++j])
			data->env[i][j] = tmp->key[j];
		data->env[i][j++] = '=';
		k = 0;
		while (tmp->value[k])
			data->env[i][j++] = tmp->value[k++];
		data->env[i][j] = '\0';
		tmp = tmp->next;
		i++;
	}
	data->env[i] = NULL;
}

/* This prepares the table to hold the env variables and copies the variables
** into the table so they can be accessed easily later on*/
void	init_env_table(t_msh *data)
{
	t_env	*tmp;

	data->env = (char **)malloc(sizeof(char *)
			* (size_of_list(data->ppt->list) + 1));
	if (!data->env)
	{
		ft_putstr_fd("Error: Env table malloc failed\n", 2);
		return ;
	}
	tmp = data->ppt->list;
	init_env_table_complement(data, tmp);
}
