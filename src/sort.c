#include "ft_nm.h"
#include <string.h>

// char *all_in_min(char *str)
// {
//     int i = 0;
//     // int lengh = ft_strlen(str);
//     char *tab = malloc(ft_strlen(str) + 1);

//     while (str[i])
//     {
//         if (str[i] >= 'A' && str[i] <= 'Z')
//             tab[i] = str[i] + 32;
//         else
//             tab[i] = str[i];
//         i++;
//     }
//     tab[i] = '\0';
//     return tab;
// }

// static int free_var(char *str_min, char *tmp_min, int return_value)
// {
//     free(str_min);
//     free(tmp_min);
//     return return_value;
// }

// int is_smaller(char *tmp, char *tab_str)
// {
//     char *str_min = all_in_min(tab_str);
//     char *tmp_min = all_in_min(tmp);
//     int i = 0;
//     int j = 0;

//     while (tmp_min[i] == '_')
//         i++;
//     while (str_min[j] == '_')
//         j++;

//     while (tmp_min[i] && str_min[j])
//     {
//         if (tmp_min[i] == '_' && str_min[j] != '_' && i == j)
//             return free_var(str_min, tmp_min, 1);
//         if (tmp_min[i] != '_' && str_min[j] == '_' && i == j)
//             return free_var(str_min, tmp_min, 0);
//         if (tmp_min[i] < str_min[j])
//             return free_var(str_min, tmp_min, 0);
//         if (tmp_min[i] > str_min[j])
//             return free_var(str_min, tmp_min, 1);
//         j++;
//         i++;
//     }
//     if (ft_strlen_without_tiret(tmp_min) == ft_strlen_without_tiret(str_min))
//     {
//         if (tmp_min[0] == '_' && str_min[0] != '_')
//             return free_var(str_min, tmp_min, 0);
//         if (tmp_min[0] != '_' && str_min[0] == '_')
//             return free_var(str_min, tmp_min, 1);
//     }
//     if (ft_strlen(str_min) < ft_strlen(tmp_min))
//         return free_var(str_min, tmp_min, 1);
//     return free_var(str_min, tmp_min, 0);
// }

int is_smaller(char *a, char *b)
{
    int i = 0, j = 0;

    // Skip leading underscores and compare characters case-insensitively
    while (a[i] == '_')
        i++;
    while (b[j] == '_')
        j++;

    // if (strcmp(a, "strdup") == 0)
    //     printf("a: %s\nb: %s\n", a, b);

    while (a[i] && b[j])
    {

        while (a[i] == '_')
            i++;
        while (b[j] == '_')
            j++;
        int char_a = tolower((unsigned char)a[i]);
        int char_b = tolower((unsigned char)b[j]);

        if (char_a != char_b)
        {
            return char_a < char_b;
        }

        if (a[i] != '\0')
            i++;
        if (b[j] != '\0')
            j++;
    }

    // Handle cases where one string is a prefix of the other
    return a[i] == '\0' && b[j] != '\0';
}
// QuickSort utility functions
void quickSort(char *arr[], int low, int high)
{
    if (low >= high)
        return;

    char *pivot = arr[high];
    int i = low;

    for (int j = low; j < high; j++)
    {
        if (is_smaller(arr[j], pivot))
        {
            char *temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
            i++;
        }
    }

    char *temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;

    quickSort(arr, low, i - 1);
    quickSort(arr, i + 1, high);
}

void tri(char **name_tab, int type)
{
    int n = size_tab(name_tab); // Calculate size once

    if (type == TYPE_P)
    {
        print_final(name_tab, type);
        return;
    }

    quickSort(name_tab, 0, n - 1); // Apply QuickSort

    if (type == TYPE_R)
    {
        print_final_with_r(name_tab); // Print in reverse order if needed
    }
    else
    {
        print_final(name_tab, type);
    }
}