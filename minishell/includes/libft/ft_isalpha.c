/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:21:33 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/05 11:53:41 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 *	- The ft_isalpha() function tests for any character for which
 *	isupper(3) or islower(3) is true.  The value of the argument must be
 *
 *	- The isalpha() function returns zero if the character tests false and
 *	returns non-zero if the character tests true .
*/

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
