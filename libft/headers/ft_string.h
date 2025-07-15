/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:25:41 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/15 22:10:07 by ihajji           ###   ########.fr       */
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

// str_arr_core.c
void		str_arr_init(t_str_arr *arr);
void		str_arr_destroy(t_str_arr *arr);
void		str_arr_push(t_str_arr *arr, char *text);
void		str_arr_extend(t_str_arr *dest, t_str_arr *src);
t_str		*str_arr_get(t_str_arr *arr, size_t index);

// str_arr_utils.c
t_str		*str_arr_peek(t_str_arr *arr);
t_str		*str_arr_peek_advance(t_str_arr *arr);
void		str_arr_peek_reset(t_str_arr *arr);
void		str_arr_insert(t_str_arr *arr, size_t index, char *text);
void		str_arr_remove(t_str_arr *arr, size_t index);

// str_arr_extra.c
void		str_arr_free(t_str_arr *arr);
t_str_arr	str_arr_split(t_str *str, char c);
void		print_str_arr(t_str_arr *arr);
char		**str_arr_to_cstr_array(t_str_arr *arr);
t_str_arr	str_arr_from_cstr_array(char **cstr);

// str_core.c
void		str_init(t_str *str);
void		str_destroy(t_str *str);
void		str_ensure_capacity(t_str *str, size_t needed_capacity);
void		str_create(t_str *str, char *text);
t_str		str_new(char *src);

// str_build.c
void		str_set(t_str *str, char *new_data);
t_str		str_new_fill(size_t size, char c);
t_str		str_substr(t_str *str, size_t start, size_t len);
t_str		str_join(t_str *array, size_t len, char *delimiter);
t_str		*str_split(t_str *s, char delimiter, size_t *count);

// str_mod1.c
void		str_insert(t_str *str, size_t pos, char *to_insert);
void		str_append(t_str *str, char *to_add);
void		str_prepend(t_str *str, char *to_add);
void		str_replace(t_str *str, char *old_str, char *new_str, short mode);
void		str_replace_char(t_str *str, char old_char, char new_char);

// str_mod2.c
void		str_surround(t_str *str, size_t start, size_t size, char *to_add);
void		str_erase(t_str *str, size_t pos, size_t len);
void		str_repeat(t_str *str, size_t n);
void		str_clear(t_str *str);
void		str_append_char(t_str *str, char c);

// str_peek.c
char		str_peek(t_str *str);
char		str_peek_advance(t_str *str);
char		str_peek_reset(t_str *str);
char		str_char_at(t_str *str, size_t i);

// str_shift.c
char		str_shift(t_str *str);
void		str_shift_by(t_str *str, size_t offset);
void		str_shift_while(t_str *str, char *charset);
ssize_t		str_find(t_str *str, char *to_find);

// str_seg1.c
void		str_segment_remove(t_str *str, size_t start, size_t length);
char		*str_segment_extract(t_str *str, size_t start, size_t length);
char		*str_segment_slice(t_str *str, size_t start, size_t length);
void		str_segment_replace(t_str *str, 
				size_t start, 
				size_t length, 
				char *new_text);

// str_seg2.c
void		str_segment_set(t_str *str,
				size_t start, 
				size_t lenght, 
				size_t end);
size_t		str_segments_count(t_str *str, char delimiter);
int			str_match(t_str *str,
				char *target,
				int (*cmp)(const char *, const char *, size_t),
				size_t start);

// str_convert1.c
char		*convert_str(t_str *str);
char		**convert_str_arr(t_str_arr *arr);
char		*str_to_cstr(t_str *str);
// str_convert2.c
t_str		convert_cstr(char *cstr);
t_str_arr	convert_vec_strarr(char **og);
t_str		str_from_cstr(const char *cstr);

// str_utils.c
size_t		str_total_size(t_str *arr, size_t len, size_t delim_len);
void		str_fill(t_str *result, t_str *arr, size_t len, char *d);
void		str_fill_split(t_str *str, char d, t_str *arr, size_t c);
// str_arr_core.c
// str_arr_utils.c
// str_arr_extra.c
// str_core.c
// str_build.c
// str_mod1.c
// str_mod2.c
// str_peek.c
// str_shift.c
// str_seg1.c
// str_seg2.c
// str_convert1.c
// str_convert2.c

#endif
