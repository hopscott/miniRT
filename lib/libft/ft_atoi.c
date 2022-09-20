/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:25:50 by swillis           #+#    #+#             */
/*   Updated: 2022/09/20 14:56:40 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r')
		return (1);
	if (c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int	ft_isnum(char c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int				i;
	int				sign;
	unsigned int	n;
	int				nbr;

	sign = 1;
	i = 0;
	n = 0;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	if (str && str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str && str[i] && ft_isnum(str[i]))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	nbr = n * sign;
	return (nbr);
}
