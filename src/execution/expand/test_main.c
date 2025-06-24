// #include <minishell.h>
#include <execution.h>
#include <ft_string.h>

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
	append_env(&env_list, new_env_var("CHI7A", "i", true));
	while (1)
	{

		t_str	line;
		str_create(&line, readline("enter :"));
		t_str	mask = build_mask(&line);
		// printf("the mask is = %s\n", mask.data);
		expand_var(&line, env_list, &mask);
		// printf("%s\n%s\n", line.data, mask.data);
		t_str_arr args = split_input(&line, &mask);
		t_str_arr arg = extract_args(&args, env_list);
		print_str_arr(&arg);
		if (!strncmp("clear", line.data, 6))
			system("clear");
	}
	free_env_list(env_list);
}
