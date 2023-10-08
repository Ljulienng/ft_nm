#include "ft_nm.h"

int type = 0;
t_all *g_all = NULL;

int check_arg(char *binary_path, int bits)
{
    int i = 0;
    FILE *fp = fopen(binary_path, "rb");
    if (!fp)
    {
        return 1;
    }
    Elf64_Ehdr elf_header;

    if (fread(&elf_header, sizeof(elf_header), 1, fp) != 1)
    {
        bits = 1;
    }
    if (elf_header.e_ident[0] != 0x7f ||
        elf_header.e_ident[1] != 'E' ||
        elf_header.e_ident[2] != 'L' ||
        elf_header.e_ident[3] != 'F')
    {
        return (1);
    }
    while (binary_path[i] != '\0')
    {
        i++;
    }
    i--;

    if (ft_strlen(binary_path) > 3 && bits == 1)
    {
        if (binary_path[i] == 'o')
        {
        }
        else
            return 1;
        if ((binary_path[i - 1] == 's' && binary_path[i - 2] == '.') || (binary_path[i - 1] == '.'))
        {
        }
        else
            return 1;
    }
    else
    {
        if (elf_header.e_ident[EI_CLASS] == ELFCLASS32)
            bits = 32;
        else if (elf_header.e_ident[EI_CLASS] == ELFCLASS64)
            bits = 64;
        else
        {
            fclose(fp);
            return 1;
        }
    }
    return 0;
}

void affichage(char **tab)
{
    int i = 0;

    while (tab[i] != NULL)
    {
        if (ft_strlen(tab[i]) > 0)
            printf("%d = %s\n", i, tab[i]);
        i++;
    }
    return;
}

void print_list()
{
    while (g_all->next)
    {
        printf("---------------------\n");
        printf("|g_all->addr = %016lx\n", g_all->address);
        printf("|g_all->name = %s\n", g_all->name);
        printf("|g_all->type = %d\n", g_all->type);
        printf("|g_all->symbole = %c\n", g_all->symbole);
        printf("---------------------\n");
        g_all = g_all->next;
    }
    return;
}

int option(char *str, int argc, int nb_arg)
{
    if (ft_strncmp("-r", str, ft_strlen("-r")) == 0 && ft_strlen(str) == 2)
    {
        type = TYPE_R;
        nb_arg++;
        if (argc == 2)
        {
            printf("ft_nm: 'a.out': No such file\n");
            return (-1);
        }
    }
    else if (ft_strncmp("-a", str, ft_strlen("-a")) == 0 && ft_strlen(str) == 2)
    {
        type = TYPE_A;
        nb_arg++;
        if (argc == 2)
        {
            printf("ft_nm: 'a.out': No such file\n");
            return (-1);
        }
    }
    else if (ft_strncmp("-p", str, ft_strlen("-p")) == 0 && ft_strlen(str) == 2)
    {
        type = TYPE_P;
        nb_arg++;
        if (argc == 2)
        {
            printf("ft_nm: 'a.out': No such file\n");
            return (-1);
        }
    }
    else if (ft_strncmp("-u", str, ft_strlen("-u")) == 0 && ft_strlen(str) == 2)
    {
        type = TYPE_U;
        nb_arg++;
        if (argc == 2)
        {
            printf("ft_nm: 'a.out': No such file\n");
            return (-1);
        }
    }
    else if (ft_strncmp("-g", str, ft_strlen("-g")) == 0 && ft_strlen(str) == 2)
    {
        type = TYPE_G;
        nb_arg++;
        if (argc == 2)
        {
            printf("ft_nm: 'a.out': No such file\n");
            return (-1);
        }
    }
    return nb_arg;
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <binary> ... \n", argv[0]);
        return 1;
    }
    int nb_arg = 1;
    nb_arg = option(argv[1], argc, nb_arg);
    if (nb_arg == -1)
        return 1;

    while (nb_arg < argc)
    {
        char **name_tab = NULL;
        int count = 0;
        if (check_arg(argv[nb_arg], 0) == 1)
        {
            fprintf(stderr, "ft_nm: %s: file format not recognized\n", argv[nb_arg]);
        }
        else
        {
            int fd = open(argv[nb_arg], O_RDONLY);
            if (fd < 0)
            {
                printf("Impossible d'ouvrir le fichier %s\n", argv[nb_arg]);
                return 1;
            }
            void *mapped = mmap(NULL, 100000000000, PROT_READ, MAP_PRIVATE, fd, 0);
            if (mapped == MAP_FAILED)
            {
                printf("Erreur lors du mappage du fichier binaire en mémoire\n");
                close(fd);
                return 1;
            }

            Elf64_Ehdr *ehdr = (Elf64_Ehdr *)mapped;
            Elf64_Shdr *shdr = (Elf64_Shdr *)(mapped + ehdr->e_shoff);
            // Elf64_Shdr *shstrtab = &shdr[ehdr->e_shstrndx];
            // // char *strtab = (char *)(mapped + shstrtab->sh_offset);
            Elf64_Sym *symtab = NULL;
            char *symtab_str = NULL;
            int i, symtab_count;
            if ((argc > 2 && type == 0) || (argc > 3 && type > 0))
            {
                printf("\n");
                printf("%s:\n", argv[nb_arg]);
            }
            for (i = 0; i < ehdr->e_shnum; i++)
            {
                if (shdr[i].sh_type == SHT_SYMTAB)
                {
                    symtab = (Elf64_Sym *)(mapped + shdr[i].sh_offset);
                    symtab_count = shdr[i].sh_size / sizeof(Elf64_Sym);
                    symtab_str = (char *)(mapped + shdr[shdr[i].sh_link].sh_offset);
                    // // char *strtab = (char *)(mapped + shstrtab->sh_offset);
                    for (int j = 0; j < symtab_count; j++)
                    {
                        if (j == 0)
                            name_tab = (char **)malloc(sizeof(char *) * (symtab_count));
                        unsigned char symbol_type_and_binding = symtab[j].st_info;
                        unsigned char symbol_type = symbol_type_and_binding & 0x0F; // les 4 bits de poids faible contiennent le type
                        unsigned char symbol_binding = symbol_type_and_binding >> 4;
                        add_symbol(j, symbol_type, symbol_binding, symtab_str, symtab, type);
                        // ft_lstadd_back(&g_all, fill_all(symtab[j].st_value, symtab_str + symtab[j].st_name, symbol_type, 0));
                        if (type == TYPE_A)
                        {
                            if (ft_strlen(symtab_str + symtab[j].st_name) > 0)
                            {
                                name_tab[count] = symtab_str + symtab[j].st_name;
                                count++;
                            }
                        }
                        else
                        {
                            if (ft_strlen(symtab_str + symtab[j].st_name) > 0 && symbol_type != 4)
                            {
                                name_tab[count] = symtab_str + symtab[j].st_name;
                                count++;
                            }
                        }
                    }

                    break;
                }
            }
            name_tab[count] = NULL;
            tri(name_tab, type);
            free_tab(name_tab);
            munmap(mapped, 100000000000);
            close(fd);
        }
        nb_arg++;
    }
    return 0;
}
