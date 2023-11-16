/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:29:20 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 10:38:13 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* This function is used to export the environment variable. when we export
 * the variable, it will be added to the export list. If the variable is
 * already present in the export list, then it will be modified.
*/
static void	export_export_up(t_msh *data, char *str)
{
	t_env	*node;
	char	*key;

	key = ft_strdup(str);
	node = init_env_node(key, NULL);
	data->export->exp = stack_env_list(data->export->exp, node);
}

/* This function is used to check the syntax of the export command. If the
 * syntax is correct, then it will call the export_export_up function to
 * export the variable.
*/
static bool	check_syntax_up(t_msh *data, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '=' && i != 0)
			break ;
		if (!is_alnumunder(str[i]))
			return (false);
	}
	if (str[i] == '\0')
	{
		export_export_up(data, str);
		return (false);
	}
	return (true);
}

/* This function is used to modify the value of the variable. If the variable
 * is already present in the export list, then it will be modified.
*/
static void	do_export_up(t_msh *data, char *arg)
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

/* This function updates or adds envirroment variables to the export list. it
** checks if the syntax is correct and if the variable is already present in
** the updates the variables accordingls the exit status is set to 0.
*/
void	builtin_export_update(t_msh *data)
{
	int		i;
	char	*str;

	str = data->lst_cmd->argv[1];
	if (str == NULL)
		return ;
	if (abs_string_cmp(str, "#"))
		return ;
	i = 0;
	while (data->lst_cmd->argv[++i])
	{
		str = data->lst_cmd->argv[i];
		if (!check_ue_syntax_up(str))
			continue ;
		if (!check_syntax_up(data, str))
			continue ;
		do_export_up(data, str);
	}
	g_exit_status = 0;
}
