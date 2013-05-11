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
const int N=1005;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

typedef int type;
struct Point {
	int x, y, z;
};
Point p[N];
int dis(Point a, Point b){
    return abs(a.x-b.x)+abs(a.y-b.y)+abs(a.z-b.z);
}

struct Edge {
    int u, v;
    type c;
    Edge(){}
    Edge(int _u, int _v, type _c): u(_u),v(_v),c(_c){}
};
vector<Edge> e;

type in[N];
int id[N], vis[N], pre[N];
type DMST(int root, int nv, vector<Edge> &e) {
	type ret= 0;
	while(1) {
		rp(i,nv)    in[i]= INF;
		foreach(i,e){
			if(in[i->v]>i->c && i->u!=i->v && i->v!=root) {
				pre[i->v]= i->u;
				in[i->v]= i->c;
			}
		}
        rp(i,nv)    if(i!=root && in[i]==INF)   return -1;
        //找环 标记
        mem(vis,-1); mem(id,-1); in[root]= 0; int cnt= 0;
        rp(i,nv) {
        	ret+= in[i]; int v= i;
            for(; vis[v]==-1 && id[v]==-1&& v!=root; v=pre[v])
                vis[v]= i;
            if (v!=root && id[v]==-1&& vis[v]==i) { //判断是否存在环 注意v点必须第一次遍历到的。
            	for(int u=pre[v];u!=v;u=pre[u])
                    id[u]= cnt;
                id[v]= cnt++;
            }

        }
        if(!cnt)    break;
        rp(i,nv)    if(id[i]==-1)   id[i]= cnt++;
        foreach(i,e) {
        	int u=i->u, v=i->v;
        	i->u= id[u];
        	i->v= id[v];
        	if(id[u]!=id[v])
                i->c-= in[v];
        }
        nv= cnt;
        root= id[root];
	}
	return ret;
}


int n, X, Y, Z;
int main() {

    while(~scanf("%d%d%d%d",&n,&X,&Y,&Z) &&n) {
        CLR(e);
    	rep(i,1,n) {
            sf(p[i].x,p[i].y,p[i].z);
    	}
    	rep(i,1,n) {
            e.PB(Edge(0,i,X*p[i].z));
    		isf(k); DO(k) {
    			isf(x);
    			if(i==x)    continue;
    			int d=dis(p[i],p[x])*Y;
    			e.PB(Edge(i,x,d+(p[i].z>=p[x].z?0:Z)));
    		}
    	}
        printf("%d\n", DMST(0,n+1,e));
    }

}

