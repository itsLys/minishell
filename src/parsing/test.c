/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:20:58 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/24 12:21:51 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Type: %s", tokens->type);
		if (tokens->val)
			printf(" | Value: %s", tokens->val);
		printf("\n");
		tokens = tokens->next;
	}
}
