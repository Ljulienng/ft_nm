#include "ft_nm.h"

char *all_in_min(char *str)
{
    int i = 0;
    // int lengh = ft_strlen(str);
    char *tab = malloc(sizeof(char) * (ft_strlen(str) + 1));

    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            tab[i] = str[i] + 32;
        else
            tab[i] = str[i];
        i++;
    }
    tab[i] = '\0';
    return tab;
}

int is_smaller(char *tmp, char *tab_str)
{
    char *str_min = all_in_min(tab_str);
    char *tmp_min = all_in_min(tmp);
    int i = 0;
    int j = 0;

    while (tmp_min[i] == '_')
        i++;
    while (str_min[j] == '_')
        j++;

    while (tmp_min[i] && str_min[j])
    {
        if (tmp_min[i] == '_' && str_min[j] != '_' && i == j)
        {
            free(tmp_min);
            free(str_min);
            return 1;
        }
        if (tmp_min[i] != '_' && str_min[j] == '_' && i == j)
        {
            free(tmp_min);
            free(str_min);
            return 0;
        }
        if (tmp_min[i] < str_min[j])
        {
            free(str_min);
            free(tmp_min);
            return 0;
        }
        if (tmp_min[i] > str_min[j])
        {
            free(tmp_min);
            free(str_min);
            return 1;
        }
        j++;
        i++;
    }
    if (ft_strlen_without_tiret(tmp_min) == ft_strlen_without_tiret(str_min))
    {
        if (tmp_min[0] == '_' && str_min[0] != '_')
        {
            free(tmp_min);
            free(str_min);
            return 0;
        }

        if (tmp_min[0] != '_' && str_min[0] == '_')
        {
            free(tmp_min);
            free(str_min);
            return 1;
        }
    }
    if (ft_strlen(str_min) < ft_strlen(tmp_min))
    {
        free(tmp_min);
        free(str_min);
        return 1;
    }
    free(tmp_min);
    free(str_min);
    return 0;
}

void tri(char **name_tab, int type)
{
    if (type == TYPE_P)
        print_final(name_tab, type);
    char *tmp = NULL;
    char **tri_tab = (char **)malloc(sizeof(char *) * (size_tab(name_tab) + 1));
    int i = 0;
    int letter = 0;
    tmp = name_tab[0];
    int to_delete = 0;
    while (i < size_tab(name_tab))
    {
        while (letter < size_tab(name_tab))
        {
            if (ft_strlen(name_tab[letter]) != 0)
            {
                if (is_smaller(tmp, name_tab[letter]) == 1)
                {
                    tmp = name_tab[letter];
                    to_delete = letter;
                }
            }
            letter++;
        }
        tri_tab[i] = tmp;
        i++;
        letter = 0;
        name_tab[to_delete] = "";
        for (int j = 0; j < size_tab(name_tab); j++)
        {
            if (ft_strlen(name_tab[letter]) != 0)
            {
                tmp = name_tab[j];
                to_delete = j;
                break;
            }
            to_delete = 0;
        }
    }
    tri_tab[i] = NULL;
    if (type == TYPE_R)
        print_final_with_r(tri_tab);
    else
        print_final(tri_tab, type);
    free(tri_tab);
    free_all();
    return;
}