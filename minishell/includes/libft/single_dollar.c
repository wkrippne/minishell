/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkrippne <wkrippne@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:12:46 by wkrippne          #+#    #+#             */
/*   Updated: 2023/06/13 22:19:33 by wkrippne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* returns true if the second character from the string coming from the input
* is either '\0', a space or a double quotation mark. 
* Returns false if none of these three options is met.
*/

bool	single_dollar(char *input_at_i)
{
	return ((!input_at_i[1]
			|| input_at_i[1] == ' '
			|| input_at_i[1] == '\"'));
}
