/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:51:05 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 13:44:40 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* This function takes a linked list of key-value pairs and a key as input
** it searches through each node to find a node with a matching key if
it is found it returns a duplicate of the corresponding value. if not "NULL"*/
char	*get_value_from_key(t_env *env, char *key)
{
	t_env	*node;
	char	*str;

	node = env;
	while (node)
	{
		if (abs_string_cmp(key, node->key))
		{
			str = ft_strdup(node->value);
			return (str);
		}
		node = node->next;
	}
	return (NULL);
}

/* This function takes a linked list of key-value pairs (exp in the data struct)
** and a key as input it searches through each node to find a node with a
** matching key is found it replaces the value in that node with the value
** specified in the new_valueparameter. the function frees to avoid leaks
** if no match nothing happens */
void	modify_value_exp(t_msh *data, char *key, char **new_value)
{
	t_env	*node;

	node = data->export->exp;
	while (node)
	{
		if (abs_string_cmp(key, node->key))
		{
			free (node->value);
			node->value = *new_value;
			return ;
		}
		node = node->next;
	}
}

/* This func takes a linked list of key-value pairs (list in the data struct)
** and a key as input it searches through each node to find a node with a
** matching key if match is found it replaces the value in that node with the
** value specified in the new_value parameter. the function frees to avoid
**leaks if no match nothing happens */
void	modify_value(t_msh *data, char *key, char **new_value)
{
	t_env	*node;

	node = data->ppt->list;
	while (node)
	{
		if (abs_string_cmp(key, node->key))
		{
			free (node->value);
			node->value = *new_value;
			return ;
		}
		node = node->next;
	}
}

/* This funct takes a linked list of key-value pairs (env) and a key as input
** checks each node in the linkd lst to see if any node has a matching key.
** if found returns true else false */
bool	is_key_in_env(t_env *env, char *key)
{
	while (env)
	{
		if (abs_string_cmp(key, env->key))
			return (true);
		env = env->next;
	}
	return (false);
}
