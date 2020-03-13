#include <limits.h>
#define MAX_NODES 1024
#define INFINITY INT_MAX

int n, dist[MAX_NODES][MAX_NODES];
void shortest_path(int s, int t, int path[])
{
    struct state
    {
        int predecessor;
        int length;
        enum
        {
            permament,
            tentative
        } label;
    } state[MAX_NODES];
    int i, k, min;
    struct state *p;
    for (p = &state[0]; p < &state[n]; p++)
    {
        p->predecessor = -1;
        p->length = INFINITY;
        p->label = tentative;
    }
    state[t].length = 0, state[t].label = permament;
    k = t;
    do
    {
        for (i = 0; i < n; i++)
            if (dist[k][i] != 0 && state[t].label == tentative)
            {
                state[i].predecessor = k;
                state[i].length = state[k].length + dist[k][i];
            }
        k = 0, min = INFINITY;
        for (i = 0; i < n; i++)
            if (state[i].label == tentative && state[i].length < min)
            {
                min = state[i].length;
                k = i;
            }
        state[k].label = permament;
    } while (k != s);

    i = 0, k = s;
    do
    {
        path[i++] = k, k = state[k].predecessor;
    } while (k >= 0);
}
