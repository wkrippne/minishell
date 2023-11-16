/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:53:00 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/06 13:35:39 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* The function takes a string finds a specific character, extracts a portion
** of the string, and replaces the original string with the extracted portion
** which is used to rep a simple version od the prog's manager in prompt*/
static void	s_manager_prompt(t_ppt *root)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (root->s_manager[i] != '/' && root->s_manager[i] != '\0')
		i++;
	j = 0;
	while (root->s_manager[j] != '.' && root->s_manager[j] != ':'
		&& root->s_manager[j] != '\0')
		j++;
	tmp = ft_substr(root->s_manager, (i + 1), (j - (i + 1)));
	free (root->s_manager);
	root->s_manager = tmp;
}

/* this compares the current working directory with the user's home
** directory with the user's home directly and modifies the represantation
** of the current working directory in the prompt accordingly*/
static void	path_prompt(t_ppt *root)
{
	int		len_p;
	int		len_h;
	char	*tmp;

	len_p = (int)ft_strlen(root->path);
	len_h = (int)ft_strlen(root->home);
	if ((len_h == len_p) && !(ft_strncmp(root->home, root->path, len_h)))
	{
		free (root->path);
		root->path = ft_strdup("~");
		return ;
	}
	if ((len_h < len_p) && !(ft_strncmp(root->home, root->path, len_h)))
	{
		tmp = ft_substr(root->path, len_h, (len_p - len_h));
		free (root->path);
		root->path = ft_strjoin("~", tmp);
		free (tmp);
		return ;
	}
	if ((len_h > len_p) && !ft_strncmp(root->path, root->home, len_p))
		return ;
	free (root->path);
	root->path = NULL;
}

/* This func combines users name, system manager name, cwd and
** other symbols to create a string that represents the prompt
** dislplayed to the user*/
static void	prompt_prompt(t_ppt *root)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	free (root->prompt);
	tmp1 = ft_strjoin(root->user, "@");
	tmp2 = ft_strjoin(root->s_manager, ":");
	tmp3 = ft_strjoin(tmp1, tmp2);
	free (tmp1);
	free (tmp2);
	tmp1 = ft_strjoin(root->path, "$ ");
	root->prompt = ft_strjoin(tmp3, tmp1);
	free (tmp3);
	free (tmp1);
}

/* This func creates and displays the prompt in Our minishell, retrieves
** important info like the users name, session manager and home directroy
** it also gets the current working directory and uses all this info
** to construct a meaningful prompt*/
char	*display_prompt(t_ppt *root)
{
	if (root->n_exec == 0)
	{
		root->user = get_value_from_key(root->list, "USER");
		root->s_manager = get_value_from_key(root->list, "SESSION_MANAGER");
		if (root->s_manager == NULL)
			root->s_manager = strdup("");
		root->home = get_value_from_key(root->list, "HOME");
		s_manager_prompt(root);
	}
	free (root->path);
	root->path = getcwd(NULL, 0);
	path_prompt(root);
	if (!root->path)
		put_str_exit("Error: Path prompt is NULL\n", 1);
	prompt_prompt(root);
	root->n_exec++;
	return (root->prompt);
}
