
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
#define foreach(i,x) for(__typeof(x.begin()) i=x.begin();i!=x.end();++i)
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define rp(i,a) for(int i=0;i<a;i++)
#define FD(i,a,b) for(int i=a;i>=b;i--)
#define STOP  system("pause")
#define PP printf(" ")
#define mem(x,y) memset(x,y,sizeof(x))
#define LN printf("\n");
#define du freopen("in.txt","r",stdin)
#define chu freopen("out.txt","w",stdout)
#define EPS 1e-8
#define FI first
#define SE second
#define PB push_back
#define MP make_pair


typedef long long LL;
inline bool insize(int c,int l,int r){if (c>=l&&c<=r) return true; return false;}
template<class T> inline void checkmin(T &a,T b){if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b){if(a < b)    a = b;}
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int ,int> II;

int dx[] = {0,1,0,-1};//up Right down Left
int dy[] = {1,0,-1,0};
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

const int N=1005;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

struct Point{

    double x, y;
    void readln(){
        scanf("%lf%lf",&x,&y);
    }
    double dis(Point tmp){
        return sqrt((x-tmp.x)*(x-tmp.x)+(y-tmp.y)*(y-tmp.y));
    }
};


struct Prim_mst
{
    double w[N][N];
    int pn, pu[N], pv[N],pre[N];
    int fa[N];
    double d[N];
    int person[N];
    bool vis[N];
    double mst;
    int find(int x)
    {
        if(fa[x]==x) return x;
        return fa[x]= find(fa[x]);
    }
    double prime(int n)
    {
        rep(i,0,n)
            d[i]= -1;
        mem(pre,0);
        mem(vis,0);
        double ret= 0;
        pn= -1;
        int last= 1;
        d[last]= 0;
        rep(i,1,n)
        {
            if(last==-1)    return -1;
            pu[++pn]= last;
            pv[pn]= pre[last];
            ret+= d[last];
            vis[last]= 1;
            int p0= last;
            last= -1;
            rep(j,1,n)
                if(!vis[j])
                {
                    if(d[j]<0 || d[j]>w[p0][j])
                    {
                        d[j]= w[p0][j];
                        pre[j]= p0;
                    }
                    if(last<0 || d[j]<d[last])
                        last= j;
                }
        }
        return ret;
    }
    double calc(int x, int n)
    {
        rep(i,1,n)  fa[i]= i;
        rep(i,1,pn)
            if(i!=x)
            {
                int l= find(pu[i]);
                int r= find(pv[i]);
                fa[l]= r;
            }
        int s1= -1, s2= -1;
        int tmp= find(pu[x]);
        rep(i,1,n)
            if(find(i)==tmp)
                checkmax(s1, person[i]);
            else
                checkmax(s2, person[i]);
        return (double)(s1+s2)/(mst-w[pu[x]][pv[x]]);
    }
    void solve(int n)
    {
        mst= prime(n);
        double ret= -1;
        rep(i,1,pn)
            checkmax(ret, calc(i, n));
        printf("%.2lf\n", ret);
    }


};

int n;
Point pot[N];
Prim_mst p;

int main()
{

    int nca;
    sf(nca);
    while(nca--)
    {
        sf(n);
        rep(i,1,n)
        {
            pot[i].readln();
            scanf("%d",&p.person[i]);
        }
        rep(i,1,n) rep(j,i,n)
            p.w[i][j]=p.w[j][i]= pot[i].dis(pot[j]);
        p.solve(n);

    }


}
