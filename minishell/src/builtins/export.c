/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:41:31 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 12:35:28 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* This func displays the exported environment variables by printing them in
** a specific format, it ensures that all the necessary info about variables
** is displayed including the key-value pairs for the environment
** variables and only the keys for exported variables*/
static void	export_only(t_msh *data)
{
	t_env	*env;
	t_env	*exp;

	env = data->export->env;
	exp = data->export->exp;
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\"\n", 1);
		env = env->next;
	}
	while (exp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(exp->key, 1);
		ft_putstr_fd("\n", 1);
		exp = exp->next;
	}
}

/* This func is responsible for adding a new variable represnted by str
** parameter, to the list of exported variables in the shell data struct
** creates a new env node with the provided key and NULL value, and
** adds to the list using stack_env_list*/
static void	export_export(t_msh *data, char *str)
{
	t_env	*node;
	char	*key;

	key = ft_strdup(str);
	node = init_env_node(key, NULL);
	data->export->exp = stack_env_list(data->export->exp, node);
}

/* this func checks the syntax variable to be exported, it ensures that the
** variable contains only valid characters and has the correct syntax for
** variable assignement*/
static bool	check_syntax_var_equal(t_msh *data, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '=' && i != 0)
			break ;
		if (!is_alnumunder(str[i]))
		{
			ft_putstr_fd("msh: Export: not a valid identifier\n", 2);
			return (false);
		}
	}
	if (str[i] == '\0')
	{
		export_export(data, str);
		return (false);
	}
	return (true);
}

/* This func takes a variable and its value, splits them and adds
** or modifies the variable in the shells list of environment variables*/
static void	do_export(t_msh *data, char *arg)
{
	char	**table;
	char	*value;
	char	*key;
	t_env	*node;

	table = ft_split(arg, '=');
	key = ft_strdup(table[0]);
	if (table[1] == NULL)
		value = ft_strdup("\0");
	else
		value = ft_strdup(table[1]);
	free_table(table);
	if (is_key_in_env(data->ppt->list, key))
		return (modify_value(data, key, &value), free(key));
	if (is_key_in_env(data->export->exp, key))
		ft_unset(data, key);
	node = init_env_node(key, value);
	data->ppt->list = stack_env_list(data->ppt->list, node);
}

/* this func is used to export variables in the shell, it takes one or more
** arguments, checks their syntax and adds or modifies the variables
** in the list of environment variables*/
void	builtin_export(t_msh *data)
{
	int		i;
	char	*str;

	str = data->lst_cmd->argv[1];
	if (str == NULL)
		return (export_only(data));
	if (abs_string_cmp(str, "#"))
		return (export_only(data));
	i = 0;
	while (data->lst_cmd->argv[++i])
	{
		str = data->lst_cmd->argv[i];
		if (!check_ue_syntax(str, "export"))
			continue ;
		if (!check_syntax_var_equal(data, str))
			continue ;
		do_export(data, str);
	}
	free_table(data->env);
	init_env_table(data);
	g_exit_status = 0;
}
