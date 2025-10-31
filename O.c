#include <stdio.h>
#include <string.h>

int main(void)
{
    char line[100];
    int a, b;
    char op;

    printf("# Ohjelman suoritus alkaa\n");

    while (1)
    {
        printf("> ");
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("Virhe: syötteen lukeminen epäonnistui.\n");
            continue;
        }

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

        int parsed = sscanf(line, "%d %c %d", &a, &op, &b);
        if (parsed != 3)
        {
            printf("Virheellinen syöte (puuttuvia argumentteja)\n");
            continue;
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
            printf("Virheellinen laskuoperaatio: käytä +, -, *, / tai %%\n");
        }
    }

    printf("# Ohjelman suoritus päättyy\n");
    return 0;
}
