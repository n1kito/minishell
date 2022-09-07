#include "minishell.h"

// This function initializes the 2 pointers used to store the name and the var
// It allocates sufficient memory for them to accomodate the strings
// This function takes the linked list and writes the env variables in it
// the first string called NAME takes the beggininning of the string until the =
// the second string VARIABLE takes the rest of the string

int	clean_env(t_env **env, int return_code)
{
	t_env	*tmp;
	t_env	*lst;

	tmp = NULL;
	lst = *env;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->variable)
			free(tmp->variable);
		if (tmp)
			free(tmp);
	}
	*env = NULL;
	return (return_code);
}

static t_env	*env_init(char *envp)
{
	int		equal;
	int		len;
	t_env	*new;

	equal = 1;
	while (envp[equal] && envp[equal] != '=')
		equal++;
	len = ft_strlen(envp);
	new = (t_env *)malloc(sizeof(t_env));
	new->name = malloc(sizeof(char) * equal + 1);
	new->variable = malloc(sizeof(char) * len - equal);
	if (!new || !new->name)
		return (NULL);
	new->is_env = 1;
	new->next = NULL;
	ft_strlcpy(new->name, envp, equal + 1);
	ft_strlcpy(new->variable, &envp[equal + 1], len - equal);
	return (new);
}

// This function initializes the linked list
// This list will be used to store the environment

static int	list_init(t_env **env, char **envp)
{
	int		i;
	t_env	*lst;
	t_env	*tmp;

	i = 0;
	if (!(*env))
	{
		lst = env_init(envp[i]);
		i++;
		if (!lst)
			return (0);
		*env = lst;
	}
	while (envp[i])
	{
		tmp = env_init(envp[i]);
		if (!tmp)
			return (0);
		lst->next = tmp;
		lst = lst->next;
		i++;
	}
	return (1);
}

static int	is_in_env(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static t_env	*get_env_last(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

static int	add_to_env(t_master *master, char *name, char *variable)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (err_msg("malloc fail [add_to_env()][1]", 0, master));
	new_node->name = ft_strdup(name);
	new_node->variable = ft_strdup(variable);
	new_node->is_env = 1;
	new_node->next = NULL;
	if (!new_node->name || !new_node->variable)
		return (err_msg("malloc fail [add_to_env()][2]", 0, master));
	if (!master->env)
		master->env = new_node;
	else
		get_env_last(master->env)->next = new_node;
	return (1);
}

static int	add_missing_variables_to_env(t_master *master)
{
	char	*buffer;
	t_env	*env;

	env = master->env;
	buffer = NULL;
	buffer = getcwd(buffer, PATH_MAX);
	if (!is_in_env(env, "PWD"))
	{
		if (!add_to_env(master, "PWD", buffer))
			return (free(buffer), 0);
	}
	free(buffer);
	if (!is_in_env(env, "SHLVL"))
	{
		if (!add_to_env(master, "SHLVL", "1"))
			return (0);
	}
	if (!is_in_env(env, "_"))
	{
		if (!add_to_env(master, "_", "/usr/bin/env"))
			return (0);
	}
	return (1);
}

/*This function takes the environment given as an argument*/
/*It then transforms it into a linked list with*/
/*It then returns a pointer to the first element of the list*/
int	get_env(char **envp, t_master *master)
{
	int		ret;

	ret = 1;
	if (envp && *envp)
		ret = list_init(&master->env, envp);
	if (!ret)
		return (clean_env(&master->env, 0));
	if (!add_missing_variables_to_env(master))
		return (clean_env(&master->env, 0));
	return (1);
}
