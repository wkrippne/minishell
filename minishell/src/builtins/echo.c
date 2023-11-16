/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:43 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 11:08:49 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Here I am checking the echo with the -n flag
* If it does not detect the - or n then it's false */
static bool	check_flag(char *arg)
{
	int	i;

	if (!arg)
		return (false);
	i = 0;
	if (arg[i] == '-' && arg[i + 1] != 'n')
		return (false);
	while (arg[i])
	{
		if (arg[i] == '-' && i == 0)
		{
			i++;
			while (arg[i] == 'n')
				i++;
			if (arg[i] == '\0')
				return (true);
			break ;
		}
		i++;
	}
	return (false);
}

/* Check delimeter if it is 1 quote or 2 but it is not close it opens dquote
* or if it is a Back slash */
static bool	check_delimiter(char *str, char xar, char *del, int pos)
{
	if (xar == *del && pos != 0 && str[pos - 1] != '\\')
	{
		*del = '\0';
		return (true);
	}
	if (xar == '\\')
		return (true);
	if ((xar == '\'' || xar == '\"') && *del == '\0')
	{
		if (pos == 0)
		{
			*del = xar;
			return (true);
		}
		if (str[pos - 1] == '\\')
		{
			ft_putchar_fd(xar, 1);
			return (true);
		}
		*del = xar;
		return (true);
	}
	return (false);
}

/* in here is just the echo function but also with another feature
** called continueit can slo; a statement to proceed
** to the next iteration */
static void	do_echo(char **arg, int pos)
{
	int		i;
	char	*str;
	char	delimiter;

	while (arg[pos])
	{
		i = -1;
		str = arg[pos];
		delimiter = '\0';
		while (str[++i])
		{
			if (check_delimiter(str, str[i], &delimiter, i))
				continue ;
			ft_putchar_fd(str[i], 1);
		}
		if (arg[++pos] != NULL)
			ft_putchar_fd(' ', 1);
	}
}

/* This takes the words or texts given to echo and shows them
** on the screen, if there are special instructions (Flags)
** it follows them, then adds a new line at the end to mark
** that the program was succesfull executed */
void	builtins_echo(t_msh *data)
{
	char	**arg;
	int		i;

	arg = data->lst_cmd->argv;
	i = 1;
	while (check_flag(arg[i]))
		i++;
	if (arg[i] == NULL)
		return ;
	do_echo(arg, i);
	if (i == 1)
		ft_putchar_fd('\n', 1);
	g_exit_status = 0;
}
