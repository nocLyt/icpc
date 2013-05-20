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
typedef int   LL;

const int N= 15;       // 点数
const int H_SIZE= 10007;
const int S_SIZE= 1000010;

/*
    题目大意：
    两个含有2的格子，两个含有3的格子。求从2走到2和从3走到3的路径长度。
    并且两个路径不能相交，有障碍格子，非障碍格子最多只能走一次。

    插头状态分为： 有插头, 2格子的插头， 3格子的插头。 用4进制比较快。
    注意点：
        对于2，3格子，最多只能有一个插头。(论文上说的独立插头)
        对于障碍格子，不能有插头。
    具体的讨论在代码里有注释。

    这个题已经开始讨论好多种情况了。插头DP有了模板以后代码的难度就降低了，但是难点就是怎么考虑全面并且不犯错，真的好难阿。

*/

struct HASHMAP
{
    int head[H_SIZE], nt[S_SIZE], nv;
    LL sta[S_SIZE], f[S_SIZE];
    void init()
    {
        memset(head, -1,sizeof(head));
        nv= 0;
    }
    void add(LL st, int h, int ans)
    {
        f[nv]= ans;
        sta[nv]= st;
        nt[nv]= head[h];
        head[h]= nv++;
    }
    void push(LL st, int ans)
    {
        int h= st%H_SIZE;
        for(int k=head[h];~k;k=nt[k])//!!
        {
            if(st==sta[k])
            {
                if(f[k]>ans)
                    f[k]= ans;
                return;
            }
        }
        add(st, h, ans);
    }
};

HASHMAP hm[2];
int g[N][N], code[N], n,m;

void decode(int *code, int m, LL st)
{
    for(int i=m;i>=0;i--)
    {
        code[i]= st&3;
        st>>= 2;
    }
}
LL encode(int *code, int m)
{
    LL st= 0;
    for(int i=0;i<=m;i++)
    {
        st<<=2;
        st|= code[i];
    }
    return st;
}
void shift(int *code, int m)
{
    for(int i=m;i>=1;i--)
        code[i]= code[i-1];
    code[0]= 0;
}

void init()
{
    memset(g,0,sizeof(g));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d", &g[i][j]);
            if(g[i][j]==1 || g[i][j]== 0)
                g[i][j]^= 1;
        }
}

void dp_Blank(int i,int j, int cur) // 空白格子
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code, m, hm[cur].sta[k]);
        int left= code[j-1], up= code[j];
        if(left && up)  // 含有两个插头
        {
            if(left == up)  // 两个插头相等才有效
            {
                code[j]= code[j-1]= 0;
                if(j==m)
                    shift(code, m);
                hm[cur^1].push(encode(code, m), hm[cur].f[k]+1);
            }
        }
        else if(left || up) // 当且仅有一个插头
        {
            int t= left?left:up;
            if(g[i][j+1]==1 || g[i][j+1]==t)    // 右转移
            {
                code[j]= t; code[j-1]= 0;
                hm[cur^1].push(encode(code, m), hm[cur].f[k]+1);
            }
            if(g[i+1][j]==1 || g[i+1][j]==t)    // 下转移
            {
                code[j-1]= t; code[j]= 0;
                if(j==m)
                    shift(code, m);
                hm[cur^1].push(encode(code, m), hm[cur].f[k]+1);
            }
        }
        else    //一个插头都没有
        {
            // 跳过
            code[j]= code[j-1]=0;
            if(j==m)
                shift(code, m);
            hm[cur^1].push(encode(code, m), hm[cur].f[k]);

            // 产生 连通块
            //!! 在这傻逼了 一个插头=2，一个插头=3的给忽略的。 并且分枝判断考虑少了。
            int t= g[i+1][j]+g[i][j+1];
            if( t>=2 && (t!=5))
            {
                if(t<4 || (t==4 && g[i+1][j]==2) )  //产生2连通块 : 11,12,21,22
                {
                    decode(code,m,hm[cur].sta[k]);  //!!尼玛，sta打成f了。
                    code[j]= code[j-1]= 2;
                    hm[cur^1].push(encode(code, m), hm[cur].f[k]+1);
                }
                if( (g[i+1][j]&1) && (g[i][j+1])&1 )  // 产生3连通块 : 11,13,31,33
                {
                    decode(code,m,hm[cur].sta[k]);  //!!尼玛，sta打成f了。
                    code[j]= code[j-1]= 3;
                    hm[cur^1].push(encode(code, m), hm[cur].f[k]+1);
                }
            }


        }

    }
}

void dp_Block(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code, m, hm[cur].sta[k]);
        //!! 如果有插头的话，不符合题意，应直接跳过
        if(code[j-1] || code[j])
            continue;
        code[j]= code[j-1]=0;
        if(j==m)
            shift(code, m);
        hm[cur^1].push(encode(code, m), hm[cur].f[k]);
    }
}

void dp_2(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code,m,hm[cur].sta[k]);
        int left= code[j-1], up= code[j];
        //!! 如果有两个插头，就是不符合题意！应该跳过
        if((left&&up)||(left&&left!=2) || (up&&up!=2)) // 有两个插头， 或者含有不是2的插头，直接跳过
            continue;
        if(left || up)  //有一个插头
        {
            code[j]= code[j-1]= 0;
            if(j==m)
                shift(code, m);
            hm[cur^1].push(encode(code, m), hm[cur].f[k]+1);
        }
        else    // 没有插头，产生一个插头
        {
            // to right
            if(g[i][j+1]==1|| g[i][j+1]==2)
            {
                code[j]= 2; code[j-1]= 0;
                hm[cur^1].push(encode(code,m), hm[cur].f[k]+1);
            }
            // to down
            if(g[i+1][j]==1 || g[i+1][j]==2)
            {
                code[j-1]= 2; code[j]= 0;
                if(j==m)
                    shift(code,m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]+1);
            }

        }


    }

}


void dp_3(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code,m, hm[cur].sta[k]);
        int left=code[j-1], up=code[j];
        if((left&&up)||(left&&left!=3) || (up&&up!=3))
            continue;
        if(left||up)
        {
            code[j]= code[j-1]= 0;
            if(j==m)
                shift(code,m);
            hm[cur^1].push(encode(code, m), hm[cur].f[k]+1);
        }
        else
        {
            if(g[i][j+1]==1 || g[i][j+1]==3)
            {
                code[j]= 3; code[j-1]= 0;
                hm[cur^1].push(encode(code,m), hm[cur].f[k]+1);
            }
            if(g[i+1][j]==1 || g[i+1][j]==3)
            {
                code[j-1]= 3; code[j]= 0;
                if(j==m)
                    shift(code,m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]+1);
            }

        }

    }
}


void solve()
{
    int cur= 0;
    hm[cur].init();
    hm[cur].push(0,0);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            hm[cur^1].init();
            if(g[i][j]==0)
                dp_Block(i,j,cur);
            else if(g[i][j]==1)
                dp_Blank(i,j,cur);
            else if(g[i][j]==2)
                dp_2(i,j,cur);
            else
                dp_3(i,j,cur);
            cur^=1 ;
        }
    LL ans= 0;
    for(int i=0;i<hm[cur].nv;i++)
        ans+= hm[cur].f[i];
    if(ans>0)
        ans-= 2;
    cout<<ans<<endl;
}

int main()
{

    while(~scanf("%d%d", &n,&m))
    {
        if(!n && !m)    break;
        init();
        solve();
    }

}
