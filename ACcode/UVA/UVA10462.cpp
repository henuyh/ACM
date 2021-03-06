#include <bits/stdc++.h>
#define LL long long
#define P pair<int, int>
#define lowbit(x) (x & -x)
#define mem(a, b) memset(a, b, sizeof(a))
#define mid ((l + r) >> 1)
#define lc rt<<1
#define rc rt<<1|1
#define endl '\n'
const int maxn = 1e2 + 5;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
using namespace std;
struct ac{
	int u, v, w, flag;
}g[maxn*maxn];
int cmp (ac x, ac y) {
	return x.w < y.w;
}
vector<int> son[maxn];
int pre[maxn], dis[maxn][maxn];
int find (int x) {
	return (pre[x] == x) ? x : pre[x] = find(pre[x]);
}
int n, m;
void Kruskal() {
	for (int i = 0; i <= n; ++i) {
		son[i].clear();
		son[i].push_back(i);
		pre[i] = i;
	}
	sort(g, g+m, cmp);
	int sum = 0;
	int cnt = 0;
	for (int i = 0; i < m; ++i) {
		if (cnt == n+1) break;
		int fx = find(g[i].u);
		int fy = find(g[i].v);
		if (fx == fy) continue;
		g[i].flag = 1;
		sum += g[i].w;
		cnt++;
		int lenx = son[fx].size();
		int leny = son[fy].size();
		for (int j = 0; j < lenx; ++j) {
			for (int k = 0; k < leny; ++k) {
				dis[son[fx][j]][son[fy][k]] = dis[son[fy][k]][son[fx][j]] = g[i].w; 
			}
		}
		pre[fy] = fx;
		for (int j = 0; j < leny; ++j) {
			son[fx].push_back(son[fy][j]);
		}
		son[fy].clear();
	}
	if (cnt != n - 1) {
		puts("No way");
		return;
	}
	int ans = inf;
	for (int i = 0; i < m; ++i) {		
		if (g[i].flag) continue;
		ans = min(ans, sum + g[i].w - dis[g[i].u][g[i].v]);
	}
	if (ans == inf) puts("No second way");
	else printf("%d\n", ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
    	scanf("%d%d", &n, &m);
    	for (int i = 0; i < m; ++i) {
    		scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w);
    		g[i].flag = 0;
    	}
    	printf("Case #%d : ", Case++);
    	Kruskal();
    }
    return 0;
}