#include "ft_nm.h"

int type = 0;
t_all *g_all = NULL;

int check_arg(char *binary_path, int *bits)
{
    FILE *fp = fopen(binary_path, "rb");
    if (!fp)
    {
        perror("Error opening file");
        return 1;
    }

    Elf64_Ehdr elf_header;
    if (fread(&elf_header, sizeof(elf_header), 1, fp) != 1)
    {
        perror("Error reading file");
        fclose(fp);
        return 1;
    }

    // Checking ELF magic numbers
    if (memcmp(elf_header.e_ident, ELFMAG, (size_t)SELFMAG) != 0)
    {
        fclose(fp);
        return 1;
    }

    // Determine the architecture
    if (elf_header.e_ident[EI_CLASS] == ELFCLASS32)
        *bits = 32;
    else if (elf_header.e_ident[EI_CLASS] == ELFCLASS64)
        *bits = 64;
    else
    {
        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
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
    int bits = 0;
    nb_arg = option(argv[1], argc, nb_arg);
    if (nb_arg == -1)
        return 1;

    while (nb_arg < argc)
    {
        char **name_tab = NULL;
        int count = 0;
        if (check_arg(argv[nb_arg], &bits) == 1)
        {
            fprintf(stderr, "ft_nm: %s: file format not recognized\n", argv[nb_arg]);
        }
        else
        {
            int fd = open(argv[nb_arg], O_RDONLY);
            if (fd < 0)
                exit_error("open failed\n", 1);
            struct stat statbuf;
            if (fstat(fd, &statbuf) < 0)
            {
                close(fd);
                perror("fstat failed");
                return 1;
            }

            void *mapped = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
            if (mapped == MAP_FAILED)
            {
                close(fd);
                exit_error("mmap failed\n", 1);
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
                    name_tab = (char **)malloc(sizeof(char *) * (symtab_count));
                    if (name_tab == NULL)
                    {
                        perror("Failed to allocate memory for name_tab");
                        munmap(mapped, statbuf.st_size);
                        close(fd);
                        return 1;
                    }
                    for (int j = 0; j < symtab_count; j++)
                    {
                        unsigned char symbol_type_and_binding = symtab[j].st_info;
                        unsigned char symbol_type = symbol_type_and_binding & 0x0F; // les 4 bits de poids faible contiennent le type
                        unsigned char symbol_binding = symbol_type_and_binding >> 4;
                        add_symbol(j, symbol_binding, symtab_str, symtab, shdr);
                        if ((type == TYPE_A && ft_strlen(symtab_str + symtab[j].st_name) > 0) ||
                            (type != TYPE_A && ft_strlen(symtab_str + symtab[j].st_name) > 0 && symbol_type != 4))
                        {
                            name_tab[count++] = symtab_str + symtab[j].st_name;
                        }
                    }

                    break;
                }
            }
            if (count > 0)
                name_tab[count] = NULL;
            else
                name_tab = NULL;
            if (name_tab != NULL)
                tri(name_tab, type);
            else
                printf("ft_nm: %s: no symbols\n", argv[nb_arg]);
            // printf("size tab : %d\n", size_tab(name_tab));
            free_tab(name_tab);
            munmap(mapped, statbuf.st_size);
            close(fd);
        }
        nb_arg++;
    }
    return 0;
}
