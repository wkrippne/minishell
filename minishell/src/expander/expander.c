/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:53:07 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 13:45:12 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

/* check_expander checks and expands variables on a string by iterating through
** each character, detecting variables indicated by $ and perform the expansion
** using the do_expander func*/
void	check_expander(t_msh *data, void **content)
{
	int		i;
	char	quote;
	char	*arg;
	char	*expanded;

	if (full_dolar((char *)(*content)))
		return ;
	i = -1;
	quote = '\0';
	arg = (char *)(*content);
	data->num = 0;
	expanded = (char *)malloc(sizeof(char) * (size_expand(data, arg) + 1));
	while (arg[++i])
	{
		quote = quote_value(arg[i], quote);
		if (arg[i] == '$' && quote != '\'')
			do_expander(data, arg, &expanded, &i);
		else
			expanded[data->num++] = arg[i];
	}
	expanded[data->num] = '\0';
	free (*content);
	*content = expanded;
}

/* This func goes through a list of arguements and check if any arguement
** contains a dollar sign, if it is founc it expands the environmental
** variable by replacing it with it's value*/
static void	do_expand_lstarg(t_msh *data)
{
	t_list	*tmp;

	tmp = data->lst_cmd->lstarg;
	while (tmp)
	{
		if (ft_strrchr((char *)tmp->content, '$'))
			check_expander(data, &tmp->content);
		tmp = tmp->next;
	}
}

/* this func goes through each output redirection in the shell command
** if a filenameof a redirection contains the $ character it means there
** is a variable that needs to be expanded and we call check_expander*/
static void	do_expand_redout(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmpred;

	tmp = data->lst_cmd->lstofredirout;
	while (tmp)
	{
		tmpred = (t_redir *)(tmp->content);
		if (ft_strrchr(tmpred->filename, '$'))
			check_expander(data, (void **)(&tmpred->filename));
		tmp = tmp->next;
	}
}

/* this func is used to expand the variables in the input redir filenames
** within a command*/
static void	do_expand_redin(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmpred;

	tmp = data->lst_cmd->lstofredirin;
	while (tmp)
	{
		tmpred = (t_redir *)(tmp->content);
		if (ft_strrchr(tmpred->filename, '$') && tmpred->type == LESS)
			check_expander(data, (void **)(&tmpred->filename));
		tmp = tmp->next;
	}
}

/*this goes through each command and expands it's variables in the arguements
** output and input redir filenames, it does it by calling it separately and
** once they have been processed it finishes the execution*/
void	expander(t_msh *data)
{
	t_scom	*tmp;

	tmp = data->lst_cmd;
	while (tmp)
	{
		do_expand_lstarg(data);
		do_expand_redout(data);
		do_expand_redin(data);
		tmp = tmp->next;
	}
}
