/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:54:13 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/05 11:52:56 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * The ft_bzero() function writes n null bytes to the buffer.
 * If n is zero, bzero() does nothing . fuck the what?!
*/

void	ft_bzero(void *buffer, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)buffer + i) = '\0';
		i++;
	}
}
