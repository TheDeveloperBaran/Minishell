/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsahin <ilsahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:10:14 by ilsahin           #+#    #+#             */
/*   Updated: 2023/10/28 14:10:15 by ilsahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_flag(void)
{
	if (g_ms.check_flag == 1)
		errno = 4;
	if (g_ms.check_flag == 1)
	{
		errno = 1;
		g_ms.check_flag = 0;
	}
}
