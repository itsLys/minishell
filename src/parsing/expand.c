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

#include "libft.h"
#include <parsing.h>
#include <stddef.h>
#include <stdio.h>

// NOTE: 	"adsfasdf"afadf'adsfadsf'adsf
// 			 DDDDDDDDNNNNNSSSSSSSSNNNN
// 			 adsfasdfafadfadsfadsfadsf
//
//
size_t	mask_seter(char *word, char *flager, char *c, size_t *j)
{
	size_t	i;

	i = 1;
	while (word[i] && word[i] != c[0])
	{
		flager[*j] = c[1];
		i++;
		(*j)++;
	}
	if (i == 2)
		flager[*j] = 'N';
	i++;
	return (i);
}

char	*mask_creator(char *word)
{
	size_t	i;
	size_t	j;
	char	*mask;

	i = 0;
	j = 0;
	mask = ft_calloc(sizeof(char), ft_strlen(word) + 1);
	while (word[i])
	{
		if (word[i] == '"')
			i += mask_seter(&word[i], mask, "\"D", &j);
		else if (word[i] == '\'')
			i += mask_seter(&word[i], mask, "\'S", &j);
		else
		{
			while (word[i] && word[i] != '"' && word[i] != '\'')
			{
				mask[j] = 'N';
				i++;
				j++;
			}
		}
	}
	printf("ma	;%s\n", mask);
	return mask;
}

size_t	word_seter(char *word, char *flager, char c, size_t *j)
{
	size_t	i;

	i = 1;
	while (word[i] && word[i] != c)
	{
		flager[*j] = word[i];
		i++;
		(*j)++;
	}
	i++;
	return (i);
}

char	*remove_quotes(char *word, size_t size_new_word)
{
	size_t	i;
	size_t	j;
	char	*new_word;

	i = 0;
	j = 0;
	new_word = ft_calloc(sizeof(char), size_new_word + 1);
	while (word[i])
	{
		if (word[i] == '"')
			i += word_seter(&word[i], new_word, '\"', &j);
		else if (word[i] == '\'')
			i += word_seter(&word[i], new_word, '\'', &j);
		else
		{
			while (word[i] && word[i] != '\"' && word[i] != '\'')
			{
				new_word[j] = word[i];
				i++;
				j++;
			}
		}
	}
	printf("or	;%s\naf	;%s\n", word, new_word);
	return (new_word);
}

// NOTE : je peux passer une node pipe line et je peux donc acceder a son arg list et redir list 

// char	*expand(char **env, t_ast_node *pipeline)
// {
// 	
// }


int main (int ac, char **av)
{
	printf("av = %s\n", av[1]);
	remove_quotes(av[1], ft_strlen(mask_creator(av[1])));

}

