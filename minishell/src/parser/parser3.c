/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:40:04 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 13:48:08 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

/*This function helps us skip 	 double and single quotes*/
int	jump_dq_and_sq(char **str, int i)
{
	if (**str == '\"')
	{
		while (**str)
		{
			(*str)++;
			i++;
			if (**str == '\"')
				return (i);
		}
	}
	else if (**str == '\'')
	{
		while (**str)
		{
			(*str)++;
			i++;
			if (**str == '\'')
				return (i);
		}
	}
	return (i);
}

/* This function looks for characters in a string until it reaches a whitespace
** a metacharacter or unsportedmetach, skpis over quoted sections and extracts
** the file name from the string and store it appropriately*/
int	get_token_aux(t_redir *red, t_scom *scom, char **str, int type)
{
	int	i;

	i = 0;
	while (**str && !ft_strchr(WSPACE, **str)
		&& !ft_strchr(METACH, **str) && !ft_strchr(UNSUPMETACH, **str))
	{
		i = jump_dq_and_sq(str, i);
		(*str)++;
		i++;
	}
	red->filename[i] = '\0';
	if (type == GREATGREAT || type == GREAT)
		return (ft_lstadd_back(&(scom->lstofredirout), ft_lstnew(red)), 0);
	else
		return (ft_lstadd_back(&(scom->lstofredirin), ft_lstnew(red)), 0);
}

/* This function checks  if the current word in the cli represents a valid redir
** if it does it creates a red to store redir details, and then checks for errors
** and calls the func to handle the addition of the redir to appropriate list*/
int	get_token_word_redir(t_msh	*data, char **str, int type)
{
	t_scom	*scom;
	t_redir	*red;

	red = (t_redir *)malloc(sizeof(t_redir));
	red->type = type;
	scom = ft_lstlastscom(data->lst_cmd);
	while (**str && ft_strchr(WSPACE, **str))
		(*str)++;
	if (**str && (ft_strchr(METACH, **str) || ft_strchr(UNSUPMETACH, **str)))
	{
		ft_putstr_fd("\"syntax error near unxp token `", 2);
		ft_putchar_fd(**str, 2);
		ft_putstr_fd("\'\n", 2);
		return (free(red), 1);
	}
	if (**str == '\0')
	{
		ft_putstr_fd("syntax error near unxp token `newline\'\n", 2);
		return (free(red), 1);
	}
	red->filename = ft_strdup(*str);
	return (get_token_aux(red, scom, str, type));
}

/* This func looks at the next char after the output redir symbol
** > if it's also > it means we have a double output redir >> and
** it calls a function to handle it*/
int	redirout(t_msh	*data, char **str)
{
	(*str)++;
	if (**str == '>')
		return ((*str)++, get_token_word_redir(data, str, GREATGREAT));
	else
		return (get_token_word_redir(data, str, GREAT));
}

int	redirin(t_msh	*data, char **str)
{
	(*str)++;
	if (**str == '<')
	{
		data->heredoc = 1;
		return ((*str)++, get_token_word_redir(data, str, LESSLESS));
	}
	else
		return (get_token_word_redir(data, str, LESS));
}
