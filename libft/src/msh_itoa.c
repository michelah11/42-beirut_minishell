/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 00:28:25 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/01/13 03:14:11 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	msh_numlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	msh_sign(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

static int	absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*msh_itoa(int n, t_mem *mem)
{
	int		len;
	int		sign;
	char	*str;

	len = msh_numlen(n);
	sign = msh_sign(n);
	if (n == -2147483648)
		return (msh_strdup("-2147483648", mem));
	str = (char *)msh_malloc(sizeof(char) * (len + 1), mem);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		if (sign < 0 && len == 0)
			str[0] = '-';
		else
		{
			str[len] = absolute(n) % 10 + 48;
			n /= 10;
		}
		len --;
	}
	return (str);
}
