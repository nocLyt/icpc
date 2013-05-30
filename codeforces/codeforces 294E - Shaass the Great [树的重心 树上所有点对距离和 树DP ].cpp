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
#define feach(i,x) for(__typeof(x.begin()) i=x.begin();i!=x.end();++i)
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

int dx[] = {0,1,0,-1, 1, 1, -1, -1};//up Right down Left
int dy[] = {1,0,-1,0, 1, -1, 1, -1};
int sig(double x){return fabs(x-0)<EPS?0:x>0?1:-1;}
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
template<class T0, class T1> inline void sf(T0& x, T1& y) {sf(x);sf(y);}
template<class T0, class T1, class T2> inline void sf(T0& x, T1& y, T2& z) {sf(x);sf(y);sf(z);}
// mem 127, 0x7f => 2139062143 => 0x7F7F7F7F
// mem  63, 0x3f => 1061109567 => 0x3f3f3f3f
// mem 255, 0xff => -1
const int N=5005;       // 点数
const int E=20055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    题意： 给定一颗边权树。。你可以移动任意一条边，只要新图仍然是一颗树。 求min(所有点对之间的距离的和)

    枚举删去每条边。 然后 划分成两个子树。
    那么显然要接到这两棵子树的重心（所有结点到该点的距离和最小）上去。
    设到两个子树的重心为 pl, pr 两颗子树的节点和为lc, rc.  删掉的边的边权为c;
    两颗子树的点到该树重心的距离和为 ls1 rs1
    两颗子树内部点对的距离和为 ls2, rs2

    则新树的距离和为: lc*rc*c+ ls1*rc+ rs1*lc+ ls2+rs2;
    求最小值。
    注意INF要大大大大一些。

    http://blog.csdn.net/veda_/article/details/8774223
    这个分析的很好。 其中所说的最小的suml,sumr就是求树的重心。


*/

struct Graph {
#define rpg(i,u) for(int i=g.head[u];~i;i=g.nt[i])
	int head[N];
	int pnt[E], val[E], nt[E], ne;
	int fro[E];
	void init() {
		ne= 0; mem(head,-1);
	}
	void add(int u, int v, int c) {
	    fro[ne]= u;
		pnt[ne]= v; val[ne]= c;
		nt[ne]= head[u]; head[u]= ne++;
	}
};

Graph g;
int n;
int son[N]; //结点有多少个儿子。
int del;    // 表示Grpa中 下标为del的边被删掉了。

int dfs(int u, int fa) {   //算出来儿子个数
    son[u]= 1;
    rpg(i,u) {          if((i>>1)==del) continue;
    	int v= g.pnt[i];
    	if(fa==v)   continue;
    	son[u]+= dfs(v, u);
    }
    // printf("son[%d]= %d\n",u,son[u]);
    return son[u];
}

// 计算 重心   子树孩子个数的最大值最小。
// pp为重心  ppc表示子树孩子个数的最大值最小  n表示树的节点个数
// tmp来表示 子树u 孩子个数的最大值
void dfs1(int u, int fa, int& pp, int &ppc, int n) { 

    int tmp= n-son[u];
    rpg(i,u)  {         if((i>>1)==del) continue;
    	int v= g.pnt[i];
        if(v==fa)   continue;
        checkmax(tmp, son[v]);
        dfs1(v,u,pp,ppc,n);
    }
    if(tmp<ppc) {
    	pp= u; ppc= tmp;
    }
}

void dfs2(int u, int fa, LL &ls1, LL &ls2, int n) {    //计算 树内所有点 到树根局距离和。
    son[u]= 1;
	rpg(i,u) {      if((i>>1)==del) continue;
        int v= g.pnt[i], c=g.val[i];
        if(v==fa)   continue;
        dfs2(v,u,ls1,ls2,n);
        son[u]+= son[v];
        ls1+= (LL)son[v]* c;
        ls2+= (LL)son[v]*(n-son[v])*c;
	}
}



int main(){
    //du;

    sf(n);  g.init();
    DO_C(n-1) {
    	int x, y, c;sf(x,y,c);
    	g.add(x,y,c); g.add(y,x,c);
    }

    LL ans= LINF;   // 要大大大大点
    repp(i,0,g.ne-1,2) {
        del= i>>1;
    	int u= g.fro[i], v=g.pnt[i], c= g.val[i], lpc=INF, lp, rp, rpc=INF;

        // 先对一棵树操作
        int lc= dfs(u, -1);      // 左子树有 lc个节点
        dfs1(u,-1,lp,lpc,lc);   // 左子树的重心为lp
        // 重新计算 孩子， 计算所有点到 lp的距离和 ls1, 树内所有点相互到达的距离 ls2
        LL ls1(0), ls2(0);
        dfs2(lp,-1,ls1,ls2,lc);

        //再操作另一棵树
        int rc= dfs(v,-1);
        dfs1(v,-1,rp,rpc,rc);
        LL rs1(0), rs2(0);
        dfs2(rp,-1,rs1,rs2,rc);

        LL sum= (LL)c*rc*lc+ rs2+ls2+ (LL)ls1*rc+ rs1*lc ;
        checkmin(ans, sum);
    }
    cout<<ans<<endl;


}
