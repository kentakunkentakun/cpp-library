//nCr
long long next_combination(long long sub) {
    long long x = sub & -sub, y = sub + x;
    return (((sub & ~y) / x) >> 1) | y;
}

long long bit = (1<<k)-1;  // bit = {0, 1, 2}
for (;bit < (1<<n); bit = next_combination(bit)) {
        /* ここに処理を書く */
}
