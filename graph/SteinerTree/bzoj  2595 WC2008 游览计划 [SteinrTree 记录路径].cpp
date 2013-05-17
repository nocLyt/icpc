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

int dx[] = {0,1,0,-1};//up Right down Left
int dy[] = {1,0,-1,0};
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
const int N=10;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    枚举子树形态：     f[i][j]= min(f[i][j], f[i][k]+f[i][l]) 其中k和l是j的一个划分，即 k|l==j;
    按照边进行松弛:    f[i][j]= min(f[i][j], dp[i'][j]+w[i][j]) 期中i' 和j相连

    参考： http://endlesscount.blog.163.com/blog/static/821197872012525113427573/
*/

int n, m, stc, max_s;
int f[N][N][3000], pre[N][N][3000];
int g[N][N], st[N][N];
queue<int> q;
bool vis[N][N][3000];
bool bo[N][N];

void spfa() {
    while(!q.empty()) {
    	int tmp= q.front();
    	int x= tmp/100000;
    	int y= (tmp- x*100000)/10000;
    	int s= tmp- x*100000- y*10000;
    	q.pop();
    	vis[x][y][s]= 0;
    	rp(i,4) {
    		int tx= x+dx[i], ty= y+dy[i];
    		if(insize(tx,0,n-1) && insize(ty,0,m-1)) {
    			int ts= s | st[tx][ty];
    			if(f[x][y][s]+g[tx][ty]<f[tx][ty][ts]) {
			    f[tx][ty][ts]= f[x][y][s]+g[tx][ty];
			    pre[tx][ty][ts]= x*100000+ y*10000+ s;
			    if(!vis[tx][ty][ts] && ts==s) {
			    	vis[tx][ty][ts]=1;
			    	q.push(tx*100000 +ty*10000+ts);
			    }
    			}
    		}
    	}
    }
}


void dfs(int x, int y, int s) {
	bo[x][y]= 1;
	int t= pre[x][y][s];
	if(!t)  return;
	int px= t/100000;
	int py= (t- px*100000)/10000;
	int ps= t- px*100000- py*10000;
	dfs(px,py,ps);
	if(px==x && py==y)
        dfs(x,y, (s-ps)|st[x][y]);
}



int main() {

    stc= 0; mem(vis,0); mem(bo,0); mem(g,0); mem(st,0);
    scanf("%d%d", &n,&m);
    rp(i,n) rp(j,m) {
    	scanf("%d",&g[i][j]);
    	if(!g[i][j]) {
    		st[i][j]= 1<<(stc++);
    	}
    }

    max_s= (1<<(stc));

    rp(i,n) rp(j,m) {
    	rp(k,max_s) f[i][j][k]= INF;
    	if(st[i][j])    f[i][j][st[i][j]]= 0;
    }
    // 枚举子状态 [i][j][k]

    rep(k,1,max_s-1){
    	rp(i,n) rp(j,m) {
    		if(st[i][j]&& !(k&st[i][j]) )    continue;
    		for(int x=(k-1)&k;x;x=(x-1)&k) {
    			int t= f[i][j][x|st[i][j]]+ f[i][j][(k-x)|st[i][j]]- g[i][j];
    			if(t<f[i][j][k]) {
    				f[i][j][k]= t;
    				pre[i][j][k]= i*100000+j*10000+(x|st[i][j]);
    			}
    		}
    		if(f[i][j][k]<INF)  q.push(i*100000+j*10000+k), vis[i][j][k]=1;
    	}
        spfa();
    }

    rp(i,n) rp(j,m) {
    	if(st[i][j]) {
    		printf("%d\n", f[i][j][max_s-1]);
            dfs(i,j,max_s-1);
            rp(x,n) {
            	rp(y,m) {
            		if(st[x][y])    printf("x");
            		else if(bo[x][y])  printf("o");
            		else printf("_");
            	}
            	puts("");
            }
    		return 0;
    	}
    }


}




