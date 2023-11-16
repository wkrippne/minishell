/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:51:02 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 11:01:07 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* This takes a str that has a key-value format like key=value and
 * splits it into two strings, one for key and one for value.
*/
static void	init_key_value(char **key, char **value, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	*key = ft_substr(str, 0, i);
	*value = ft_substr(str, (i + 1), ft_strlen(str) - i);
}

/* This takes a key and a value and creates a new node for the linked list
 * with those values. */
t_env	*init_env_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		put_str_exit("Error: Malloc of *node fails\n", 1);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

/* This function adds a new node to the end of the linked list. if it is
** empty the node becomes the head of the list. otherwise it iterates through
** the list until it reaches the end and adds the node there.
*/
t_env	*stack_env_list(t_env *var, t_env *node)
{
	t_env	*header;

	header = var;
	if (var == NULL)
		return (node);
	while (var->next != NULL)
		var = var->next;
	var->next = node;
	return (header);
}

/* This functions takes an array of env variables and converts them into a
** linked list. It does this by iterating through each env variable, extracts
** its key-value pair, creates a new node with those values and adds it to the
** linked list, and store the linked list in the data structer. */
t_msh	*env_to_list(t_msh *data, char **env)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*node;

	if (!env)
		put_str_exit("Error: env is NULL\n", 1);
	i = -1;
	data->ppt->list = NULL;
	while (env[++i])
	{
		init_key_value(&key, &value, env[i]);
		node = init_env_node(key, value);
		data->ppt->list = stack_env_list(data->ppt->list, node);
	}
	return (data);
}
