/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:53:11 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 10:43:48 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

bool	full_dolar(const char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] != '$')
			return (false);
		i++;
	}
	return (true);
}

/* this checks if the quote character starts or ends a quote, if it starts
** it returns the character itselt if it ends it returns 0*/
char	quote_value(char c, char quote)
{
	if (ft_strrchr("\"\'", c) && !quote)
		return (c);
	else if (ft_strrchr("\"\'", c) && quote == c)
		return (0);
	return (quote);
}

/* this checks of the char is a letter, number, underscore ot if it is not*/
int	is_alnumunder(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '_')
		return (1);
	else
		return (0);
}

/* This func adds the length of the g_exit_status converted to a string to
** overall the length expansion, we do this to avoid memory problems
** bcz we give appropriate memory for the string to accommodate the
** replaced variables or sequences*/
void	size_expand_2_aux(int *len, int *i)
{
	char	*key;

	key = ft_itoa(g_exit_status);
	*len += (int)ft_strlen(key);
	*i += 1;
	free(key);
}
