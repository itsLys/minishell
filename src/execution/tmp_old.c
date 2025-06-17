#include <minishell.h>
#include <execution.h>

// NOTE: extract_args(char **args, t_env *env);

void print_2d_array(char **array)
{
	int i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

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

bool	is_shell_var(const char *str)
{
	if (str[0] == '$'
		&& (str[1] && (ft_isalnum(str[1]) || str[1] == '_')))
		return (true);
	return (false);
}

size_t	count_vars(const char *str)
{
	size_t	i;
	size_t	vars_counter;

	i = 0;
	vars_counter = 0;
	while (str[i])
	{
		if (is_shell_var(&str[i]))
			vars_counter++;
		i++;
	}
	return (vars_counter);
}

char	**find_vars_in_str(char *arg)
{
	size_t	i;
	size_t	j;
	size_t	nmb_of_vars;
	char 	*var_start;
	char	**vars;
	char	*copy;

	j = 0;
	nmb_of_vars = count_vars(arg);
	vars = ft_calloc(sizeof(char *), nmb_of_vars + 1);
	if (!vars)
		return (NULL);
	copy = ft_strdup(arg);
	if (!copy)
		return (NULL);
	while (true)
	{
		i = 0;
		var_start = ft_strchr(copy, '$');
		if (!var_start)
			break ;
		erase(var_start, 0);
		while (var_start[i] && ft_isalnum(var_start[i]))
			i++;
		vars[j] = ft_strndup(var_start, i);
		i++;
		j++;
	}
	return (vars);
}

void	append_env(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!*head)
	{
		*head = new_node;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_env	*new_env_var(const char *name, const char *value, bool exported)
{
	t_env *node;

	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		return NULL;
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
	node->exported = exported;
	node->next = NULL;
	return (node);
}

void	print_env_list(t_env *env)
{
	while (env)
	{
		printf("%s=%s", env->name, env->value);
		printf("\n");
		env = env->next;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

char *get_env_value(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (ft_strdup(""));
}

bool	is_expandable(char *mask)
{
	return ((mask[0] == 'D' || mask[0] == 'N'));
}

char	*alloc_varname(char *input)
{
	size_t	i;
	char	*varname;

	i = 0;
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	varname = ft_calloc(sizeof(char), i + 1);
	return (varname);
}

size_t sizeof_new_input(char *input, t_env *env, char *mask)
{
	size_t i = 0;
	size_t size = 0;
	char *varname;
	char *value;
	char inside;

	while (input[i])
	{
		if (is_shell_var(&input[i]) && is_expandable(&mask[i]))
		{
			inside = mask[i];
			i++; // skip $
			varname = alloc_varname(&input[i]);
			size_t j = 0;
			while ((ft_isalnum(input[i]) || input[i] == '_') && mask[i] == inside)
				varname[j++] = input[i++];
			value = get_env_value(env, varname);
			size += ft_strlen(value);
			free(varname);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
}

char	*insert_str(char *src, char *to_insert, size_t index)
{
	size_t	len_src;
	size_t	len_insert;
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_src = ft_strlen(src);
	len_insert = ft_strlen(to_insert);
	if (index > len_src)
		return (NULL);
	new_str = ft_calloc(len_src + len_insert + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (i < index)
	{
		new_str[i] = src[i];
		i++;
	}
	while (j < len_insert)
		new_str[i++] = to_insert[j++];
	while (index < len_src)
		new_str[i++] = src[index++];
	return (free(src), new_str);
}

char *expand_vars(char *input, t_env *env, char **mask)
{
	char	*result;
	char	*varname;
	char	*value;
	char	*new_mask;
	char	inside;
	size_t	i[4];

	ft_memset(i, 0, sizeof(i));
	result = ft_calloc(sizeof(char) ,sizeof_new_input(input, env, *mask));
	new_mask = ft_calloc(sizeof(char) ,sizeof_new_input(input, env, *mask));
	while (input[i[0]])
	{
		if (is_shell_var(&input[i[0]]) && is_expandable(&(*mask)[i[0]]))
		{
			inside = (*mask)[i[0]];
			i[0]++;
			i[2] = 0;
			i[3] = 0;
			varname = alloc_varname(&input[i[0]]);
			while ((ft_isalnum(input[i[0]]) || input[i[0]] == '_')
					&& ((*mask)[i[0]] == inside))
				varname[i[2]++] = input[i[0]++];
			value = get_env_value(env, varname);
			while (value[i[3]])
			{
				result[i[1]] = value[i[3]++];
				new_mask[i[1]++] = inside;
			}
			free(varname);
		}
		else
		{
			result[i[1]] = input[i[0]];
			new_mask[i[1]++] = (*mask)[i[0]++];
		}
	}
	free((*mask));
	(*mask) = new_mask;
	return (result);
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
// char	**extract_args(char **args)
// {
//
// }

// TODO : 
int main(int ac, char **av)
{
	t_env *env_list = NULL;
	append_env(&env_list, new_env_var("VAR", ".c b", true));
	append_env(&env_list, new_env_var("VAR1", "bonjour je suis", true));
	append_env(&env_list, new_env_var("VAR2", "	", true));
	append_env(&env_list, new_env_var("VAR3", "pskch pskch", true));
	append_env(&env_list, new_env_var("VAR4", "wa3r", true));
	append_env(&env_list, new_env_var("VAR5", "hamid", true));
	
	char *mask = quote_mask(av[1]); // $VAR1"$"'$VAR3'
	// char *input = "$VAR1$VAR3";
	remove_quotes(av[1], mask);
	char *output= expand_vars(av[1], env_list, &mask);
	printf("%s\n%s\n", output, mask);
	free(output);
	free_env_list(env_list);
}
