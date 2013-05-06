
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

struct node
{
    int a, b, t;
    void read()
    {
        scanf("%d", &a);
        char ch;
        while((ch=getchar())==' ');
        scanf("%d", &b);
        if(ch=='=') t= 0;
        else if(ch=='<')    t= 1;
        else t= 2;
    }
};

int fa[N], rank[N];
node a[N];
int ans[N];
int n,m;
VI vi;

void init()
{
    rep(i,0,n)
        fa[i]= i, rank[i]= 0;
}

int find(int x)
{
    if(fa[x]==x)    return x;

    int tmp= fa[x];
    fa[x]= find(fa[x]);
    rank[x]= (rank[x]+rank[tmp])%3;
    return fa[x];
}

bool isTrue(int x, int y, int r)
{
    int fax= find(x);
    int fay= find(y);

    if(fax!=fay)    return 1;

    int tmp= 0;
    if(rank[y]==1)  tmp= 2;
    else if(rank[y]==2) tmp=1;

    tmp= (tmp+rank[x])%3;
    if(tmp==r)  return 1;
    return 0;
}

void unionf(int x, int y, int r)
{
    int fax= find(x);
    int fay= find(y);
    if(fax==fay)  return;
    int tmp= 0;
    if (rank[x]==2) tmp= 1;
    else if (rank[x]==1) tmp= 2;

    rank[fax]= (tmp+r+rank[y])%3;
    fa[fax]= fay;

}

int testf(int k)
{
    int i= 1;
    for(;i<=m;i++)
    {
        if(a[i].a==k || a[i].b==k)  continue;
        if(isTrue(a[i].a, a[i].b,a[i].t))
            unionf(a[i].a, a[i].b, a[i].t);
        else
            return i;
    }
    return i;

}

int main()
{

    while(~scanf("%d%d", &n,&m))
    {
        rep(i,1,m)
            a[i].read();
        int right=-1, len= 0, cnt=0;

        rep(i,0,n-1)
        {
            init();
            ans[i]= testf(i);
            if(ans[i]>m)
                right=i, cnt++;
            else
                checkmax(len, ans[i]);
        }

        if(cnt==1)  printf("Player %d can be determined to be the judge after %d lines\n",right,len);
        else if(cnt>1)  puts("Can not determine");
        else    puts("Impossible");
    }
    return 0;

}
