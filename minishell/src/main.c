/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:39:55 by wkrippne          #+#    #+#             */
/*   Updated: 2023/07/06 16:05:21 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int		g_exit_status;

/* this takes the input, trims, whitespaces and checks if the trimmed
** input is a valid command, if yes it is added to the history and executed*/
static int	do_trim_parser(t_msh *data, char *input, char **trim)
{
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		return (free (input), 0);
	}
	*trim = ft_strtrim(input, WSPACE);
	if (*(*trim) == '\0')
		return (free(input), free(*trim), -1);
	if (!ft_strchr(WSPACE, *input))
		add_history(input);
	free(input);
	if (ft_parse(*trim, data))
	{
		free_lstscom(data);
		free (*trim);
		return (-1);
	}
	return (1);
}

/* This runs the shell program that repeatedly prompts the user for input
** reads the command processes it and executes it, we also handle special
** cases like emptu input or exit commands*/
static void	do_minishell(t_msh *data)
{
	int		flag_dtp;
	char	*input;
	char	*trim;

	while (true)
	{
		init_signal(0);
		input = readline(display_prompt(data->ppt));
		flag_dtp = do_trim_parser(data, input, &trim);
		if (flag_dtp < 0)
			continue ;
		if (flag_dtp == 0)
			break ;
		create_pipe(data);
		do_execute(data);
		free_lstscom(data);
		free(data->pid);
		data->pid = NULL;
		free_fd(data);
		free (trim);
	}
}

/* this main sets up the necessary data structures, initialise the shell env
** starts the shell program with also handling the command line arguements
** clears history and sets a signal to be ignored*/
int	main(int argc, char **argv, char **env)
{
	t_msh	*data;

	if (argc > 1)
		return (ft_putstr_fd("msh: invalid number of arguments\n", 2), 1);
	(void) argv;
	data = (t_msh *)malloc(sizeof(t_msh));
	data = (t_msh *)ft_memset(data, 0, sizeof(t_msh));
	data = init_data(data, env);
	rl_clear_history();
	signal(SIGQUIT, SIG_IGN);
	do_minishell(data);
	free_over(data);
	return (0);
}
