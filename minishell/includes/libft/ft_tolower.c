/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:33:51 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/05 12:06:05 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * The tolower() function converts an upper-case letter to the corresponding
 * lower-case letter.
 *
 * If the argument is an upper-case letter, the tolower() function returns
 * the corresponding lower-case letter if there is one;
 * Otherwise, the argument is returned unchanged. 
**/

int	ft_tolower(int c)
{
	if ((c >= 'A') && (c <= 'Z'))
		c += 32;
	return (c);
}
