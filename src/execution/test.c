#include <minishell.h>

// NOTE: extract_args(char **args);

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

bool	is_shell_var(char *str)
{
	size_t i;

	i = 0;
	if (str[i] == '$' && str[i + 1] && ft_isalnum(str[i + 1]))
		return (true);
	return (false);
}

size_t	count_vars(char *str)
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

char	**find_vars(char *arg)
{
	size_t	i;
	size_t	j;
	size_t	nmb_of_vars;
	char 	*var_start;
	char	**vars;
	
	j = 0;
	nmb_of_vars = count_vars(arg);
	vars = ft_calloc(sizeof(char *), nmb_of_vars);
	if (!vars)
		return (NULL);
	while (nmb_of_vars)
	{
		i = 0;
		var_start = ft_strchr(arg, '$');
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

t_env	*new_env_var(const char *name, const char *value)
{
	t_env *node;

	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		return NULL;
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
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

char	*search_env(char *var, t_env **env)
{
	t_env	*head;

	head = *env;
	while (head)
	{
		if (!ft_strcmp(head->name, var))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

char	*env_var_name(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_strndup(str, i));
}

char	*env_var_val(char *str)
{
	size_t	i;
	char	*value;
	
	i = 1;
	value = ft_strchr(str, '=');
	while (value[i])


}

void	copy_env(t_env *env_list, char **env)
{
	size_t	i;
	size_t	j;

	while (env[i])
	{
		while (env[i][j])
		{
				
		}
	}
}

// TODO :
// il faut que je crees une fonction qui recopie tout le env direct. 
// de plus je dois diviser les VAR qui se composent de plusieurs mots tel que
// VAR = mot1 mot2 mot3.
// je dois creer une fonction qui verifie si le mask est double ou solitaire.
// regrouper tout ce qui precede dans une seule fonction "extraxt_args"
int main (int ac, char **av, char **env)
{
	t_env *env_list = NULL;

	append_env(&env_list, new_env_var("VAR", "zakaria wa3r"));
	append_env(&env_list, new_env_var("VAR1", "zakaria ma wa3rch"));
	append_env(&env_list, new_env_var("VAR2", "zakaria "));
	append_env(&env_list, new_env_var("VAR3", "hanane"));

	print_env_list(env_list);
	printf("val = %s\n", search_env("VAR1", &env_list));
	free_env_list(env_list);
}
