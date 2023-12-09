#include "ft_nm.h"

#include "ft_nm.h"
#include <elf.h>
#include <ctype.h> // for tolower function

void add_symbol_32(int j, unsigned char symbol_binding, char *symtab_str, Elf32_Sym *symtab, Elf32_Shdr *shdr)
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
			Elf32_Shdr section = shdr[symtab[j].st_shndx];
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
			if (ELF32_ST_TYPE(symtab[j].st_info) == STT_OBJECT)
			{
				symbol_char = 'v'; // Weak object symbol
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

void print_symbol_32(t_all *symbol)
{
	if (symbol->address == 0 && (symbol->symbole == 'w' || symbol->symbole == 'W' || symbol->symbole == 'v'))
		printf("%8c %c %s\n", ' ', symbol->symbole, symbol->name); // Print without address (32-bit format)
	else if (symbol->address == 0 && symbol->symbole == 'U')
		printf("         %c %s\n", symbol->symbole, symbol->name); // Undefined symbol without address (32-bit format)
	else
		printf("%08lx %c %s\n", symbol->address, symbol->symbole, symbol->name); // Print with address (32-bit format)
}
