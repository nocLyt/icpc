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

int dblcmp(double x)   {return fabs(x)<EPS?0:x>0?1:-1;}
inline bool insize(int c,int l,int r){if (c>=l&&c<=r) return true; return false;}
template<class T> inline T sqr(T x){return x*x;}
template<class T> inline void checkmin(T &a,T b)	{if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b)	{if(a < b)	a = b;}
typedef long long   LL;

const int N= 20;       // 点数
const int H_SIZE= 10007;
const int S_SIZE= 100010;

/*
    题目大意： 简单回路。 有的格子必须经过，有的格子可经过可不经过，有的格子不能经过，求回路的个数。

    因为要走必须经过的点， 所以我们不能确定最后一个非障碍格子是否满足条件。
    增加一个状态isend ，记录是否已经形成环。
    如果已经形成环了，那么如果再在转移的时候碰到 左插头和上插头，那么肯定不是一个条环了，不符合条件，舍去不计。
                    并且，如果再转移到必须的走的格子，说明形成环时没有走这个格子，也要舍去不计。

    还要注意，如果没有左插头和上插头，那么可以产生连通块， 也可以跳过 可走可不走的格子。注意，跳过操作和 生产连通块是并列的。

    其他的就是和 Ural1519 Formula1 一样了。
*/

struct HASHMAP
{
    int head[H_SIZE], nt[S_SIZE], nv;
    LL f[S_SIZE], sta[S_SIZE];
    void init()
    {
        memset(head, -1, sizeof(head));
        nv=0;
    }
    void add(LL st, int h, LL ans)
    {
        f[nv]= ans;
        sta[nv]= st;
        nt[nv]= head[h];
        head[h]= nv++;
    }
    void push(LL st, LL ans)
    {
        int h= st%H_SIZE;
        for(int i=head[h];~i;i=nt[i])
        {
            if(st==sta[i])
            {
                f[i]+= ans;
                return;
            }
        }
        add(st, h, ans);
    }
};

HASHMAP hm[2];
int code[N], n, m, tmp[N], g[N][N];
int isend;

void decode(int *code, int , LL st)
{
    for(int i=m;i>=0;i--)
    {
        code[i]= st&7;
        st>>= 3;
    }
    isend= st&1;
}
void shift(int *code, int m)
{
    for(int i=m;i>=1;i--)
        code[i]= code[i-1];
    code[0]= 0;
}
LL encode(int *code, int m) // 增加 isend标记
{
    LL st= isend;
    int cnt= 1;
    memset(tmp, -1,sizeof(tmp));
    tmp[0]= 0;

    for(int i=0;i<=m;i++)
    {
        if(tmp[code[i]]==-1)    tmp[code[i]]= cnt++;
        code[i]= tmp[code[i]];
        st<<= 3;
        st|= code[i];
    }
    return st;
}


void init()
{
    char str[20];
    memset(g,0,sizeof(g));
    scanf("%d%d", &n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s", str);
        for(int j=0;j<m;j++)
        {
            if(str[j]=='*')
                g[i][j+1]= 1;
            else if(str[j]=='O')
                g[i][j+1]= 2;
        }
    }
}



void dp_Blank(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code, m, hm[cur].sta[k]);
        int left= code[j-1], up= code[j];
        if(isend)// 已经形成回路了。
        {
            if(left ||up || g[i][j]==2)  continue;
            code[j]= code[j-1]= 0;
            if(j==m)//!! 漏了这个一直WA...
                shift(code,m);
            hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            continue;
        }
        else if(left && up)// 左和上插头都存在
        {
            if(left==up)// 同一个连通块， 合并， 更新isend
            {
                code[j]= code[j-1]= 0;
                isend= 1;
                if(j==m)
                    shift(code, m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
            else // 不是同一个连通块，则合并。
            {
                code[j]= code[j-1]= 0;
                for(int t=0;t<=m;t++)
                    if(code[t]==up)
                        code[t]= left;
                if(j==m)
                    shift(code,m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
        }
        else if(left|| up)// 存在一个插头
        {
            int t= left?left:up;
            if(g[i][j+1]) // 向右扩展
            {
                code[j-1]=0; code[j]= t;
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
            if(g[i+1][j])// 向下
            {
                code[j-1]=t; code[j]= 0;
                if(j==m)
                    shift(code, m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }

        }
        else
        {
            if(g[i][j+1] && g[i+1][j])// 产生新连通块
            {
                code[j]= code[j-1]= 13;  //!!要>7
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
            // 注意处理 可经过可不经过的点。 和上面产生连通块是并列关系
            if(g[i][j]==1)
            {
                code[j]= code[j-1]= 0;
                if(j==m)
                    shift(code, m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }

        }

    }
}


void dp_Block(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code,m,hm[cur].sta[k]);
        code[j-1]= code[j]= 0;
        if(j==m)
            shift(code,m);
        hm[cur^1].push(encode(code,m), hm[cur].f[k]);
    }
}


void solve()
{
    int cur= 0;
    hm[cur].init();
    hm[cur].push(0,1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            hm[cur^1].init();
            if(g[i][j])
                dp_Blank(i,j,cur);
            else
                dp_Block(i,j,cur);
            cur^= 1;
        }
    LL ans= 0;
    for(int i=0;i<hm[cur].nv;i++)
    {
        ans+= hm[cur].f[i];
    }
    cout<<ans<<endl;
}

int main(){
    int nca, ica(0);
    scanf("%d", &nca);
    while(nca--)
    {
        hm[0].init(); hm[1].init();
        printf("Case %d: ", ++ica);
        init();
        solve();
    }


}



