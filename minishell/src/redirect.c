/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:32:01 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 16:07:24 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

/* this handles the situation when file is not found*/
void	error_file(t_msh *data, int fd, char *filename)
{
	if (fd < 0)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		free_fork(data);
		exit(1);
	}
}

/* This func allows the user to enter multi lines of text until a specific
** condition is met*/
void	loop_heredoc(t_msh *data, char *filename, int fd)
{
	char	*buff;

	while (1)
	{
		buff = readline(">");
		if (!buff)
		{
			ft_putstr_fd("msh: warning: here-doc at line 1 deli. by eof\n", 2);
			break ;
		}
		buff[ft_strlen(buff)] = '\0';
		if (abs_string_cmp(filename, buff))
			break ;
		if (ft_strrchr(buff, '$'))
			check_expander(data, (void **)(&buff));
		ft_putendl_fd(buff, fd);
		free(buff);
	}
	free(buff);
}

/* do_heredoc handles the process of readinf input from the user and storing it
** in a temporary file namede heredoc, it also sets up the fd for the commands
** input to read from this temporary file*/
void	do_heredoc(t_msh *data)
{
	int		tmp_fd;
	t_list	*tmp;
	t_redir	*tmp_red;

	tmp = data->lst_cmd->lstofredirin;
	tmp_red = tmp->content;
	tmp_fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	signal(SIGINT, SIG_DFL);
	error_file(data, tmp_fd, ".heredoc");
	loop_heredoc(data, tmp_red->filename, tmp_fd);
	close(tmp_fd);
	data->lst_cmd->ft_stdin = open(".heredoc", O_RDWR);
}

/* This func looks at each input redir and either opens a file for reading
** << type or performs a heredoc redir by collecting input drom user
** and storing it in a temporary file*/
void	open_redir_in(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmp_red;

	tmp = data->lst_cmd->lstofredirin;
	while (data->lst_cmd->lstofredirin)
	{
		tmp_red = data->lst_cmd->lstofredirin->content;
		if (tmp_red->type == LESS)
		{
			data->lst_cmd->ft_stdin = open(tmp_red->filename, O_RDONLY);
			error_file(data, data->lst_cmd->ft_stdin, tmp_red->filename);
		}
		else if (tmp_red->type == LESSLESS)
		{
			do_heredoc(data);
		}
		data->lst_cmd->lstofredirin = data->lst_cmd->lstofredirin->next;
	}
	data->lst_cmd->lstofredirin = tmp;
}

/* This looks at each output redir and either opens a file for writing,
** truncating it if it already exists*/
void	open_redir_out(t_msh *data)
{
	t_list	*tmp;
	t_redir	*tmp_red;

	tmp = data->lst_cmd->lstofredirout;
	while (tmp)
	{
		tmp_red = tmp->content;
		if (tmp_red->type == GREAT)
		{
			data->lst_cmd->ft_stdout = open(tmp_red->filename,
					O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			error_file(data, data->lst_cmd->ft_stdout, tmp_red->filename);
		}
		else if (tmp_red->type == GREATGREAT)
		{
			data->lst_cmd->ft_stdout = open(tmp_red->filename,
					O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
			error_file(data, data->lst_cmd->ft_stdout, tmp_red->filename);
		}
		tmp = tmp->next;
	}
}
