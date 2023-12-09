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
    // Handle the -r flag (Reverse Sort)
    if (ft_strncmp("-r", str, ft_strlen("-r")) == 0 && ft_strlen(str) == 2)
    {
        type = TYPE_R; // Set mode to reverse sort
        nb_arg++;
        // Check if -r is the only argument
        if (argc == 2)
        {
            printf("ft_nm: 'a.out': No such file\n");
            return (-1); // Error if no file specified
        }
    }
    // Handle the -a flag
    else if (ft_strncmp("-a", str, ft_strlen("-a")) == 0 && ft_strlen(str) == 2)
    {
        type = TYPE_A; // Set mode specific to -a (functionality not specified)
        nb_arg++;
        // Check if -a is the only argument
        if (argc == 2)
        {
            printf("ft_nm: 'a.out': No such file\n");
            return (-1); // Error if no file specified
        }
    }
    // Handle the -p flag (No Sort)
    else if (ft_strncmp("-p", str, ft_strlen("-p")) == 0 && ft_strlen(str) == 2)
    {
        type = TYPE_P; // Set mode to no sorting
        nb_arg++;
        // Check if -p is the only argument
        if (argc == 2)
        {
            printf("ft_nm: 'a.out': No such file\n");
            return (-1); // Error if no file specified
        }
    }
    // Handle the -u flag (Undefined Symbols)
    else if (ft_strncmp("-u", str, ft_strlen("-u")) == 0 && ft_strlen(str) == 2)
    {
        type = TYPE_U; // Set mode to display undefined symbols
        nb_arg++;
        // Check if -u is the only argument
        if (argc == 2)
        {
            printf("ft_nm: 'a.out': No such file\n");
            return (-1); // Error if no file specified
        }
    }
    // Handle the -g flag (Global Symbols)
    else if (ft_strncmp("-g", str, ft_strlen("-g")) == 0 && ft_strlen(str) == 2)
    {
        type = TYPE_G; // Set mode to display global symbols
        nb_arg++;
        // Check if -g is the only argument
        if (argc == 2)
        {
            printf("ft_nm: 'a.out': No such file\n");
            return (-1); // Error if no file specified
        }
    }
    return nb_arg; // Return the number of arguments processed
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
            struct stat statbuf;
            if (fd < 0)
                exit_error("open failed\n", 1);
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

            // Handle 64-bit ELF file

            if ((argc > 2 && type == 0) || (argc > 3 && type > 0))
            {
                printf("\n");
                printf("%s:\n", argv[nb_arg]);
            }
            if (bits == 64)
            {
                Elf64_Ehdr *ehdr = (Elf64_Ehdr *)mapped;
                Elf64_Shdr *shdr = (Elf64_Shdr *)(mapped + ehdr->e_shoff);
                if (process_64(ehdr, shdr, mapped, type, &name_tab, &count) == 1)
                {
                    perror("Failed to allocate memory for name_tab");
                    munmap(mapped, statbuf.st_size);
                    close(fd);
                    return 1;
                }
            }
            else
            {
                Elf32_Ehdr *ehdr = (Elf32_Ehdr *)mapped;
                Elf32_Shdr *shdr = (Elf32_Shdr *)(mapped + ehdr->e_shoff);
                if (process_32(ehdr, shdr, mapped, type, &name_tab, &count) == 1)
                {
                    perror("Failed to allocate memory for name_tab");
                    munmap(mapped, statbuf.st_size);
                    close(fd);
                    return 1;
                }
            }

            if (count > 0)
                name_tab[count] = NULL;
            else
                name_tab = NULL;
            if (name_tab != NULL)
                tri(name_tab, type, bits);
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
