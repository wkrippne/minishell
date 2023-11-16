/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:42:06 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 12:58:51 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* This func checks if the given variable name matches the key of the 1st node
** in the exported variable list, if there is a match it removes the 1st node
** from the list and returns true, if empty the false */
bool	check_exp_first_node(t_msh *data, char *str)
{
	t_env	*tmp;
	t_env	*exp;

	exp = data->export->exp;
	if (exp == NULL)
		return (false);
	if (abs_string_cmp(str, exp->key))
	{
		free (exp->key);
		tmp = exp->next;
		free (exp);
		data->export->exp = tmp;
		return (true);
	}
	return (false);
}

/* This func checks if the given variable name matches the key of any node
** in the exported variable list, starting from the second node and going till
** the end, if there is a match it removes the corresponding node from
** the list and returns true, if no match then false*/
bool	check_exp_till_end(t_msh *data, char *str)
{
	t_env	*tmp;
	t_env	*exp;

	exp = data->export->exp;
	while (exp)
	{
		if (abs_string_cmp(str, exp->key))
		{
			free (exp->key);
			tmp->next = exp->next;
			free (exp);
			return (true);
		}
		tmp = exp;
		exp = exp->next;
	}
	return (false);
}

/* This func checks if the given variable name matches the key of
** the first node in the environment variable list, if there is a match
** it removes the correspnding node from the lst and returns true else false*/
bool	check_env_first_node(t_msh *data, char *str)
{
	t_env	*tmp;
	t_env	*env;

	env = data->export->env;
	if (env == NULL)
		return (false);
	if (abs_string_cmp(str, env->key))
	{
		free (env->key);
		free (env->value);
		tmp = env->next;
		free (env);
		data->export->env = tmp;
		return (true);
	}
	return (false);
}

/* This func checks if a variable name matches the key of any node in the
** environment variable list, starting from the second node and continuing
** until the end, if there is a macth, it removes the corresponding
** node from the list and returns true else false*/
bool	check_env_till_end(t_msh *data, char *str)
{
	t_env	*tmp;
	t_env	*env;

	env = data->export->env;
	while (env)
	{
		if (abs_string_cmp(str, env->key))
		{
			free (env->key);
			free (env->value);
			tmp->next = env->next;
			free (env);
			return (true);
		}
		tmp = env;
		env = env->next;
	}
	return (false);
}

/* This func removes specified env variables from the programs env
** it checks the arguements one by one, verifies their syntax and
** searches for matching variables in both the environment variable
** list and the exported variables list, if a match is found
** the variable is removed */
void	builtin_unset(t_msh *data)
{
	char	*str;
	int		i;

	if (data->lst_cmd->argv[1] == NULL)
		return ;
	i = 0;
	while (data->lst_cmd->argv[++i])
	{
		str = data->lst_cmd->argv[i];
		if (!check_ue_syntax(str, "unset"))
			continue ;
		if (check_env_first_node(data, str))
			continue ;
		if (check_env_till_end(data, str))
			continue ;
		if (check_exp_first_node(data, str))
			continue ;
		if (check_exp_till_end(data, str))
			continue ;
	}
	free_table(data->env);
	init_env_table(data);
}
