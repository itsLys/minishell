

#include "libft.h"
#include <parsing.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// NOTE: 	"$"afadf'adsfadsf'adsf
// 			"D"NNNNN'SSSSSSSS'NNNN

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
//
// size_t	incr(char *word, char c, size_t *size)
// {
// 	size_t	i;
//
// 	i = 1;
// 	while (word[i] && word[i] != c)
// 	{
// 		i++;
// 		(*size)++;
// 	}
// 	i++;
// 	return (i);
// }
// size_t	word_real_size(char *word)
// {
// 	size_t	i;
// 	size_t	size;
//
// 	i = 0;
// 	size = 0;
// 	while (word[i])
// 	{
// 		if (word[i] == '"')
// 		{
// 			incr(word, char c, size_t *size)
// 		}
// 		else if (word[i] == '\'')
// 		{
// 			i++;
// 			while (word[i] && word[i] != '\'')
// 			{
// 				i++;
// 				size++;
// 			}
// 			i++;
// 		}
// 		else
// 		{
// 			while (word[i] && word[i] != '"' && word[i] != '\'')
// 			{
// 				i++;
// 				size++;
// 			}
// 		}
// 	}
// 	return (size);
// }

char	*mask_creator(char *word)
{
	size_t	i;
	size_t	j;
	char	*mask;

	i = 0;
	j = 0;
	mask = ft_calloc(sizeof(char), ft_strlen(word) + 2);
	while (word[i])
	{
		if (word[i] == '"')
			i += mask_seter(&word[i], mask, "\"D", &j);
		else if (word[i] == '\'')
			i += mask_seter(&word[i], mask, "\"D", &j);
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
	return (mask);
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
			i += word_seter(word, new_word, '\"', &j);
		else if (word[i] == '\'')
			i += word_seter(word, new_word, '\'', &j);
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

int main (int ac, char **av)
{
	printf("ma	;%s\n", mask_creator(av[1]));
	// remove_quotes(av[1], strlen(mask_creator(av[1])));
}

// char	*expand(char **env, char *word)
// {
// 	char *mask;
//
// 	
// 	
// }
