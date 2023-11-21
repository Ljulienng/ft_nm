#include "ft_nm.h"
#include <string.h>

char *all_in_min(char *str)
{
    int i = 0;
    // int lengh = ft_strlen(str);
    char *tab = malloc(ft_strlen(str) + 1);

    while (str[i])
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            tab[i] = str[i] + 32;
        else
            tab[i] = str[i];
        i++;
    }
    tab[i] = '\0';
    return tab;
}

static int free_var(char *str_min, char *tmp_min, int return_value)
{
    free(str_min);
    free(tmp_min);
    return return_value;
}

int is_smaller(char *tmp, char *tab_str)
{
    char *str_min = all_in_min(tab_str);
    char *tmp_min = all_in_min(tmp);
    int i = 0;
    int j = 0;

    while (tmp_min[i] == '_')
        i++;
    while (str_min[j] == '_')
        j++;

    while (tmp_min[i] && str_min[j])
    {
        if (tmp_min[i] == '_' && str_min[j] != '_' && i == j)
            return free_var(str_min, tmp_min, 1);
        if (tmp_min[i] != '_' && str_min[j] == '_' && i == j)
            return free_var(str_min, tmp_min, 0);
        if (tmp_min[i] < str_min[j])
            return free_var(str_min, tmp_min, 0);
        if (tmp_min[i] > str_min[j])
            return free_var(str_min, tmp_min, 1);
        j++;
        i++;
    }
    if (ft_strlen_without_tiret(tmp_min) == ft_strlen_without_tiret(str_min))
    {
        if (tmp_min[0] == '_' && str_min[0] != '_')
            return free_var(str_min, tmp_min, 0);
        if (tmp_min[0] != '_' && str_min[0] == '_')
            return free_var(str_min, tmp_min, 1);
    }
    if (ft_strlen(str_min) < ft_strlen(tmp_min))
        return free_var(str_min, tmp_min, 1);
    return free_var(str_min, tmp_min, 0);
}
// QuickSort utility functions
int partition(char *arr[], int low, int high)
{
    char *pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        // Use is_smaller instead of strcmp
        if (is_smaller(pivot, arr[j]))
        {
            i++;
            char *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    char *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(char *arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Improved tri function using QuickSort
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