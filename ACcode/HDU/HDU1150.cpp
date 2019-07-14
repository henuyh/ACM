#include <bits/stdc++.h>
#define LL long long
#define P pair<int, int>
#define lowbit(x) (x & -x)
#define mem(a, b) memset(a, b, sizeof(a))
#define mid ((l + r) >> 1)
#define lc rt<<1
#define rc rt<<1|1
#define endl '\n'
const int maxn = 1e3 + 5;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
using namespace std;
int used[maxn], girl[maxn];
vector<int> g[maxn];
void init() {
	for (int i = 0; i < maxn; ++i) g[i].clear();
	mem(girl, 0);
}
int dfs(int u) {
	for (int i = 0; i < (int)g[u].size(); ++i) {
		int v = g[u][i];
		if (used[v]) continue;
		used[v] = 1;
		if (girl[v] == 0 || dfs(girl[v])) {
			girl[v] = u;
			return 1;
		}
	}
	return 0;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n, m, k;
	while (cin >> n >> m >> k , n) {
		init();
		for (int i = 0; i < k; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			g[b].push_back(c);
		}
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			mem(used, 0);
			ans += dfs(i);
		}
		cout << ans << endl;
	}
	
	return 0;
}
