/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:25:50 by swillis           #+#    #+#             */
/*   Updated: 2022/09/20 14:55:43 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

int	nbr_len(int nbr)
{
	int	len;

	len = 1;
	while (nbr / 10)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}

double	ft_atod(char *str)
{
	int		i;
	int		integral;
	int		fractional;
	double	sign;

	integral = ft_atoi(str);
	i = 0;
	sign = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (integral == 0 && str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && ft_isnum(str[i]))
		i++;
	fractional = 0;
	if (++i < (int)ft_strlen(str))
		fractional = ft_atoi(&str[i]);
	if (fractional == 0)
		return ((double)integral);
	return (((double)integral + \
		((double)fractional / pow(10, nbr_len(fractional)))) * sign);
}
