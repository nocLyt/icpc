
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

const int N=50000;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;


/*
    这个题题意不太好懂啊=。=
    我们定义 一个路径的E值为它的最长边的边长。
    然后有Q个询问， 询问有多少个路径的E值小于等于Li;

    解法： 离线并查集。
    按边长排序，把询问从小到大排序。
    然后对于询问 Li, 把所有<=Li的边加进去，统计。 合并两个集合，+= 两个集合点数的乘积

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

int fa[N],n,m,q, cnt[N];
node e[N];
II qs[N], ans[N];

void init()
{
    rep(i,0,n)
    {
        fa[i]= i;
        cnt[i]= 1;
    }

}
int find(int x)
{
    if(fa[x]==x)    return x;
    return fa[x]= find(fa[x]);
}
bool cmp1(const II &a, const II &b)
{
    return a.second<b.second;
}
bool cmp2(const II &a, const II &b)
{
    return a.first<b.first;
}
void unionf(int x, int y, int &sum)
{
    int fax= find(x);
    int fay= find(y);
    if(fax==fay)
        return;
    sum+= cnt[fax]*cnt[fay];
    cnt[fax]+= cnt[fay];
    fa[fay]= fax;
}


int main()
{

    while(~scanf("%d%d%d",&n,&m,&q))
    {
        rep(i,1,m)
            e[i].read();
        sort(e+1,e+1+m);
        rep(i,1,q)
        {
            qs[i].first= i;
            scanf("%d", &qs[i].second);
        }
        sort(qs+1,qs+1+q,cmp1);
        init();
        int sum= 0;
        int k= 1;
        rep(i,1,q)
        {
            for(;k<=m&& e[k].c<=qs[i].second;k++)
                unionf(e[k].x, e[k].y,sum);
            ans[i].first= qs[i].first;
            ans[i].second= sum;
        }
        sort(ans+1, ans+1+q,cmp2);

        rep(i,1,q)
            printf("%d\n", ans[i].second);

    }


}
