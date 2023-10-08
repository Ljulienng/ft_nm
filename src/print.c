#include "ft_nm.h"

void add_symbol(int j, unsigned char symbol_type, unsigned char symbol_binding, char *symtab_str, Elf64_Sym *symtab, int type)
{
    if (ft_strlen(symtab_str + symtab[j].st_name) > 0 && symbol_type != 4)
    {
        if (symbol_type == 6 && symbol_binding == 2 && (symtab[j].st_shndx == 21 || symtab[j].st_shndx == 22))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'W', 0));
            // printf("%c %s \n", 'W', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 6 && symbol_binding == 1 && (symtab[j].st_shndx == 21 || symtab[j].st_shndx == 22))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'B', 0));
            // printf("%c %s \n", 'B', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 6 && symbol_binding == 0 && (symtab[j].st_shndx == 21 || symtab[j].st_shndx == 22))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'b', 0));
            // printf("%c %s \n", 'b', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 2 && symbol_binding == 2 && (symtab[j].st_shndx <= 17 && symtab[j].st_shndx >= 8))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'W', 0));
            // printf("%c %s \n", 'W', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 2 && symbol_binding == 1 && ((symtab[j].st_shndx >= 12 && symtab[j].st_shndx <= 17) || symtab[j].st_shndx == 2 || symtab[j].st_shndx == 1))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'T', 0));
            // printf("%c %s \n", 'T', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 2 && symbol_binding == 1 && symtab[j].st_shndx == 0)
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'U', 0));
            // printf("%c %s \n", 'U', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 2 && symbol_binding == 0 && ((symtab[j].st_shndx <= 16 && symtab[j].st_shndx >= 14) || symtab[j].st_shndx == 10 || (symtab[j].st_shndx >= 1 && symtab[j].st_shndx <= 4)))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 't', 0));
            // printf("%c %s \n", 't', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 1 && symbol_binding == 2 && (symtab[j].st_shndx >= 17 && symtab[j].st_shndx <= 27))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'V', 0));
            // printf("%c %s \n", 'V', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 1 && symbol_binding == 2 && (symtab[j].st_shndx == 0))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'v', 0));
            // printf("%c %s \n", 'v', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 1 && symbol_binding == 1 && ((symtab[j].st_shndx >= 21 && symtab[j].st_shndx <= 26) || symtab[j].st_shndx == 29))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'D', 0));
            // printf("%c %s \n", 'D', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 1 && symbol_binding == 1 && (symtab[j].st_shndx <= 18 && symtab[j].st_shndx >= 16))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'R', 0));
            // printf("%c %s \n", 'R', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 1 && symbol_binding == 1 && (symtab[j].st_shndx == 0))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'U', 0));
            // printf("%c %s \n", 'U', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 1 && symbol_binding == 0 && ((symtab[j].st_shndx >= 26 && symtab[j].st_shndx <= 27) || symtab[j].st_shndx == 7 || symtab[j].st_shndx == 10 || (symtab[j].st_shndx >= 30 && symtab[j].st_shndx <= 1139) || (symtab[j].st_shndx >= 1231)))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'b', 0));
            // printf("%c %s \n", 'b', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 1 && symbol_binding == 0 && ((symtab[j].st_shndx >= 21 && symtab[j].st_shndx <= 25) || (symtab[j].st_shndx >= 28 && symtab[j].st_shndx <= 30) || symtab[j].st_shndx == 1143 || symtab[j].st_shndx == 19))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'd', 0));
            // printf("%c %s \n", 'd', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 1 && symbol_binding == 0 && (symtab[j].st_shndx == 4 || symtab[j].st_shndx == 20 || symtab[j].st_shndx == 18 || symtab[j].st_shndx == 1140))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'r', 0));
            // printf("%c %s \n", 'r', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 0 && symbol_binding == 2 && (symtab[j].st_shndx >= 25 && symtab[j].st_shndx <= 30))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'W', 0));
            // printf("%c %s \n", 'W', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 0 && (symbol_binding == 2 || symbol_binding == 1) && symtab[j].st_shndx == 24)
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'D', 0));
            // printf("%c %s \n", 'D', symtab_str + symtab[j].st_name);
        }
        else if ((symbol_type == 0 || symbol_type == 2) && symbol_binding == 2 && symtab[j].st_shndx == 0)
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'w', 0));
            // printf("%c %s \n", 'w', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 0 && symbol_binding == 1 && (symtab[j].st_shndx == 25 || symtab[j].st_shndx == 29))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'D', 0));
            // printf("%c %s \n", 'D', symtab_str + symtab[j].st_name);
        }
        else if ((symbol_type == 0 || symbol_type == 1) && symbol_binding == 1 && (symtab[j].st_shndx == 26 || symtab[j].st_shndx == 27 || symtab[j].st_shndx == 28 || symtab[j].st_shndx == 4 || symtab[j].st_shndx == 30 || symtab[j].st_shndx == 31))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'B', 0));
            // printf("%c %s \n", 'B', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 0 && symbol_binding == 1 && ((symtab[j].st_shndx >= 14 && symtab[j].st_shndx <= 16) || symtab[j].st_shndx == 2))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'T', 0));
            // printf("%c %s \n", 'T', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 0 && symbol_binding == 1 && symtab[j].st_shndx == 0)
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'U', 0));
            // printf("%c %s \n", 'U', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 0 && symbol_binding == 0 && (symtab[j].st_shndx == 24))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'd', 0));
            // printf("%c %s \n", 'd', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 0 && symbol_binding == 0 && (symtab[j].st_shndx >= 29 || (symtab[j].st_shndx >= 15 && symtab[j].st_shndx <= 23) || symtab[j].st_shndx == 6 || symtab[j].st_shndx == 13))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'r', 0));
            // printf("%c %s \n", 'r', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 0 && symbol_binding == 0 && (symtab[j].st_shndx == 14 || symtab[j].st_shndx == 2))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 't', 0));
            // printf("%c %s \n", 't', symtab_str + symtab[j].st_name);
        }
        else if (symbol_type == 0 && symbol_binding == 0 && (symtab[j].st_shndx == 1))
        {
            ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'd', 0));
            // printf("%c %s \n", 'd', symtab_str + symtab[j].st_name);
        }
        // else
        //  printf("%u et %u et %u %s \n", symbol_type, symbol_binding, symtab[j].st_shndx,  symtab_str + symtab[j].st_name);
    }
    if (type == TYPE_A && symbol_type == 4)
    {
        ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, 'a', 0));
    }
    return;
}

