/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:59:28 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/06 14:03:17 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

/* this function is used to get the token of the word */
int	get_token(t_msh	*data, char **str)
{
	while (**str && ft_strchr(WSPACE, **str))
		(*str)++;
	if (**str == '|')
		return (get_token_pipe(data, str));
	else if (**str == '<')
		return (redirin(data, str));
	else if (**str == '>')
		return (redirout(data, str));
	else if (**str && ft_strchr(UNSUPMETACH, **str))
		return (printf("Msh does not sup this op. %c\n", **str), (*str)++, 1);
	else
		get_token_word(data, str);
	return (0);
}

/* This function counts the number of elemenys
** in a linked list  and returns count*/
int	size_lstarg(t_scom *data)
{
	int		i;
	t_list	*tmp;

	tmp = data->lstarg;
	if (!tmp)
		return (0);
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/* These are variables used to keep track of certain counts the the program*/
void	init_argv_norm(t_msh *data, int nscom)
{
	data->nscom = nscom;
	data->npipe = nscom - 1;
}

/* This Function iterates through nscom(nbr of structured commands) and
** assigns them to the array,it also keeps track of the number */
void	init_argv(t_msh *data)
{
	int		i;
	int		nscom;
	t_list	*tmparglst;
	t_scom	*tmpscom;

	tmpscom = data->lst_cmd;
	nscom = 0;
	while (tmpscom != NULL)
	{
		i = size_lstarg(tmpscom);
		tmparglst = tmpscom->lstarg;
		tmpscom->i = nscom;
		tmpscom->argv = (char **)malloc(sizeof(char *) * (i + 1));
		i = 0;
		while (tmparglst != NULL)
		{
			if (tmparglst->content)
				tmpscom->argv[i++] = ft_strdup((char *)tmparglst->content);
			tmparglst = tmparglst->next;
		}
		tmpscom->argv[i] = NULL;
		nscom++;
		tmpscom = tmpscom->next;
	}
	init_argv_norm(data, nscom);
}

/* this func takes an iput string processes it by extracting tokens
** necessary checks and expansions and prepares the data structure to
** represent the parsed command*/
int	ft_parse(char *input, t_msh *data)
{
	char	*str;
	t_scom	*tmp;

	str = input;
	tmp = ft_lstnewscom();
	ft_lstadd_backscom(&(data->lst_cmd), tmp);
	if (!check_unclosed_quotes(input))
	{
		ft_putstr_fd("Error: Unclosed quotes found\n", 2);
		return (1);
	}
	while (*str)
	{
		if (get_token(data, &str))
			return (1);
	}
	if (check_nbr_pipes(data->lst_cmd))
		return (1);
	expander(data);
	init_argv(data);
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->nscom);
	return (0);
}
