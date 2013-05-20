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
template<class T> inline void checkmin(T &a,T b)    {if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b)    {if(a < b)    a = b;}
typedef long long LL;

const int N= 35;       // 点数
const int H_SIZE= 10007;
const int S_SIZE= 2000010;

/*

    草纸上画了画，分析得 从奇数行转移到偶数行，不用移位。  偶数行的话，偏移两位, 前两位填 0；

    每个格子进出要考虑三个面， 状态增了一倍。
    把图竖起来，行列交换了考虑 简单些。
    奇数行 和 偶数行 向下转移略有不同，要注意。

*/

struct HASHMAP
{
    int head[H_SIZE], nt[S_SIZE], sta[S_SIZE], nv;
    LL  f[S_SIZE];
    void init()
    {
        memset(head, -1,sizeof(head));
        nv= 0;
    }
    void add(int st, int h, LL ans)
    {
        f[nv]= ans;
        sta[nv]= st;
        nt[nv]= head[h];
        head[h]= nv++;
    }
    void push(int st, LL ans)
    {
        int h= st%H_SIZE;
        for(int k=head[h];~k;k=nt[k])//!!
        {
            if(st==sta[k])
            {
                f[k]+= ans;
                return;
            }
        }
        add(st, h, ans);
    }
};

HASHMAP hm[2];
int g[N][N], code[N], n,m, z;

void decode(int *code, int m, int st)
{
    for(int i=m;i>=0;i--)
    {
        code[i]= st&1;
        st>>= 1;
    }
}

int encode(int *code, int m)
{
    int st= 0;
    for(int i=0;i<=m;i++)
    {
        st<<=1;
        st|= code[i];
    }
    return st;
}
void shift(int *code, int m) //!!
{
    for(int i=m;i>1;i--)
        code[i]= code[i-2];
    code[1]= code[0]= 0;
}


// 奇数行格子， 不用考虑 shift了。 (i,j) -> (i+1,j-1), (i+1,j), (i,j+1)
void dp_Blank(int i,int j, int cur) // 空白格子
{
    // 左left 左上 q, 右上 p
    int r= 2*(j-1);
    int d1= (i&1)?j-1:j, d2= (i&1)?j:j+1;
    for(int k=0;k< hm[cur].nv;k++)
    {
        decode(code, 2*m, hm[cur].sta[k]);
        int left= code[r], q= code[r+1], p= code[r+2];
        int ss= left+ q+ p;
        if(ss==2) // 两个插头, 合并连通块
        {
            code[r]= code[r+1]= code[r+2]= 0;
            if(j==m && !(i&1))  shift(code, m*2);
            hm[cur^1].push(encode(code,2*m), hm[cur].f[k]);
        }
        else if(ss==1)  // 有一个插头
        {
            if(g[i+1][d1])// 左下
            {
                code[r]= 1; code[r+1]= code[r+2]= 0;
                if(j==m && !(i&1))  shift(code, m*2);
                hm[cur^1].push(encode(code,2*m), hm[cur].f[k]);
            }
            if(g[i+1][d2])  // 右下
            {
                code[r+1]=1; code[r]= code[r+2]=0;
                if(j==m && !(i&1))  shift(code, m*2);
                hm[cur^1].push(encode(code,2*m), hm[cur].f[k]);
            }
            if(g[i][j+1])  // Right
            {
                code[r+2]=1; code[r]= code[r+1]= 0;
                hm[cur^1].push(encode(code,2*m), hm[cur].f[k]);
            }
        }
        else if(ss==0)    // 没有插头， 产生一个连通块
        {
            if(g[i+1][d1] && g[i+1][d2] )  // 左下和右下
            {
                code[r]= code[r+1]= 1; code[r+2]= 0;
                if(j==m && !(i&1))  shift(code, m*2);
                hm[cur^1].push(encode(code,2*m), hm[cur].f[k]);
            }
            if(g[i+1][d1] && g[i][j+1]) // 左下和 右
            {
                code[r]= code[r+2]= 1; code[r+1]= 0;
                if(j==m && !(i&1))  shift(code, m*2);
                hm[cur^1].push(encode(code,2*m), hm[cur].f[k]);
            }
            if(g[i+1][d2] && g[i][j+1])    // Right_Down && Right
            {
                code[r+1]= code[r+2]= 1; code[r]= 0;
                if(j==m && !(i&1))  shift(code, m*2);
                hm[cur^1].push(encode(code,2*m), hm[cur].f[k]);
            }
        }


    }

}

void dp_Block(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code, 2*m, hm[cur].sta[k]);
        int r= 2*(j-1);
        code[r]= code[r+1]= code[r+2]= 0;
        if(j==m&& !(i&1))
            shift(code,m*2);
        hm[cur^1].push(encode(code,2*m), hm[cur].f[k]);
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
            if(g[i][j])  // 石头
                dp_Blank(i,j,cur);
            else
                dp_Block(i,j,cur);
            cur^=1 ;
        }
    LL ans= 0;
    for(int i=0;i<hm[cur].nv;i++)
        if(hm[cur].sta[i]==0)
            ans+= hm[cur].f[i];

    cout<<ans<<endl;
}

void init()
{
    memset(g,0,sizeof(g));
    n= 8;
    char str[5];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            g[i][j]= 1;
    for(int i=0;i<z;i++)
    {
        scanf("%s", str);
        g[ str[1]-'A'+1][m-(str[0]-'A')]= 0;
    }

}


int main()
{

    while(~scanf("%d%d", &m,&z))
    {
        init();
        solve();
    }

}