void print_final_with_r(char **tri_tab)
{
    t_all *tmp = g_all;
    int i = size_tab(tri_tab) - 1;
    while (i > 0)
    {
        tmp = g_all;
        while (tmp)
        {
            if ((ft_strlen(tri_tab[i]) == ft_strlen(tmp->name)) && ft_strncmp(tri_tab[i], tmp->name, ft_strlen(tri_tab[i])) == 0 && tmp->write != 1)
            {
                if (tmp->address == 0)
                    printf("%16c %c %s\n", ' ', tmp->symbole, tmp->name);
                else
                    printf("%016lx %c %s\n", tmp->address, tmp->symbole, tmp->name);
                tmp->write = 1;
            }
            tmp = tmp->next;
        }
        i--;
    }
    return;
}

void print_final(char **tri_tab, int type)
{
    t_all *tmp = g_all;
    int i = 0;
    while (i < size_tab(tri_tab))
    {
        tmp = g_all;
        while (tmp)
        {
            if (type == TYPE_U)
            {
                if ((ft_strlen(tri_tab[i]) == ft_strlen(tmp->name)) && ft_strncmp(tri_tab[i], tmp->name, ft_strlen(tri_tab[i])) == 0 && tmp->write != 1 && (tmp->symbole == 'U' || tmp->symbole == 'v' || tmp->symbole == 'w'))
                {
                    if (tmp->address == 0)
                        printf("%16c %c %s\n", ' ', tmp->symbole, tmp->name);
                    else
                        printf("%016lx %c %s\n", tmp->address, tmp->symbole, tmp->name);
                    tmp->write = 1;
                }
            }
            else if (type == TYPE_G)
            {
                if ((ft_strlen(tri_tab[i]) == ft_strlen(tmp->name)) && ft_strncmp(tri_tab[i], tmp->name, ft_strlen(tri_tab[i])) == 0 && tmp->write != 1 && (tmp->symbole >= 'A' && tmp->symbole <= 'Z'))
                {
                    if (tmp->address == 0)
                        printf("%16c %c %s\n", ' ', tmp->symbole, tmp->name);
                    else
                        printf("%016lx %c %s\n", tmp->address, tmp->symbole, tmp->name);
                    tmp->write = 1;
                }
            }
            else
            {
                if ((ft_strlen(tri_tab[i]) == ft_strlen(tmp->name)) && ft_strncmp(tri_tab[i], tmp->name, ft_strlen(tri_tab[i])) == 0 && tmp->write != 1)
                {
                    if (tmp->address == 0)
                        printf("%16c %c %s\n", ' ', tmp->symbole, tmp->name);
                    else
                        printf("%016lx %c %s\n", tmp->address, tmp->symbole, tmp->name);
                    tmp->write = 1;
                }
            }
            tmp = tmp->next;
        }
        i++;
    }
    return;
}
