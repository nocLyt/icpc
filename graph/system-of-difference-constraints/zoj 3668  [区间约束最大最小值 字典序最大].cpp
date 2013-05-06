//#pragma comment(linker, "/STACK:102400000,102400000")

#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#include <bitset>
#include <stack>
#include <deque>
#include <assert.h>

using namespace std;
#define BUG1 puts("BUG11\n")
#define BUG2 puts("BUG22\n")
#define rep(i,a,b)  for(int (i)=(a);(i)<=(b);(i)++)
#define rp(i,n) for(int i=0;i<n;i++)
#define repp(i,a,b,c) for(int i=a;(c>0)?(i<=b):(i>=b);i+=c)
#define isf(x) int x;sf(x);
#define STOP  system("pause")
#define PP printf(" ")
#define mem(x,y) memset(x,y,sizeof(x))
#define LN printf("\n");
#define du freopen("in.txt","r",stdin)
#define chu freopen("out.txt","w",stdout)
#define EPS 1e-8
//--------
#define FI first
#define SE second
#define PB push_back
#define MP(a,b) make_pair(a,b)
#define VIS vector<string>
#define SZ(x) int(x.size())
#define foreach(i,x) for(__typeof(x.begin()) i=x.begin();i!=x.end();++i)
#define ALL(x) x.begin(),x.end()
template<class T> inline void CLR(T &A) {A.clear();}
#define DO(n) while(n--)
#define DO_C(n) int n____=n;while(n____--)
//----------
typedef long long LL;
inline bool insize(int c,int l,int r){if (c>=l&&c<=r) return true; return false;}
template<class T> inline void checkmin(T &a,T b){if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b){if(a < b)    a = b;}
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int ,int> II;
typedef queue<int> QI;

int dx[] = {0,1,0,-1};//up Right down Left
int dy[] = {1,0,-1,0};
int dblcmp(double x){return fabs(x-0)<EPS?0:x>0?1:-1;}
template<class T> inline void sf(T& x)
{
    char c;
    int mul = 1;
    while((c = getchar()) != EOF)
    {
        if(c == '-')mul = -1;
        if(c >= '0' && c <= '9')
        {
            x = c-'0';
            break;
        }
    }
    if(c == EOF){x = EOF;return;}
    while((c = getchar()))
    {
        if(c >= '0' && c <= '9')
        {
            x = (x<<1)+(x<<3)+(c-'0');
        }
        else break;
    }
    x *= mul;
}
template<class T0, class T1> inline void sf(T0& x, T1& y){sf(x);sf(y);}
// mem 127, 0x7f => 2139062143 => 0x7F7F7F7F
// mem  63, 0x3f => 1061109567 => 0x3f3f3f3f
// mem 255, 0xff => -1
const int N=100005;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    这个题的字典序最大，就是让前面的石头尽可能的大。
    spfa 判负环。
    对于区间[L,R] 最大值a, 最小值 b
    add(L,R,a), add(R,L,-b)
    然后为了保证 每个石子能量最大为10000和字典序最大
    add(L,R,10000) add(R,L,10000);

*/

struct Graph
{
#define grep(g,i,u) for(int i=g.head[u];~i;i=g.nt[i])
    int head[N];
    int pnt[E], nt[E], val[E], ne;
    void init() {mem(head,-1); ne=0; }
    void add(int u, int v,int c=0) {pnt[ne]=v, val[ne]=c, nt[ne]= head[u], head[u]= ne++;}
};

struct SPFA
{
    bool vis[N];
    int d[N];
    int cnt[N];
    QI q;
    bool relax(int u, int v, int c)
    {
        if(d[v]>d[u]+c)
        {
            d[v]= d[u]+c;
            return 1;
        }
        return 0;
    }
    bool spfa(Graph &g, int n, int src)
    {
        mem(cnt,0); mem(vis,0); mem(d,0x3f); while(!q.empty())  q.pop();
        q.push(src), d[src]= 0, vis[src]=1;
        while(!q.empty())
        {
            int u= q.front(); q.pop();
            vis[u]= 0;
            grep(g,i,u)
            {
                int v= g.pnt[i];
                if(relax(u,v,g.val[i]) && !vis[v])
                {
                    if((++cnt[v])>n)    return 0;
                    q.push(v); vis[v]= 1;
                }
            }
        }
        return 1;
    }

    void solve(Graph &g, int n)
    {
        if(!spfa(g,n,0))
           puts("The spacecraft is broken!");
        else
        {
            printf("%d", d[1]-d[0]);
            rep(i,2,n)
                printf(" %d", d[i]-d[i-1]);
            puts("");
        }

    }

};
Graph g;
int n, m;
SPFA spfa;

int main()
{

    while(~scanf("%d%d", &n,&m))
    {
        g.init();
        DO_C(m)
        {
            int L, R, a, b;
            sf(L,R); sf(a,b);   L--;
            g.add(L, R, b), g.add(R,L, -a);
        }
        rep(i,1,n)
            g.add(i-1,i,10000), g.add(i,i-1,10000);

        spfa.solve(g, n);

    }


}

