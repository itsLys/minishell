#include <minishell.h>

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
	size_t i;

	i = 0;
	if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
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

// char	**find_vars_in_str(char *arg)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	nmb_of_vars;
// 	char 	*var_start;
// 	char	**vars;
// 	char	*copy;
//
// 	j = 0;
// 	nmb_of_vars = count_vars(arg);
// 	vars = ft_calloc(sizeof(char *), nmb_of_vars + 1);
// 	if (!vars)
// 		return (NULL);
// 	copy = ft_strdup(arg);
// 	if (!copy)
// 		return (NULL);
// 	while (nmb_of_vars)
// 	{
// 		i = 0;
// 		var_start = ft_strchr(copy, '$');
// 		if (!var_start)
// 			break ;
// 		erase(var_start, 0);
// 		while (var_start[i] && ft_isalnum(var_start[i]))
// 			i++;
// 		vars[j] = ft_strndup(var_start, i);
// 		i++;
// 		j++;
// 	}
// 	return (vars);
// }

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
	node->is_exported = exported;
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

size_t	sizeof_new_input(char *input, t_env *env)
{
	char	**vars;
	size_t	new_size;
	size_t	i;

	i = 0;
	new_size = ft_strlen(input);
	vars = find_vars_in_str(input);
	while (vars[i])
	{
		new_size -= ft_strlen(vars[i]) + 1;
		new_size += ft_strlen(get_env_value(env, vars[i++]));
	}
	return (new_size);
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

char *expand_vars(char *input, t_env *env)
{
	char	*result;
	char	*varname;
	char	*value;
	size_t	index[4];

	ft_memset(index, 0, sizeof(index));
	result = ft_calloc(sizeof(char) ,sizeof_new_input(input, env) + 1);
	while (input[index[0]])
	{
		if (is_shell_var(&input[index[0]]))
		{
			index[0]++;
			index[2] = 0;
			index[3] = 0;
			varname = alloc_varname(&input[index[0]]);
			while (ft_isalnum(input[index[0]]) || input[index[0]] == '_')
				varname[index[2]++] = input[index[0]++];
			value = get_env_value(env, varname);
			while (value[index[3]])
				result[index[1]++] = value[index[3]++];
			free(varname);
			free(value);
		}
		else
			result[index[1]++] = input[index[0]++];
	}
	return (result);
}

int main(void)
{
	t_env *env_list = NULL;
	append_env(&env_list, new_env_var("VAR", "zakaria", true));
	append_env(&env_list, new_env_var("VAR1", "bonjour", true));
	append_env(&env_list, new_env_var("VAR2", "		", true));
	append_env(&env_list, new_env_var("VAR3", "monde", true));
	append_env(&env_list, new_env_var("VAR4", "monde", true));
	append_env(&env_list, new_env_var("VAR5", "monde", true));
	char *s1 = expand_vars("$VAR$VAR2'est$VAR2'le$VAR2'roi'$VAR2'du$VAR2$VAR3", env_list);
	printf("%s\n", s1);
	free(s1);
	free_env_list(env_list);
}
