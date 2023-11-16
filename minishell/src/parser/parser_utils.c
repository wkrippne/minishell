/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:45:35 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/10 11:52:21 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

/* This func checks the presence of a pipe symbol and handles various error
** conditions associated with its usage in the minishell*/
int	get_token_pipe(t_msh *data, char **str)
{
	(*str)++;
	if (**str == '|')
		return (printf("Minishell does not support this operator \'||\'\n"), 1);
	else
	{
		while (**str && ft_strchr(WSPACE, **str))
			(*str)++;
		if (**str == '|')
		{
			printf("Parse error near unexpected token `%c\'\n",**str);
			return (1);
		}
	}
	return (ft_lstadd_backscom(&(data->lst_cmd), ft_lstnewscom()), 0);
}

/* this func extracts a word for arguement from input string, skipping the
** white spaces and metacharacters, it handles the quotes correctly and adds the
** extracted word of argument to the appropriate lnkd list*/
void	get_token_word(t_msh *data, char **str)
{
	char	*tmp;
	int		i;
	t_scom	*scom;

	scom = ft_lstlastscom(data->lst_cmd);
	tmp = ft_strdup(*str);
	i = 0;
	while (**str && !ft_strchr(WSPACE, **str) && !ft_strchr(METACH, **str))
	{
		i = jump_dq_and_sq(str, i);
		(*str)++;
		i++;
	}
	tmp[i] = '\0';
	if (i != 0)
		ft_lstadd_back(&(scom->lstarg), ft_lstnew(tmp));
}
