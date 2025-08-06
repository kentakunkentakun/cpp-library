// nCr
long long next_combination(long long sub)
{
    long long x = sub & -sub, y = sub + x;
    return (((sub & ~y) / x) >> 1) | y;
}

long long bit = (1 << k) - 1; // bit = {0, 1, 2}
for (; bit < (1 << n); bit = next_combination(bit))
{
    /* ここに処理を書く */
}

///////////////////////////////////////////////////////////////
// com[i][j] = iCj（i個からj個を選ぶ）を全計算
com[0][0] = 1;
for (int i = 1; i < 51; ++i)
{
    for (int j = 0; j <= i; ++j)
    {
        com[i][j] += com[i - 1][j];
        if (j > 0)
            com[i][j] += com[i - 1][j - 1];
    }
}
