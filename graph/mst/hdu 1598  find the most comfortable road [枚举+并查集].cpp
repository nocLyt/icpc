
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

const int N=205;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;


/*
    数据量很小， 可以很暴力的去做
    把边排序， 然后枚举每条最短的边，构造最小生成树。
    我们不必担心最小的边是否在s(起点)->t(终点)上，因为不在边上的话必然不是最有值。
    时间复杂度 O(10^7)

*/


struct node
{
    int x, y, c;
    void read()
    {
        scanf("%d%d%d", &x,&y,&c);
    }
    bool operator <(const node &b) const
    {
        return c<b.c;
    }
};

int fa[N],n,m;
node a[1005];

int find(int x)
{
    if(fa[x]==x)    return x;
    return fa[x]= find(fa[x]);
}

int main()
{

    while(~scanf("%d%d", &n,&m))
    {
        rep(i,0,m-1)
            a[i].read();
        sort(a,a+m);
        int q;
        sf(q);
        while(q--)
        {
            int s, t;
            scanf("%d%d", &s,&t);
            int ans= -1;
            rep(i,0,m-1)
            {
                rep(k,0,n)
                    fa[k]= k;

                rep(j,i,m-1)
                {
                    int fax= find(a[j].x);
                    int fay= find(a[j].y);
                    if(fax!=fay)
                        fa[fax]= fay;
                    if(find(s)==find(t))
                    {
                        checkmin(ans, a[j].c-a[i].c);
                        break;
                    }
                }

            }
            printf("%d\n", ans);

        }

    }

}
