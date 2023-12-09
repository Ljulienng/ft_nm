#include "ft_nm.h"

int process_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, char *mapped, int type, char ***name_tab, int *count)
{
	Elf64_Sym *symtab = NULL;
	int symtab_count = 0;
	char *symtab_str = NULL;

	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB)
		{
			symtab = (Elf64_Sym *)(mapped + shdr[i].sh_offset);
			if (!symtab)
			{
				fprintf(stderr, "Invalid symtab pointer\n");
				break;
			}

			symtab_str = (char *)(mapped + shdr[shdr[i].sh_link].sh_offset);
			if (!symtab_str)
			{
				fprintf(stderr, "Invalid symtab_str pointer\n");
				break;
			}
			symtab_count = shdr[i].sh_size / sizeof(Elf64_Sym);
			// // char *strtab = (char *)(mapped + shstrtab->sh_offset);
			*name_tab = (char **)malloc(sizeof(char *) * (symtab_count));
			if (*name_tab == NULL)
				return 1;
			for (int j = 0; j < symtab_count; j++)
			{
				unsigned char symbol_type_and_binding = symtab[j].st_info;
				unsigned char symbol_type = symbol_type_and_binding & 0x0F; // les 4 bits de poids faible contiennent le type
				unsigned char symbol_binding = symbol_type_and_binding >> 4;
				add_symbol(j, symbol_binding, symtab_str, symtab, shdr);
				if ((type == TYPE_A && ft_strlen(symtab_str + symtab[j].st_name) > 0) ||
					(type != TYPE_A && ft_strlen(symtab_str + symtab[j].st_name) > 0 && symbol_type != 4))
				{
					(*name_tab)[(*count)++] = symtab_str + symtab[j].st_name;
				}
			}

			break;
		}
	}
	return 0;
}

int process_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, char *mapped, int type, char ***name_tab, int *count)
{
	Elf32_Sym *symtab = NULL;
	int symtab_count = 0;
	char *symtab_str = NULL;

	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB)
		{
			symtab = (Elf32_Sym *)(mapped + shdr[i].sh_offset);
			if (!symtab)
			{
				fprintf(stderr, "Invalid symtab pointer\n");
				break;
			}

			symtab_str = (char *)(mapped + shdr[shdr[i].sh_link].sh_offset);
			if (!symtab_str)
			{
				fprintf(stderr, "Invalid symtab_str pointer\n");
				break;
			}

			symtab_count = shdr[i].sh_size / sizeof(Elf32_Sym);
			*name_tab = (char **)malloc(sizeof(char *) * symtab_count);
			if (*name_tab == NULL)
				return 1;

			for (int j = 0; j < symtab_count; j++)
			{
				unsigned char symbol_type_and_binding = symtab[j].st_info;
				unsigned char symbol_type = symbol_type_and_binding & 0x0F;
				unsigned char symbol_binding = symbol_type_and_binding >> 4;
				// Call a modified add_symbol function suitable for 32-bit
				add_symbol_32(j, symbol_binding, symtab_str, symtab, shdr);
				if ((type == TYPE_A && ft_strlen(symtab_str + symtab[j].st_name) > 0) ||
					(type != TYPE_A && ft_strlen(symtab_str + symtab[j].st_name) > 0 && symbol_type != 4))
				{
					(*name_tab)[(*count)++] = symtab_str + symtab[j].st_name;
				}
			}

			break;
		}
	}
	return 0;
}