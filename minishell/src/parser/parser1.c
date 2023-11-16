/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:44:18 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 13:47:05 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

/* This function is basically checking the quotes in the sentence if
** They're properly opened and closed */
bool	check_unclosed_quotes(char *input)
{
	char	inside_q;

	inside_q = '\0';
	while (*input)
	{
		while (*input && !inside_q)
		{
			if (*input == '\'' || *input == '\"')
				inside_q = *input;
			input++;
		}
		while (*input && inside_q)
		{
			if (*input == inside_q)
				inside_q = '\0';
			input++;
		}
	}
	if (!inside_q)
		return (true);
	return (false);
}

/*This function finds the last element in the lnkd lst of type t_scom which
** helpsus easily access the last elements of the t_scom
** lnd list (Easy access)*/
t_scom	*ft_lstlastscom(t_scom *lst)
{
	t_scom	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

/* This is used to create new nodes that can store info about a command
** or a line of input in a linked list*/
t_scom	*ft_lstnewscom(void)
{
	t_scom	*new_node;

	new_node = (t_scom *)malloc(sizeof(t_scom));
	if (!new_node)
		return (NULL);
	new_node->i = 0;
	new_node->next = NULL;
	new_node->lstarg = NULL;
	new_node->argv = NULL;
	new_node->lstofredirin = NULL;
	new_node->lstofredirout = NULL;
	new_node->ft_stdin = STDIN_FILENO;
	new_node->ft_stdout = STDOUT_FILENO;
	return (new_node);
}

/* This adds a new node at the end of a linked lst, and ensures it is
** correctly connected to the existing nodes*/
void	ft_lstadd_backscom(t_scom **lst, t_scom *new)
{
	t_scom	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlastscom(*lst);
		temp->next = new;
	}
}

/* This function frees the linked list of type t_scom*/
void	free_lst(t_scom *lst)
{
	t_list	*next;

	if (lst->lstarg == NULL)
		return ;
	while (lst->lstarg)
	{
		next = lst->lstarg->next;
		if (lst->lstarg->content)
			free(lst->lstarg->content);
		free(lst->lstarg);
		lst->lstarg = next;
	}
}
