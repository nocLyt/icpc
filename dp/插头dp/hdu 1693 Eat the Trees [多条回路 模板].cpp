
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <stack>
#include <deque>

using namespace std;
#define BUG1 puts("BUG11\n")
#define BUG2 puts("BUG22\n")
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define rp(i,a) for(int i=0;i<a;i++)
#define mem(a,x) memset(a,x,sizeof(a))
#define FD(i,a,b) for(int i=a;i>=b;i--)
#define STOP  system("pause")
#define PP printf(" ")
#define SET(x,y) memset(x,y,sizeof(x))
#define LN printf("\n");
#define du freopen("in.txt","r",stdin)
#define chu freopen("out.txt","w",stdout)
#define EPS 1e-8

#define FI first
#define SE second
#define PB push_back
#define MP make_pair

int dblcmp(double x)   {return fabs(x)<EPS?0:x>0?1:-1;}
inline bool insize(int c,int l,int r){if (c>=l&&c<=r) return true; return false;}
template<class T> inline T sqr(T x){return x*x;}
template<class T> inline void checkmin(T &a,T b)	{if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b)	{if(a < b)	a = b;}
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int ,int> II;
typedef long long   LL;

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
    while(c = getchar())
    {
        if(c >= '0' && c <= '9')
        {
            x = (x<<1)+(x<<3)+(c-'0');
        }
        else break;
    }
    x *= mul;
}

int dx[] = {-1,0,1,0};//up Right down Left
int dy[] = {0,1,0,-1};

const int N= 13;       // 点数
const int E= 20002;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

    const int H_SIZE= 10007;
    const int S_SIZE= 1000010;
struct HASHMAP
{

    LL f[S_SIZE];
    int head[H_SIZE], nt[S_SIZE], state[S_SIZE], nv;
    void init()
    {
        nv= 0;
        memset(head,-1,sizeof(head));
    }
    void add(int st,int h, LL ans)
    {
        f[nv]= ans;
        state[nv]= st;
        nt[nv]= head[h];
        head[h]= nv++;
    }
    void push(int st, LL ans)
    {
        int h= st%H_SIZE;
        for(int i=head[h];~i;i=nt[i])
        {
            if(st==state[i])
            {
                f[i]+= ans;
                return;
            }
        }
        add(st,h,ans);
    }
};

int code[N], n, m, g[N][N];
HASHMAP hm[2];

void init()
{
    scanf("%d%d", &n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d", &g[i][j]);
    for(int i=1;i<=m;i++)   // 边界填0
        g[n+1][i]= 0;
    for(int i=1;i<=n;i++)
        g[i][m+1]= 0;
}
/*  解码 */
void decode(int *code, int m, int st)
{
    for(int i=0;i<=m;i++,st>>=1)
        code[i]= st&1;
}
/* 处理完一行的格子，换行移位 */
void shift(int *code , int m)
{
    for(int i=m;i>=1;i--)
        code[i]= code[i-1];
    code[0]= 0;
}

/*  二进制编码   */
int encode(int *code, int m)
{
    int st= 0;
    for(int i=m;i>=0;i--)
    {
        st<<=1;
        st|= code[i];
    }
    return st;
}

/*
    left 表示 (i,j-1)是否含有右插头
    up 表示 (i-1,j)是否含有上插头
*/
void dp_Blank(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code, m, hm[cur].state[k]);
        bool left= code[j-1],  up= code[j];
        if(left && up)
        {
            code[j]= code[j-1]= 0;
            if(j==m)
                shift(code, m);
            hm[cur^1].push(encode(code,m), hm[cur].f[k]);
        }
        else if(left || up)
        {
            if(g[i][j+1])   // 能转化为右插头，则必然j!=m
            {
                code[j]= 1; code[j-1]= 0;
                hm[cur^1].push(encode(code, m), hm[cur].f[k]);
            }
            if(g[i+1][j])   // 能转化为下插头， 可能j=m!!
            {
                code[j]=0; code[j-1]= 1;
                if(j==m)
                    shift(code, m); //不能忘换行移位
                hm[cur^1].push(encode(code, m), hm[cur].f[k]);
            }
        }
        else
        {
            if(g[i+1][j] && g[i][j+1])
            {
                code[j]= code[j-1]= 1;  // 可以转移
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
        }

    }
}

void dp_Block(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code, m, hm[cur].state[k]);
        code[j-1]= code[j]= 0;
        if(j==m)
            shift(code, m);
        hm[cur^1].push(encode(code,m), hm[cur].f[k]);
    }

}

LL solve()
{
    LL ans= 0;
    int cur= 0;
    hm[cur].init();
    hm[cur].push(0,1);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            hm[cur^1].init();
            if(g[i][j])
                dp_Blank(i,j,cur);
            else
                dp_Block(i,j,cur);
            cur^=1;
        }
    }
    for(int i=0;i<hm[cur].nv;i++)
        ans+= hm[cur].f[i];
    return ans;
}

int main(){
    int nca, ica(0);
    scanf("%d", &nca);
    while(nca--)
    {
        printf("Case %d: ", ++ica);
        init();
        printf("There are %I64d ways to eat the trees.\n", solve());
    }

}
