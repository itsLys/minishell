/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:15:32 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/20 22:51:02 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

void	erase(char *str, size_t index)
{
	size_t	len;

	len = ft_strlen(str);
	if (!str || index >= len)
		return ;
	while (index < len)
	{
		str[index] = str[index + 1];
		index++;
	}
}

char	*quote_mask(const char *str)
{
	int		i;
	char	*mask;
	bool	in_single;
	bool	in_double;

	i = -1;
	in_double = false;
	in_single = false;
	mask = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!mask)
		return (NULL);
	while (str[++i])
	{
		if (!in_double && str[i] == '\'')
			in_single = !in_single;
		else if (!in_single && str[i] == '"')
			in_double = !in_double;
		if (in_single)
			mask[i] = SINNQ;
		else if (in_double)
			mask[i] = DOUBQ;
		else
			mask[i] = NONEQ;
	}
	return (mask);
}

void	remove_quotes(char *str, char *mask)
{
	bool	in_single;
	bool	in_double;
	int		i;

	i = 0;
	in_single = false;
	in_double = false;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			erase(str, i);
			erase(mask, i);
			continue ;
		}
		if (str[i] == '"' && !in_single)
		{
			in_double = !in_double;
			erase(str, i);
			erase(mask, i);
			continue ;
		}
		i++;
	}
}
