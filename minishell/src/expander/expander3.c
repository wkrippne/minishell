/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:53:14 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 10:44:57 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

/* here we calculate the size of the expansion segment, we ensure that we
** allocate the appropriate amount of memory for the expanded string
** and perform actual expansion later by replacing variables with
** their values*/
void	size_expand_2(t_msh *data, char *arg, int *i, int *len)
{
	int		j;
	char	*key;
	char	*value;

	j = 0;
	if (arg[*i + 1] != '?')
	{
		while (is_alnumunder(arg[*i + 1 + j]))
			j++;
		key = ft_substr(arg, *i + 1, j);
		value = get_value_from_key(data->ppt->list, key);
		if (j == 0)
			value = ft_strdup("$");
		if (value)
			*len += (int)ft_strlen(value);
		free(key);
		free (value);
		*i += j;
	}
	else
		size_expand_2_aux(len, i);
}

/*by calculating the size of the expanded string beforehand, we ensure that we
** allocate enought memory to store expanded version of the string without
** any overflow or memory errors*/
int	size_expand(t_msh *data, char *arg)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	len = 0;
	quote = '\0';
	while (arg && arg[++i])
	{
		quote = quote_value(arg[i], quote);
		if (arg[i] == '$' && quote != '\'')
			size_expand_2(data, arg, &i, &len);
		else
			len++;
	}
	return (len);
}

/* By expanding the exit_status we make sure thet our exit status is useful for
** displaying or processing the info related to the execution of commands*/
void	expand_exit_status(t_msh *data, char **ppt, int *i)
{
	int		k;
	char	*value;

	value = ft_itoa(g_exit_status);
	k = -1;
	while (value[++k])
		(*ppt)[data->num++] = value[k];
	free(value);
	*i += 1;
}

/* this func is to handle the expansion of variables in a string by replacing
** variable references with their corresponding value*/
void	do_expander_if(t_msh *data, char *value, char **ptr)
{
	int	k;

	if (value)
	{
		k = -1;
		while (value[++k])
			(*ptr)[data->num++] = value[k];
		free (value);
	}
}

/* This func handles the expansion of the variables in a string by retrieving
** their values from the list of the env  variables and appending them to
** the output string, this makes our sting more meaningful and dynamic*/
void	do_expander(t_msh *data, char *arg, char **ptr, int *i)
{
	char	*key;
	char	*value;
	int		len;

	if (arg[*i + 1] != '?')
	{
		len = 0;
		while (is_alnumunder(arg[*i + 1 + len]))
			len++;
		key = ft_substr(arg, *i + 1, len);
		value = get_value_from_key(data->ppt->list, key);
		if (len == 0)
			value = ft_strdup("$");
		free(key);
		*i += len;
		do_expander_if(data, value, ptr);
	}
	else
		expand_exit_status(data, ptr, i);
}
