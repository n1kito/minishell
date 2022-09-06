#include "minishell.h"

// This function initializes the 2 pointers used to store the name and the var
// It allocates sufficient memory for them to accomodate the strings
// This function takes the linked list and writes the env variables in it
// the first string called NAME takes the beggininning of the string until the =
// the second string VARIABLE takes the rest of the string

static int	var_env_malloc_init(t_env *env, char **envp)
{
	int		i;
	int		equal;
	int		len;

	i = 0;
	while (env)
	{
		equal = 1;
		len = ft_strlen(envp[i]);
		while (envp[i][equal] != '=')
			equal++;
		env->name = malloc(sizeof(char) * equal + 1);
		env->variable = malloc(sizeof(char) * len - equal);
		if (!env->variable || !env->name)
			return (0);
		ft_strlcpy(env->name, envp[i], equal + 1);
		ft_strlcpy(env->variable, &(envp[i][equal + 1]), len - equal);
		env = env->next;
		i++;
	}
	return (1);
}

void	clean_env(t_env **env)
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
}

static t_env	*env_init(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->variable = NULL;
	new->is_env = 1;
	new->next = NULL;
	return (new);
}

// This function initializes the linked list
// This list will be used to store the environment

static int	list_init(t_env **env, char **envp)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = NULL;
	while (envp[i])
	{
		tmp = env_init();
		if (!tmp)
			return (0);
		if (!(*env))
			*env = tmp;
		else
		{
			tmp->next = *env;
			*env = tmp;
		}
		i++;
	}
	return (1);
}

static int	min_env(t_env **env)
{
	int		len;
	char	*buffer;
	t_env	*tmp;

	len = 3;
	tmp = NULL;
	buffer = NULL;
	buffer = getcwd(buffer, PATH_MAX);
	while (len)
	{
		tmp = env_init();
		if (len == 3)
		{
			tmp->name = ft_strdup("PWD");
			tmp->variable = ft_strdup(buffer);
		}
		if (len == 2)
		{
			tmp->name = ft_strdup("SHLVL");
			tmp->variable = ft_strdup("1");
		}
		if (len == 1)
		{
			tmp->name = ft_strdup("_");
			tmp->variable = ft_strdup("/usr/bin/env");
		}
		if (!*env)
			*env = tmp;
		else
			(*env)->next = tmp;
		tmp = tmp->next;
		len--;
	}
	return (0);
}

// This function takes the environment given as an argument
// It then transforms it into a linked list with
// It then returns a pointer to the first element of the list
int	get_env(char **envp, t_env **ptr_env)
{
	int		ret;

	ret = list_init(ptr_env, envp);
	if (ret)
		ret = var_env_malloc_init(*ptr_env, envp);
	else
		clean_env(ptr_env);
	check_missing_env_values(ptr_env);
	return (ret);
}
