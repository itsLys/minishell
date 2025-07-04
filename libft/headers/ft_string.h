/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:25:41 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/30 17:36:48 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <libft.h>
# include <stdio.h>

# define INIT_CAPACITY 16
# define ALL 0
# define ONE 1

typedef struct s_string
{
	char	*data;
	size_t	size;
	size_t	capacity;
	size_t	peek;
}	t_str;

typedef struct s_str_arr
{
	t_str	*items;
	size_t	size;
	size_t	capacity;
	size_t	peek;
}	t_str_arr;

void		str_arr_init(t_str_arr *arr);
void		str_arr_push(t_str_arr *arr, char *text);
void		str_arr_destroy(t_str_arr *arr);
void		str_arr_extend(t_str_arr *dest, t_str_arr *src);
t_str		*str_arr_get(t_str_arr *arr, size_t index);
void		print_str_arr(t_str_arr *arr);
t_str		*str_arr_peek(t_str_arr *arr);
t_str		*str_arr_peek_advance(t_str_arr *arr);
void		str_arr_peek_reset(t_str_arr *arr);
void		str_arr_insert(t_str_arr *arr, size_t index, char *text);
void		str_arr_remove(t_str_arr *arr, size_t index);
void		str_arr_free(t_str_arr *arr);

void		str_init(t_str *str);
void		str_destroy(t_str *str);
void		str_ensure_capacity(t_str *str, size_t needed_capacity);
void		str_set(t_str *str, char *new_data);
void		str_create(t_str *str, char *text);
t_str		str_new(char *src);
t_str		str_substr(t_str *str, size_t start, size_t len);
t_str		str_new_fill(size_t size, char c);

void		str_clear(t_str *str);
void		str_insert(t_str *str, size_t pos, char *to_insert);
void		str_erase(t_str *str, size_t pos, size_t len);
void		str_append(t_str *str, char *to_add);
void		str_prepend(t_str *str, char *to_add);
void		str_replace(t_str *str, char *old_str, char *new_str, short mode);
void		str_replace_char(t_str *str, char old_char, char new_char);
void		str_repeat(t_str *str, size_t n);

ssize_t		str_find(t_str *str, char *to_find);

t_str		str_join(t_str *array, size_t len, char *delimiter);
t_str		*str_split(t_str *s, char delimiter, size_t *count);

char		str_peek(t_str *str);
char		str_peek_advance(t_str *str);
char		str_peek_reset(t_str *str);
char 		str_char_at(t_str *str, size_t i);

char		str_shift(t_str *str);
void		str_shift_by(t_str *str, size_t offset);
void		str_shift_while(t_str *str, char *charset);

int			str_match(t_str *str, char *target,
				int (*cmp)(const char *, const char *, size_t), size_t start);
void		str_segment_remove(t_str *str, size_t start,
				size_t length);
size_t		str_segments_count(t_str *str, char delimiter);
char		*str_segment_extract(t_str *str, size_t start, size_t length);
char		*str_segment_slice(t_str *str, size_t start, size_t length);
void		str_segment_replace(t_str *str, size_t start,
				size_t length, char *new_text);
void		str_segment_set(t_str *str, size_t start,
				size_t lenght, size_t end);

char		*convert_str(t_str *str);
char		**convert_str_arr(t_str_arr *arr);
t_str		convert_cstr(char *cstr);
t_str_arr	convert_vec_strarr(char **og);
t_str		str_from_cstr(const char *cstr);
char		*str_to_cstr(t_str *str);
char		*convert_str(t_str *str);
char		**str_arr_to_cstr_array(t_str_arr *arr);
t_str_arr	str_arr_from_cstr_array(char **cstr);
void		str_append_char(t_str *str, char c);

#endif
