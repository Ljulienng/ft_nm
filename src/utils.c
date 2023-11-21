#include "ft_nm.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (6);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n <= 0)
		return (0);
	while (n > 1 && (*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void ft_lstadd_back(t_all **alst, t_all *new)
{
	t_all *lst;

	lst = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

t_all *fill_all(uint64_t address, char *name, char symbole, int type)
{
	t_all *lst = malloc(sizeof(t_all));

	lst->address = address;
	lst->name = name;
	lst->symbole = symbole;
	lst->type = type;
	lst->type = 0;
	lst->next = NULL;

	return (lst);
}

int ft_strlen_without_tiret(char *s)
{
	int i;

	int count = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != '_')
			count++;
		i++;
	}
	return (count);
}

int size_tab(char **name_tab)
{
	int size_tab = 0;

	while (name_tab[size_tab])
	{
		size_tab++;
	}
	return size_tab;
}

void free_all()
{
	t_all *temp;
	while (g_all->next)
	{
		temp = g_all;
		g_all = g_all->next;
		free(temp);
	}
	free(g_all);
	g_all = NULL;
	return;
}

void free_tab(char **tab)
{
	free(tab);
	return;
}

int exit_error(char *str, int ret)
{
	printf("%s\n", str);
	return (ret);
}