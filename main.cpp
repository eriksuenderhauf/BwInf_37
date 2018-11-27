#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 7;
const int MAXN = 4e4 + 42;
const int MAXK = 2e2 + 42;
int a[MAXN], sum[MAXN];
int dp[2][MAXN];
int par[MAXK][MAXN];

int f(int l, int r, int m) { // Summe der Elemente-Median von l bis r
    if (l > r)
        return 0;
    return sum[r] - sum[l - 1] - (r - l + 1) * a[m];
}

int cost(int i, int j) { // gibt das Minimum der lokalen Summe nach Lemma 1.1 zurück
    // return (summe der Elemente größer als der Median - Median) - (summe der Elemente kleiner als der Median - Median)
    return f((i + j) / 2 + 1, j, (i + j) / 2) - f(i, (i + j) / 2 - 1, (i + j) / 2);
}

void dfs(int j, int a, int b, int oA, int oB) {
    if (a > b)
        return;
    int m = (a + b) / 2;
    for (int l = oA; l <= min(oB, m - 1); l++) { // divide and conquer optimization
        int v = dp[(j & 1) ^ 1][l] + cost(l + 1, m); // berechne dp[j][m]
        if (v < dp[j & 1][m]) {
            dp[j & 1][m] = v;
            par[j][m] = l;
        }
    }
    dfs(j, a, m - 1, oA, par[j][m]);
    dfs(j, m + 1, b, par[j][m], oB);
}

int main()
{
    freopen("input6.txt", "r", stdin);
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    for (int i = 0; i <= n; i++) {
        dp[0][i] = INF, dp[1][i] = INF;
        if (i)
            sum[i] = sum[i - 1] + a[i]; // präfix summe
    }
    dp[0][0] = 0;
    for (int j = 1; j <= k; j++)
        dfs(j, 1, n, 0, n - 1); // berechne dp layer by layer
    printf("%d\n", dp[k & 1][n]);
    int p = n;
    for (int i = k; i > 0; i--) {
        int val = a[(p + par[i][p] + 1) / 2]; // median
        p = par[i][p];
        printf("%d ", val);
    }
    printf("\n");
    return 0;
}
