
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

const int N=105;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

struct Prim_mst
{
    int d[N];
    bool vis[N];
    int prime(int g[N][N], int n)
    {
        mem(d,-1);
        mem(vis,0);
        int mst= 0, last= 1;
        d[last]= 0;
        rep(i,1,n)
        {
            if(last==-1)    return -1;
            mst+= d[last];
            vis[last]= 1;
            int p0= last;
            last= -1;
            rep(j,1,n)
                if(!vis[j])
                {
                    if(g[p0][j]<0)  continue;
                    checkmin(d[j], g[p0][j]);
                    if(last==-1 || d[j]<d[last])
                        last= j;
                }
        }
        return mst;
    }
};

Prim_mst p;
int g[N][N];
int n, m;


int main()
{

    while(~scanf("%d%d", &m, &n))
    {
        if(!m)  break;
        mem(g,-1);
        while(m--)
        {
            int x, y, c;
            scanf("%d%d%d", &x,&y,&c);
            g[x][y]= g[y][x]= c;
        }
        int t= p.prime(g,n);
        if(t==-1)
            puts("?");
        else
            printf("%d\n", t);
    }


}
