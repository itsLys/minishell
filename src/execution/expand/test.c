#include <stdbool.h>
#include <ctype.h>
#include <ft_string.h>

static bool	can_expand_here(t_str input, t_str mask)
{
	// 1. Check si le caractère courant est $
	if (str_peek(&input) != '$')
		return (false);

	// 2. Check si le contexte est autorisé (N ou D)
	char context = str_peek(&mask);
	if (!(context == 'N' || context == 'D'))
		return (false);

	// 3. Check le caractère suivant dans le mask
	char next_mask;
	t_str tmp_mask = mask;
	str_peek_advance(&tmp_mask);
	next_mask = str_peek(&tmp_mask);

	if (next_mask == 'Q')
		return (true); // ex : $" ou $' → expand juste $

	// 4. Sinon, check si le caractère suivant dans input est alphabétique ou '_'
	t_str tmp_input = input;
	str_peek_advance(&tmp_input);
	char next_input = str_peek(&tmp_input);

	if (isalpha(next_input) || next_input == '_')
		return (true);

	return (false);
}
