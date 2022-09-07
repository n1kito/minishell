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

int	check_if_is_in_env(t_env *env, char *name)
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

int	add_missing_variables_to_env(t_env **env, int PWD, int SHLVL, int UN_SC)
{
	t_env	*tmp;
	char	*buffer;

	tmp = *env;
	buffer = NULL;
	getcwd(buffer, PATH_MAX);
	while (tmp)
	if (!PWD && !(*env))
		*env = env_init("PWD=");
	else if (!PWD)
	{
		(*env)->next = env_init("PWD=");
		(*env) = (*env)->next;
	}
	if (!PWD)
	{
		if ((*env)->variable)
			free((*env)->variable);
		(*env)->variable = ft_strdup(buffer);
	}
	if (!SHLVL)
	{
		(*env)->next = env_init("SHLVL=1");
		(*env) = (*env)->next;
	}
	if (!UN_SC)
		(*env)->next = env_init("_=/usr/bin/env");
	return (1);
}

/*This function takes the environment given as an argument*/
/*It then transforms it into a linked list with*/
/*It then returns a pointer to the first element of the list*/
int	get_env(char **envp, t_env **ptr_env)
{
	int		PWD;
	int		SHLVL;
	int		UN_SC;
	int		ret;
	t_env	*start;

	ret = 1;
	if (envp && *envp)
		ret = list_init(ptr_env, envp);
	if (!ret)
		return (clean_env(ptr_env, 0));
	start = *ptr_env;
	PWD = check_if_is_in_env(start, "PWD");
	SHLVL = check_if_is_in_env(start, "SHLVL");
	UN_SC = check_if_is_in_env(start, "_");
	if (PWD == 1 && SHLVL == 1 && UN_SC == 1)
		return (1);
	if (!add_missing_variables_to_env(&start, PWD, SHLVL, UN_SC))
		return (clean_env(ptr_env, 0));
	return (1);
}
