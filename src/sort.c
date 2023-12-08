#include "ft_nm.h"
#include <string.h>

int is_a_special_character(char c)
{
    // Add more special characters as needed
    const char *special_characters = "._@";
    return strchr(special_characters, c) != NULL;
}

int is_smaller(char *a, char *b)
{
    int i = 0, j = 0;

    // Skip leading underscores and compare characters case-insensitively
    while (a[i] == '_')
        i++;
    while (b[j] == '_')
        j++;

    // if (strcmp(a, "free_all") == 0)
    //     printf("a: %s\nb: %s\n", a, b);

    while (a[i] && b[j])
    {
        while (is_a_special_character(a[i]) && a[i])
            i++;
        while (is_a_special_character(b[j]) && b[j])
            j++;

        int char_a = tolower((int)a[i]);
        int char_b = tolower((int)b[j]);

        if (char_a != char_b)
        {
            // if (strcmp(a, "free_all") == 0)
            //     printf("char_a: %c\nchar_b: %c\n", char_a, char_b);
            // if (strcmp(a, "_ZN11__sanitizer18ReportErrorSummaryEPKcRKNS_11AddressInfoES1_.part.0") == 0)
            //     printf("a: %s\nb: %s\n, char_a %c, char_b %c, i %d, j%d\n", a, b, a[i], b[j], i, j);
            // if (b[j] == '\0' || a[i] == '\0')
            //     printf("char_b is null\n");
            return char_a < char_b;
        }

        if (a[i] != '\0')
            i++;
        if (b[j] != '\0')
            j++;
    }

    if (a[i] == '\0' && b[j] == '\0')
        return ft_strlen(a) > ft_strlen(b);
    // printf("DIAJDIEADJI = a: %s\nb: %s\n", a, b);

    // Handle cases where one string is a prefix of the other
    if (a[i] == '\0' && b[j] == '\0')
        return 0;

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
            // if (strcmp(arr[j], "free@GLIBC_2.2.5") == 0)
            //     printf("arr[j]: %s\npivot: %s\n", arr[j], pivot);

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
