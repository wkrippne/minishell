/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:16:45 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/05 11:53:37 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 *	- The ft_isalnum() function tests for any character for which isalpha(3) or
 *	isdigit(3) is true.  The value of the argument must be representable as
 *	an unsigned char or the value of EOF .
 *
 *	- The isalnum() function returns zero if the character tests false
 *	and returns non-zero if the character tests true.
*/

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}
