/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:33:01 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 12:42:15 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* This is to print an error message but also indicating
** what caused the error with a space and separator, and
** adds a quote to close the invalid identifier */
void	print_unset_error(char *str, char *mode)
{
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd(mode, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

/* this take the string and the mode, enter the loop to continue
** as long as there are no characters in the string and the current
** character is != which is a separator of the variable name from
** it's value, in general we are checking if unset has valid syntax */
bool	check_ue_syntax(char *str, char *mode)
{
	int		i;
	bool	begin_alfa;

	i = 0;
	begin_alfa = false;
	while (str[i] && str[i] != '=')
	{
		if (!is_alnumunder(str[i]))
		{
			print_unset_error(str, mode);
			return (false);
		}
		if (ft_isdigit(str[i]) && !begin_alfa)
		{
			print_unset_error(str, mode);
			return (false);
		}
		if (ft_isalpha(str[i]) && !begin_alfa)
			begin_alfa = true;
		i++;
	}
	return (true);
}

/* This func looks at a string and makes sure it follows some rules like
** contains letters numbers or undescores, and check that the 1st is a
** letter and if there is a digit it should come after a letter*/
bool	check_ue_syntax_up(char *str)
{
	int		i;
	bool	begin_alfa;

	i = 0;
	begin_alfa = false;
	while (str[i] && str[i] != '=')
	{
		if (!is_alnumunder(str[i]))
			return (false);
		if (ft_isdigit(str[i]) && !begin_alfa)
			return (false);
		if (ft_isalpha(str[i]) && !begin_alfa)
			begin_alfa = true;
		i++;
	}
	return (true);
}

/* this func is to allow the user to unset or remove the specific
** environment variables from the system*/
void	builtin_unset_update(t_msh *data)
{
	char	*str;
	int		i;

	if (data->lst_cmd->argv[1] == NULL)
		return ;
	i = 0;
	while (data->lst_cmd->argv[++i])
	{
		str = data->lst_cmd->argv[i];
		if (check_env_first_node(data, str))
			continue ;
		if (check_env_till_end(data, str))
			continue ;
		if (check_exp_first_node(data, str))
			continue ;
		if (check_exp_till_end(data, str))
			continue ;
	}
}
