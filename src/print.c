#include "ft_nm.h"

#include <elf.h>
void add_symbol(int j, unsigned char symbol_binding, char *symtab_str, Elf64_Sym *symtab, Elf64_Shdr *shdr)
{
    if (ft_strlen(symtab_str + symtab[j].st_name) > 0)
    {
        char symbol_char = '?'; // Default: unknown symbol

        if (symtab[j].st_shndx == SHN_UNDEF)
        {
            symbol_char = 'U'; // Undefined symbol
        }
        else if (symtab[j].st_shndx == SHN_ABS)
        {
            symbol_char = 'A'; // Absolute symbol
        }
        else if (symtab[j].st_shndx == SHN_COMMON)
        {
            symbol_char = 'C'; // Common symbol
        }
        else
        {
            Elf64_Shdr section = shdr[symtab[j].st_shndx];
            if (section.sh_type == SHT_NOBITS)
            {
                // Uninitialized data (bss segment)
                symbol_char = 'B';
            }
            else if (section.sh_flags & SHF_WRITE)
            {
                // Initialized data segment
                symbol_char = 'D';
            }
            else if (section.sh_flags & SHF_EXECINSTR)
            {
                // Executable (text) segment
                symbol_char = 'T';
            }
            else
            {
                // Read-only data segment
                symbol_char = 'R';
            }
        }

        // Handle local symbols
        if (symbol_binding == STB_LOCAL && symbol_char != '?')
        {
            symbol_char = tolower(symbol_char);
        }

        // Handle weak symbols
        if (symbol_binding == STB_WEAK)
        {
            symbol_char = (symtab[j].st_shndx == SHN_UNDEF) ? 'w' : 'W';
        }

        // Add symbol to the list
        ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, symbol_char, 0));
    }
}

void print_symbol(t_all *symbol)
{
    if (symbol->address == 0 && symbol->symbole == 'U')
        printf("                 %c %s\n", symbol->symbole, symbol->name);
    else
        printf("%016lx %c %s\n", symbol->address, symbol->symbole, symbol->name);
}

// Add helper functions for readability and to reduce code duplication
int is_correct_symbol(t_all *symbol, char *name)
{
    return (ft_strlen(name) == ft_strlen(symbol->name)) &&
           ft_strncmp(name, symbol->name, ft_strlen(name)) == 0 &&
           symbol->write != 1;
}

int is_correct_type(t_all *symbol, int type, char *name)
{
    if (type == TYPE_U)
        return is_correct_symbol(symbol, name) && (symbol->symbole == 'U' || symbol->symbole == 'v' || symbol->symbole == 'w');
    if (type == TYPE_G)
        return is_correct_symbol(symbol, name) && (symbol->symbole >= 'A' && symbol->symbole <= 'Z');
    return is_correct_symbol(symbol, name);
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
            if (is_correct_symbol(tmp, tri_tab[i]))
            {
                print_symbol(tmp);
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
            if (is_correct_type(tmp, type, tri_tab[i]))
            {
                print_symbol(tmp);
                tmp->write = 1;
            }
            tmp = tmp->next;
        }
        i++;
    }
    return;
}
