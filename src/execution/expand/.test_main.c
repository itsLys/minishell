// #include <minishell.h>
#include <execution.h>
#include <ft_string.h>

void	free_tokens(t_token **head)
{
	t_token	*next;
	t_token	*tmp;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->val);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

void	ast_free(t_ast_node *node)
{
	t_ast_node	*next;

	while (node)
	{
		next = node->sibling;
		if (node->child)
			ast_free(node->child);
		free(node->value);
		free(node);
		node = next;
	}
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

void print_2d_array(char **array, size_t size)
{
	size_t i = 0;
	while (array[i])
	{
		printf("[%s], ", array[i]);
		i++;
	}
	printf("\n");
}
int main(int ac, char **av)
{
	t_env *env_list = NULL;
	append_env(&env_list, new_env_var("VAR", ".cb", true));
	append_env(&env_list, new_env_var("VAR1", "bonjour \"je\" suis", true));
	append_env(&env_list, new_env_var("VAR2", "	", true));
	append_env(&env_list, new_env_var("VAR3", "pskch pskch", true));
	append_env(&env_list, new_env_var("VAR4", "wa3r", true));
	append_env(&env_list, new_env_var("VAR5", "hamid", true));
	append_env(&env_list, new_env_var("VAR6", "*", true));
	append_env(&env_list, new_env_var("b", "$b", true));
	append_env(&env_list, new_env_var("a", "ls        -la", true));
	append_env(&env_list, new_env_var("CHI7AJA", "i", true));
	while (1)
	{

		t_str	line;
		str_create(&line, readline("enter :"));
		t_str	mask = build_mask(&line);
		// printf("the mask is = %s\n", mask.data);
		expand_var(&line, env_list, &mask);
		// printf("%s\n%s\n", line.data, mask.data);
		t_str_arr args = split_input(&line, &mask);
		char **arg = extract_args(&args, env_list);
		print_2d_array(arg, args.size);
		if (!strncmp("clear", line.data, 6))
			system("clear");
	}
	free_env_list(env_list);
}
