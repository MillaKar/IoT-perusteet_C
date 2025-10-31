#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 10

void clear_history(char *history[], int *count)
{
    for (int i = 0; i < *count; i++)
    {
        free(history[i]);
        history[i] = NULL;
    }
    *count = 0;
}

void print_history(char *history[], int count)
{
    if (count == 0)
    {
        printf("Komentohistoria on tyhjä.\n");
        return;
    }
    printf("Komentohistoria:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

void add_to_history(char *history[], int *count, const char *line)
{
    if (*count == MAX_HISTORY)
    {
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY; i++)
            history[i - 1] = history[i];
        (*count)--;
    }
    history[*count] = malloc(strlen(line) + 1);
    if (history[*count])
        strcpy(history[*count], line);
    (*count)++;
}

int main(void)
{
    char line[100];
    int a, b;
    char op;
    char *history[MAX_HISTORY] = {0};
    int history_count = 0;

    printf("# Ohjelman suoritus alkaa\n");

    while (1)
    {
        printf("> ");
        if (fgets(line, sizeof(line), stdin) == NULL)
            continue;

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        if (strlen(line) == 0)
        {
            printf("Virheellinen syöte (tyhjä) – kirjoita \"x\" lopettaaksesi ohjelman\n");
            continue;
        }

        if (strcmp(line, "x") == 0 || strcmp(line, "X") == 0)
            break;

        if (strcmp(line, "h") == 0)
        {
            print_history(history, history_count);
            continue;
        }

        if (strcmp(line, "c") == 0)
        {
            clear_history(history, &history_count);
            continue;
        }

        if (line[0] == '!' && strlen(line) > 1)
        {
            int index = atoi(line + 1);
            if (index > 0 && index <= history_count)
            {
                printf("%s = ", history[index - 1]);
                sscanf(history[index - 1], "%d %c %d", &a, &op, &b);
            }
            else
            {
                continue;
            }
        }
        else
        {
            int parsed = sscanf(line, "%d %c %d", &a, &op, &b);
            if (parsed != 3)
            {
                printf("Virheellinen syöte (puuttuvia argumentteja)\n");
                continue;
            }
            add_to_history(history, &history_count, line);
        }

        switch (op)
        {
        case '+':
            printf("%d\n", a + b);
            break;
        case '-':
            printf("%d\n", a - b);
            break;
        case '*':
            printf("%d\n", a * b);
            break;
        case '/':
            if (b == 0)
                printf("Virhe: nollalla ei voi jakaa\n");
            else
                printf("%d\n", a / b);
            break;
        case '%':
            if (b == 0)
                printf("Virhe: nollalla ei voi jakaa\n");
            else
                printf("%d\n", a % b);
            break;
        default:
            printf("Virheellinen laskuoperaatio\n");
        }
    }

    clear_history(history, &history_count);
    printf("# Ohjelman suoritus päättyy\n");
    return 0;
}
