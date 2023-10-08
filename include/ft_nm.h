#ifndef FT_NM_H
#define FT_NM_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>

#define TYPE_R 1
#define TYPE_A 2
#define TYPE_G 3
#define TYPE_U 4
#define TYPE_P 5

typedef struct s_all
{
    int write;
    int type;
    char *name;
    char symbole;
    uint64_t address;
    struct s_all *next;
} t_all;

void add_symbol(int j, unsigned char symbol_type, unsigned char symbol_binding, char *symtab_str, Elf64_Sym *symtab, int type);
void print_final_with_r(char **tri_tab);
void print_final(char **tri_tab, int type);
char *all_in_min(char *str);
int is_smaller(char *tmp, char *tab_str);
void tri(char **name_tab, int type);
void free_tab(char **tab);
void free_all();
int size_tab(char **name_tab);

t_all *fill_all(uint64_t address, char *name, char symbole, int type);
int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_strlen(char *s);
void ft_lstadd_back(t_all **alst, t_all *new);
int ft_strlen_without_tiret(char *s);

extern t_all *g_all;
#endif