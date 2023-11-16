/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:06:32 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 10:59:52 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* this functions is called when the user presses Ctrl+C, we make sure that
** it behaves correctly when this happens*/
static void	handler_false(int sig_type)
{
	(void)sig_type;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

/* this function is called when the user presses Ctrl+\, we make sure that
** it clears the current input line, so the user can start a new command
** or continue typing without any interference*/
static void	handler_true(int sig_type)
{
	(void)sig_type;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
}

/*this sets up how the program should respond when the user presses
** Ctrl+C if the flaf is 0 it will handle it by calling handler_false
** which displays a new_line and clears input line if the flag is
** not 0 we only clear the input line, we also make sure that when
** the signal handler is running pressing Ctrl+c again wont interrupt
** the program*/
void	init_signal(int flag)
{
	struct sigaction	action;

	if (!flag)
		action.sa_handler = handler_false;
	else
		action.sa_handler = handler_true;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
}
