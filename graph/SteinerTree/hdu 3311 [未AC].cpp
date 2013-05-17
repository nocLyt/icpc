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
#define EPS 1e-9

//--------------
//
//--------
#define FI first
#define SE second
#define PB push_back
#define MP(a,b) make_pair(a,b)
#define VIS vector<string>
#define SZ(x) int(x.size())
#define foreach(i,x) for(__typeof(x.begin()) i=x.begin();i!=x.end();++i)
#define ALL(x) x.begin(),x.end()
template<class T> inline void CLR(T &A) {
    A.clear();
}
#define DO(n) while(n--)
#define DO_C(n) int n____=n;while(n____--)
//----------
typedef long long LL;
inline bool insize(int c,int l,int r) {
    if (c>=l&&c<=r) return true;
    return false;
}
template<class T> inline void checkmin(T &a,T b) {
    if(a == -1 || a > b)a = b;
}
template<class T> inline void checkmax(T &a,T b) {
    if(a < b)    a = b;
}
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int ,int> II;
typedef queue<int> QI;

int dx[] = {0,1,0,-1, 1, 1, -1, -1};//up Right down Left
int dy[] = {1,0,-1,0, 1, -1, 1, -1};
int dblcmp(double x) {
    return fabs(x-0)<EPS?0:x>0?1:-1;
}
template<class T> inline void sf(T& x) {
    char c;
    int mul = 1;
    while((c = getchar()) != EOF) {
        if(c == '-')mul = -1;
        if(c >= '0' && c <= '9') {
            x = c-'0';
            break;
        }
    }
    if(c == EOF) {
        x = EOF;
        return;
    }
    while((c = getchar())) {
        if(c >= '0' && c <= '9') {
            x = (x<<1)+(x<<3)+(c-'0');
        } else break;
    }
    x *= mul;
}
template<class T0, class T1> inline void sf(T0& x, T1& y) {sf(x);sf(y);}
template<class T0, class T1, class T2> inline void sf(T0& x, T1& y, T2& z) {sf(x);sf(y);sf(z);}

// mem 127, 0x7f => 2139062143 => 0x7F7F7F7F
// mem  63, 0x3f => 1061109567 => 0x3f3f3f3f
// mem 255, 0xff => -1
const int N=1010;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;
struct Graph {
	int head[N];
	int pnt[E],val[E],nt[E],ne;
	void init() {
		ne= 0; mem(head,-1);
	}
	void add(int u,int v, int c) {
		pnt[ne]= v; val[ne]= c;
		nt[ne]=head[u]; head[u]=ne++;
	}
};

queue<II> q;
int n, m,p, max_s;
int f[N][200];
int bit[10];
Graph g;
bool vis[N][200];
int dp[N];

void init() {
	mem(f,0x3f);     mem(vis,0);     mem(dp,0x3f); while(!q.empty())    q.pop();
    g.init();
	max_s= 1<<(n+1);
	bit[0]= 1<<n;
	rep(i,1,n+m)
        if(i<=n)    bit[i]= 1<<(i-1);
        else bit[i]= 0;
	rep(i,1,n+m) {
		isf(x);
		if(i<=n) {
            f[i][bit[i]]= 0;
            f[0][bit[0]|bit[i]]= x;
		}else {
            f[i][bit[0]]= x;
		}
	}

    DO(p) {
    	int x, y, c;
    	sf(x,y,c); g.add(x,y,c); g.add(y,x,c);
    }
}

void spfa() {
	while(!q.empty()) {
		II tmp= q.front(); q.pop();
		int u= tmp.FI, s=tmp.SE;
		vis[u][s]= 0;
		for(int i=g.head[u];~i;i=g.nt[i]) {
			int v= g.pnt[i], c=g.val[i];
			int ns= s|bit[v];
			if(f[u][s]+c< f[v][ns]) {
				f[v][ns]= f[u][s]+c;
				if(s==ns && !vis[v][ns]) {
					q.push(MP(v,ns));
					vis[v][ns]= 1;
				}
			}
		}
	}

}

void solve() {

    rep(k,1,max_s-1) {
    	rep(i,0,n+m) {
    		for(int x=(k-1)&k;x;x=(x-1)&k) {
    			f[i][k]= min(f[i][k], f[i][x|bit[i]]+f[i][(k-x)|bit[i]]);
    		}
    		if(f[i][k]<INF) q.push(MP(i,k)),vis[i][k]= 1;
    	}
    	spfa();
    }

//    rep(i,0,n+m)    rep(j,0,max_s-1)
//        printf("f[%d][%d]= %d\n", i,j,f[i][j]);


    rep(k,0,max_s-1) rep(i,0,n+m)
        checkmin(dp[k], f[i][k]);

    printf("%d\n", dp[max_s-1]);

}

int main(){

    while(~scanf("%d%d%d",&n,&m,&p)) {
    	init();
        solve();
    }

}
