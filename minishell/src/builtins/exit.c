/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:03:40 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/07 11:15:00 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* The free_print_exit sets the exit status pf the program, and prints a
** message, if the program is not running in a piped command it displays
** an exit message. and freed after including any child process as well
*/
static void	free_print_exit(t_msh *data, char *msg, int fd, char *value_txt)
{
	g_exit_status = ft_atoi(value_txt);
	if (data->npipe == 0)
		ft_putstr_fd("exit\n", fd);
	ft_putstr_fd(msg, fd);
	free_fork(data);
	exit ((unsigned char)g_exit_status);
}

/* this func handles the exit command, it checks the arguments provided
** and performs different actions based on that, if there is no arguments
** provided, it shows an error message, if a numeric arguement is provided
** it exits the shell with a status code*/
void	builtin_exit(t_msh *data)
{
	char	**arg;

	arg = data->lst_cmd->argv;
	if (arg[1] == NULL)
		free_print_exit(data, NULL, 1, "0");
	if (!ptr_is_digit(arg[1]))
		free_print_exit(data, "msh: exit: numeric argument required\n", 2, "2");
	if (ptr_is_digit(arg[1]) && arg[2] == NULL)
		free_print_exit(data, NULL, 1, arg[1]);
	if (ptr_is_digit(arg[1]) && arg[2] != NULL)
	{
		g_exit_status = 1;
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("msh: exit: too many argument\n", 2);
		return ;
	}
}

/* Free allocated memory and terminates shell*/
static void	free_exit(t_msh *data, char *value_txt)
{
	g_exit_status = ft_atoi(value_txt);
	free_all(data);
	exit ((unsigned char)g_exit_status);
}

/* This checks the command arguments and updates the exit status
** accordingly, it ensures that the shell behaves appropriately
** based on the provided arguments*/
void	builtin_exit_update(t_msh *data)
{
	char	**arg;

	arg = data->lst_cmd->argv;
	if (arg[0] && arg[1] == NULL)
		free_exit(data, "0");
	if (!ptr_is_digit(arg[1]))
		free_exit(data, "2");
	if (ptr_is_digit(arg[1]) && arg[2] == NULL)
		free_exit(data, arg[1]);
	if (ptr_is_digit(arg[1]) && arg[2] != NULL)
	{
		g_exit_status = 1;
		return ;
	}
}
