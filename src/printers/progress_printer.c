/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_printer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:12:26 by swillis           #+#    #+#             */
/*   Updated: 2022/10/08 15:29:45 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_progress(int i, int total)
{
	char	*str1;
	char	*str2;

	if (i == 0)
		printf("\n====== Loading =======\n");
	if (i % (total / 19) == 0)
	{
		str1 = ft_strdup("####################");
		str2 = ft_strdup("                    ");
		printf("\r[%s%s]", &str1[19 - ((i / (total / 20)))], \
							&str2[(i / (total / 20)) + 1]);
		fflush(stdout);
		free(str1);
		free(str2);
	}
	else if (i == total - 1)
		printf("\n======================\n");
}
