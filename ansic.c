#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    const char *name;
    int code;
    const char *desc;
} ColorEntry;

ColorEntry color_map[] = {
    {"black", 30},
    {"red", 31},
    {"green", 32},
    {"yellow", 33},
    {"blue", 34},
    {"magenta", 35},
    {"cyan", 36},
    {"white", 37},

    {"brightblack", 90},
    {"brightred", 91},
    {"brightgreen", 92},
    {"brightyellow", 93},
    {"brightblue", 94},
    {"brightmagenta", 95},
    {"brightcyan", 96},
    {"brightwhite", 97},

    {"bgblack", 40},
    {"bgred", 41},
    {"bggreen", 42},
    {"bgyellow", 43},
    {"bgblue", 44},
    {"bgmagenta", 45},
    {"bgcyan", 46},
    {"bgwhite", 47},

    {"bgbrightblack", 100},
    {"bgbrightred", 101},
    {"bgbrightgreen", 102},
    {"bgbrightyellow", 103},
    {"bgbrightblue", 104},
    {"bgbrightmagenta", 105},
    {"bgbrightcyan", 106},
    {"bgbrightwhite", 107},

    {"bold", 1},
    {"underline", 4},
    {"italic", 3},
    {NULL, 0}};

void normalize(char *str)
{
    char *p = str, *q = str;
    while (*p)
    {
        if (!isspace(*p))
        {
            *q++ = tolower(*p);
        }
        p++;
    }
    *q = '\0';
}

int find_codes(const char *input, int *codes, int max_codes)
{
    char buf[256];
    strncpy(buf, input, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    normalize(buf);

    int count = 0;
    char *token = strtok(buf, "; ,");
    while (token && count < max_codes)
    {
        int matched = 0;
        for (int i = 0; color_map[i].name; i++)
        {
            if (strcmp(token, color_map[i].name) == 0)
            {
                codes[count++] = color_map[i].code;
                matched = 1;
                break;
            }
        }

        if (!matched && isdigit(token[0]))
        {
            int num = atoi(token);
            if (num >= 0 && num <= 255)
            {
                codes[count++] = num;
                matched = 1;
            }
        }

        token = strtok(NULL, "; ,");
    }

    return count;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("\033[32m Usage: %s <color description>\n\n \033[0m", argv[0]);
        printf("\033[32m Examples:\n \033[0m");
        printf("\033[32m %s red            → \\033[31m\n \033[0m", argv[0]);
        printf("\033[32m %s green          → \\033[32m\n \033[0m", argv[0]);
        printf("\033[32m %s brightgreen    → \\033[92m\n \033[0m", argv[0]);
        printf("\033[32m %s 32             → \\033[32m\n \033[0m", argv[0]);
        printf("\033[32m %s bgblue         → \\033[44m\n \033[0m", argv[0]);
        return 1;
    }

    char input[512] = "";
    for (int i = 1; i < argc; i++)
    {
        strncat(input, argv[i], sizeof(input) - strlen(input) - 1);
        if (i < argc - 1)
            strncat(input, " ", sizeof(input) - strlen(input) - 1);
    }

    int codes[16];
    int n = find_codes(input, codes, 16);

    if (n == 0)
    {
        printf("Unrecognized color description: %s\n", input);
        return 1;
    }

    printf("\\033[");
    for (int i = 0; i < n; i++)
    {
        if (i > 0)
            printf(";");
        printf("%d", codes[i]);
    }
    printf("m\n");

    return 0;
}