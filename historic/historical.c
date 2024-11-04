#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historical.h"

typedef struct
{
    char win[30];
    char lose[30];
} score;

typedef struct
{
    int line;
    score tab[50];
} log;

typedef struct
{
    char name[30];
    int point;
} play;

typedef struct
{
    play tab[50];
    int nombre;
} leader;

log get_log()
{
    FILE *f;
    log l;
    if (!(f = fopen("historical.txt", "r")))
    {
        l.line = -1;
        return l;
    }

    // gets the number of lines from the file
    int line;
    fscanf(f, "%d\n", &line);
    l.line = line;

    score g;
    for (int i = 0; i < line; i++)
    {
        fscanf(f, "W %s L %s\n", g.win, g.lose);
        l.tab[i] = g;
    }
    fclose(f);
    return l;
}

void set_log(log l)
{
    FILE *f = fopen("historical.txt", "w");
    fprintf(f, "%d\n", l.line);
    for (int i = 0; i < l.line; i++)
    {
        fprintf(f, "W %s L %s\n", l.tab[i].win, l.tab[i].lose);
    }
    fclose(f);
}

log add_log(log l, char win[30], char lose[30])
{
    score g;
    strcpy(g.win, win);
    strcpy(g.lose, lose);
    l.tab[l.line] = g;
    l.line++;
    return l;
}

void add_score(char win[30], char lose[30])
{
    log l = get_log();
    l = add_log(l, win, lose);
    set_log(l);
}

leader existing_player(leader b, int ind, int nb)
{
    b.tab[ind].point += nb;
    return b;
}

leader new_player(leader b, char *name, int nb)
{
    strcpy(b.tab[b.nombre].name, name);
    b.tab[b.nombre].point = nb;
    b.nombre++;
    return b;
}

leader add_point(leader b, char *name, int nb)
{
    for (int i = 0; i < b.nombre; i++)
    {
        if (strcmp(b.tab[i].name, name) == 0)
        {
            b = existing_player(b, i, nb);
            return b;
        }
    }
    b = new_player(b, name, nb);
    return b;
}

leader exchange_lines(leader b, int l1, int l2)
{
    play inter = b.tab[l1];
    b.tab[l1] = b.tab[l2];
    b.tab[l2] = inter;
    return b;
}

leader sort_leader(leader b)
{
    int max;
    int i;
    int j;

    for (i = 0; i < b.nombre - 1; i++)
    {
        max = i;
        for (j = i + 1; j < b.nombre; j++)
            if (b.tab[j].point > b.tab[max].point)
                max = j;
        b = exchange_lines(b, i, max);
    }

    return b;
}

leader get_leader(log l)
{
    leader b;
    b.nombre = 0;
    for (int i = 0; i < l.line; i++)
    {
        b = add_point(b, l.tab[i].win, 10);
        b = add_point(b, l.tab[i].lose, -8);
    }
    b = sort_leader(b);
    return b;
}

void display_leader(leader b)
{
    for (int i = 0; i < b.nombre; i++)
    {
        printf("%d - %s : %d points\n", i + 1, b.tab[i].name, b.tab[i].point);
    }
}

void everything_to_display_leader()
{
    log l = get_log();
    if (l.line == -1)
    {
        printf("It has no scores yet.\n");
        return;
    }
    leader b = get_leader(l);
    display_leader(b);
}
