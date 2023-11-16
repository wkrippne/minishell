/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:57:49 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 12:55:59 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"

# define GREAT 1
# define GREATGREAT 2
# define LESS 3
# define LESSLESS 4
# define WSPACE " \t\r\n\v"
# define METACH "|<>"
# define UNSUPMETACH "&;()*{}\\"

void	init_argv(t_msh *data);
t_scom	*ft_lstlastscom(t_scom *lst);
t_scom	*ft_lstnewscom(void);
void	ft_lstadd_backscom(t_scom **lst, t_scom *new);

int		redirout(t_msh	*data, char **str);
int		redirin(t_msh	*data, char **str);
int		get_token_pipe(t_msh	*data, char **str);
void	get_token_word(t_msh	*data, char **str);
int		ft_parse(char	*input, t_msh	*data);
void	free_lst(t_scom *lst);
void	free_lstscom(t_msh *lst);
int		check_node_empty(t_scom *lst);
int		check_nbr_pipes(t_scom *lst);

#endif
