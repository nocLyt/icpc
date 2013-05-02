
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

const int N=100010;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    rank[] 储存偏移量 。 =0表示同类 =1表示不同类
    在路径压缩时根据父节点回溯修改 当前节点的偏移量。

*/

int fs[N], rank[N];
int n, m;

void init()
{
    rep(i,1,n)
        fs[i]= i, rank[i]= 0;
}

int find(int rt)
{
    if(fs[rt]==rt)  return rt;
    int p= find(fs[rt]);
    rank[rt]= (rank[rt]+rank[fs[rt]])&1;
    return fs[rt]= p;
}
int unionF(int x, int y, int k)
{
    int fax= find(x);
    int fay= find(y);

    if(fax!=fay)
    {
        fs[fax]= fay;
        rank[fax]= (rank[x]+rank[y]+k)&1;
    }
    else
    {
        int t= (rank[x]+rank[y])&1;
        if(!t)  return 1;
    }
    return 0;
}

int main()
{

    int nca, ica(0);
    sf(nca);
    while(nca--)
    {
        if(ica) puts("");
        printf("Scenario #%d:\n", ++ica);
        sf(n); sf(m);
        bool flag(0);
        init();
        while(m--)
        {
            int x,y; sf(x); sf(y);
            if (unionF(x,y, 1))
                flag= 1;

        }
        if(flag)
            puts("Suspicious bugs found!");
        else
            puts("No suspicious bugs found!");

    }

}
