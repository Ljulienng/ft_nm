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
                symbol_char = 'B'; // Uninitialized data (bss segment)
            }
            else if (section.sh_flags & SHF_WRITE)
            {
                symbol_char = 'D'; // Initialized data segment
            }
            else if (section.sh_flags & SHF_EXECINSTR)
            {
                symbol_char = 'T'; // Executable (text) segment
            }
            else
            {
                symbol_char = 'R'; // Read-only data segment
            }
        }

        // Handle weak symbols
        if (symbol_binding == STB_WEAK)
        {
            if (ELF64_ST_TYPE(symtab[j].st_info) == STT_OBJECT)
            {
                if (symtab[j].st_shndx == SHN_UNDEF)
                {
                    symbol_char = 'v'; // Weak object symbol, undefined
                }
                else
                {
                    symbol_char = 'V'; // Weak object symbol, defined
                }
            }
            else if (symtab[j].st_shndx == SHN_UNDEF)
            {
                symbol_char = 'w'; // Weak symbol, undefined
            }
            else
            {
                symbol_char = 'W'; // Weak symbol, defined
            }
        }

        // Handle local symbols
        if (symbol_binding == STB_LOCAL && symbol_char != '?')
        {
            symbol_char = tolower(symbol_char);
        }

        // Add symbol to the list
        ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, symbol_char, 0));
    }
}

void print_symbol(t_all *symbol)
{
    // Check if the symbol is a weak symbol with a zero address
    if (symbol->address == 0 && (symbol->symbole == 'w' || symbol->symbole == 'W' || symbol->symbole == 'v'))
        printf("%16c %c %s\n", ' ', symbol->symbole, symbol->name); // Print without address
    else if (symbol->address == 0 && symbol->symbole == 'U')
        printf("                 %c %s\n", symbol->symbole, symbol->name); // Undefined symbol without address
    else
        printf("%016lx %c %s\n", symbol->address, symbol->symbole, symbol->name); // Print with address
}

// Add helper functions for readability and to reduce code duplication
int is_correct_symbol(t_all *symbol, char *name)
{
    // First, ensure that both 'name' and 'symbol->name' are not NULL
    if (symbol == NULL || symbol->name == NULL || name == NULL)
    {
        return 0; // Handle error or return false
    }
    // Check if the lengths of 'name' and 'symbol->name' are equal
    size_t name_len = ft_strlen(name);
    if (name_len != (size_t)ft_strlen(symbol->name))
    {
        return 0; // Return false if lengths are not equal
    }

    // Compare the names
    if (ft_strncmp(name, symbol->name, name_len) != 0)
    {
        return 0; // Return false if names are not equal
    }

    // Check if the symbol has already been written
    if (symbol->write != 1)
    {
        return 1; // Return true if symbol hasn't been written yet
    }

    // If none of the conditions match, return false
    return 0;
}
int is_correct_type(t_all *symbol, int type, char *name)
{
    if (type == TYPE_U)
        return is_correct_symbol(symbol, name) && (symbol->symbole == 'U' || symbol->symbole == 'v' || symbol->symbole == 'w');
    if (type == TYPE_G)
        return is_correct_symbol(symbol, name) && (symbol->symbole >= 'A' && symbol->symbole <= 'Z');
    return is_correct_symbol(symbol, name);
}

void print_final_with_r(char **tri_tab, int bits)
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
                if (bits == 32)
                    print_symbol_32(tmp);
                else
                    print_symbol(tmp);
                tmp->write = 1;
            }
            tmp = tmp->next;
        }
        i--;
    }
    return;
}

void print_final(char **tri_tab, int type, int bits)
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
                if (bits == 32)
                    print_symbol_32(tmp);
                else
                    print_symbol(tmp);
                tmp->write = 1;
            }
            tmp = tmp->next;
        }
        i++;
    }
    return;
}
