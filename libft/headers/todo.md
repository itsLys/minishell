[x] void		str_arr_init(t_str_arr *arr);
[x] void		str_arr_destroy(t_str_arr *arr);
[x] void		str_arr_push(t_str_arr *arr, char *text);
[x] void		str_arr_extend(t_str_arr *dest, t_str_arr *src);
[x] t_str		*str_arr_get(t_str_arr *arr, size_t index);
[x] t_str		*str_arr_peek(t_str_arr *arr);
[x] t_str		*str_arr_peek_advance(t_str_arr *arr);
[x] void		str_arr_peek_reset(t_str_arr *arr);
[x] void		str_arr_insert(t_str_arr *arr, size_t index, char *text);
[x] void		str_arr_remove(t_str_arr *arr, size_t index);
[x] void		str_arr_free(t_str_arr *arr);
[x] t_str_arr	str_arr_split(t_str *str, char c);
[x] void		print_str_arr(t_str_arr *arr);
[x] char		**str_arr_to_cstr_array(t_str_arr *arr);
[x] t_str_arr	str_arr_from_cstr_array(char **cstr);
[x] void		str_init(t_str *str);
[x] void		str_destroy(t_str *str);
[x] void		str_ensure_capacity(t_str *str, size_t needed_capacity);
[x] void		str_create(t_str *str, char *text);
[x] t_str		str_new(char *src);
[x] void		str_set(t_str *str, char *new_data);
[x] t_str		str_new_fill(size_t size, char c);
[x] t_str		str_substr(t_str *str, size_t start, size_t len);
[x] t_str		str_join(t_str *array, size_t len, char *delimiter);
[x] t_str		*str_split(t_str *s, char delimiter, size_t *count);
[x] void		str_insert(t_str *str, size_t pos, char *to_insert);
[x] void		str_append(t_str *str, char *to_add);
[x] void		str_prepend(t_str *str, char *to_add);
[x] void		str_replace(t_str *str, char *old_str, char *new_str, short mode);
[x] void		str_replace_char(t_str *str, char old_char, char new_char);
[x] void		str_surround(t_str *str, size_t start, size_t size, char *to_add);
[x] void		str_erase(t_str *str, size_t pos, size_t len);
[x] void		str_repeat(t_str *str, size_t n);
[x] void		str_clear(t_str *str);
[x] void		str_append_char(t_str *str, char c);
[x] char		str_peek(t_str *str);
[x] char		str_peek_advance(t_str *str);
[x] char		str_peek_reset(t_str *str);
[x] char		str_char_at(t_str *str, size_t i);
[x] char		str_shift(t_str *str);
[x] void		str_shift_by(t_str *str, size_t offset);
[x] void		str_shift_while(t_str *str, char *charset);
[x] ssize_t		str_find(t_str *str, char *to_find);
[] void		str_segment_remove(t_str *str, size_t start, size_t length);
[] char		*str_segment_extract(t_str *str, size_t start, size_t length);
[] char		*str_segment_slice(t_str *str, size_t start, size_t length);
[] void		str_segment_replace(t_str *str, 
 				size_t start, 
 				size_t length, 
 				char *new_text);
[] void		str_segment_set(t_str *str,
 				size_t start, 
 				size_t lenght, 
 				size_t end);
[] size_t		str_segments_count(t_str *str, char delimiter);
[] int			str_match(t_str *str,
 				char *target,
 				int (*cmp)(const char *, const char *, size_t),
 				size_t start);
[] char		*convert_str(t_str *str);
[] char		**convert_str_arr(t_str_arr *arr);
[] char		*str_to_cstr(t_str *str);
[] char		*convert_str(t_str *str);
[] t_str		convert_cstr(char *cstr);
[] t_str_arr	convert_vec_strarr(char **og);
[] t_str		str_from_cstr(const char *cstr);
[] size_t		str_total_size(t_str *arr, size_t len, size_t delim_len);
[] void		str_fill(t_str *result, t_str *arr, size_t len, char *d);
