/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:25:50 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 22:52:44 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r')
		return (1);
	if (c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

static int	ft_isnum(char c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

static int	ft_atoi(char *str)
{
	int				i;
	int				sign;
	unsigned int	n;
	int				nbr;

	sign = 1;
	i = 0;
	n = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && ft_isnum(str[i]))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	nbr = n * sign;
	return (nbr);
}

double	ft_atod(char *str)
{
	int		i;
	int		integral;
	int		fractional;
	double	nbr;

	integral = ft_atoi(str);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i] && ft_isnum(str[i]))
		i++;
	fractional = ft_atoi(&str[++i]);
	if (fractional == 0)
		return ((double)integral);
	nbr = (double)integral + ((double)fractional / 10);
	return (nbr);
}