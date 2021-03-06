#include <bits/stdc++.h>
const int maxn = 3e5 + 5;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
using namespace std;
struct SAM{
    int trans[maxn<<1][3], slink[maxn<<1], maxlen[maxn<<1];
    // 用来求endpos
    int indegree[maxn<<1], endpos[maxn<<1], rank[maxn<<1], ans[maxn<<1];
    // 计算所有子串的和(0-9表示)
    long sum[maxn<<1];
    int last, now, root, len;
    inline void newnode (int v) {
        maxlen[++now] = v;
    }
    inline void init() {
        root = now = 1;
        memset(trans, 0, sizeof(trans));
        // memset(slink, 0, sizeof(slink));
        // memset(maxlen, 0, sizeof(maxlen));
    }
    inline void extend(int c) {
        if (trans[last][c]) { // 广义自动机 节点合并 节省空间
            int p = last, np = trans[last][c];
            if (maxlen[last] + 1 == maxlen[np]) last = np;
            else {
                int q = trans[p][c];
                newnode(maxlen[p]+1);
                int nq = now;
                memcpy(trans[nq], trans[q], sizeof(trans[q]));
                slink[nq] = slink[q];
                slink[q] = last = nq;
                while (p && trans[p][c] == q) {
                    trans[p][c] = nq;
                    p = slink[p];
                }
            }
            return;
        }
        newnode(maxlen[last] + 1); // 新建节点
        int p = last, np = now;
        // 更新trans
        while (p && !trans[p][c]) { // last的slink只想新节点
            trans[p][c] = np;
            p = slink[p];
        }
        if (!p) slink[np] = root; 
        else { // slink中存在节点有到c的边
            int q = trans[p][c];
            if (maxlen[p] + 1 != maxlen[q]) { // 判断是否为同一个endpos
                newnode(maxlen[p] + 1); // 将q点拆出nq，使得maxlen[p] + 1 == maxlen[q]
                int nq = now;
                memcpy(trans[nq], trans[q], sizeof(trans[q]));
                slink[nq] = slink[q];
                slink[q] = slink[np] = nq;
                while (p && trans[p][c] == q) {
                    trans[p][c] = nq;
                    p = slink[p];
                } 
            }else slink[np] = q;
        }
        last = np;
        // 初始状态为可接受状态
        endpos[np] = 1;
    }
    inline void insert(char *buf) {
        len = strlen(buf);
        last = 1;
        for (int i = 0; i < len; ++i) extend(buf[i] - '0'); // extend(s[i] - '1');
    }
    // 求不同的子串种类
    inline long long all () {
        long long ans = 0;
        for (int i = root+1; i <= now; ++i) {
            ans += maxlen[i] - maxlen[ slink[i] ];
        }
        return ans;
    }
}sam;
char s[maxn], ss[maxn], t[4] = "012";
int main() {
    int n;
    while (scanf("%d%s", &n, s) != EOF) {
        sam.init();
        do{
            for (int i = 0; i < n; ++i) {
                ss[i] = t[s[i]-'a'];
            }
            sam.insert(ss);
        }while(next_permutation(t, t+3));
        long long ans = sam.all();
        int tmp = 1, sum = 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] == s[i-1]) ++tmp;
            else tmp = 1;
            sum = max(sum, tmp);
        }
        ans += sum * 3;
        printf("%lld\n", ans/6);
    }
    return 0;
}
