void bubblesort(int v[], int n)
{
    int i, j;
    void swap(int v[], int i, int j);
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (v[j] > v[j + 1])
                swap(v, j, j + 1);
}

void selectionsort(int v[], int n)
{
    int i, j, imin;
    for (i = 0; i < n - 1; i++)
    {
        imin = i;
        for (j = i + 1; j < n; j++)
            if (v[j] < v[imin])
                imin = j;
        swap(v, i, imin);
    }
}

void insertsort(int v[], int n)
{
    int i, j, val;
    for (i = 1; i < n; i++)
    {
        val = v[i];
        for (j = i - 1; j >= 0 && v[j] > val; j--)
            v[j + 1] = v[j];
        v[j + 1] = val;
    }
}

void qsort(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}