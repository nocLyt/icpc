
/*

*/
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

int dblcmp(double x)   {return fabs(x)<EPS?0:x>0?1:-1;}
inline bool insize(int c,int l,int r){if (c>=l&&c<=r) return true; return false;}
template<class T> inline void checkmin(T &a,T b)	{if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b)	{if(a < b)	a = b;}
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int ,int> II;
typedef long long  LL;

int dx[] = {-1,0,1,0};//up Right down Left
int dy[] = {0,1,0,-1};

const int N=15;       // 点数
const int E= 20002;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    计算下K的范围: 12*12/4= 36<2^6
    要 已经形成环路的个数.
    要保证环不包含环， 则要保证当形成一个环时， 两边的插头个数都为偶数。 后判断， 判断[0,j-1], [j,m]
    cha 记录已经形成环的个数


    尼玛，终于1Y一道插头DP了。

*/

const int H_SIZE= 300007;
const int S_SIZE= 1000010;
const int MOD= 1000000007;



struct HASHMAP
{
    int head[H_SIZE], nt[S_SIZE], f[S_SIZE], nv;
    LL sta[S_SIZE];
    void init()
    {
        nv= 0;
        mem(head,-1);
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
        for(int k=head[h];~k;k=nt[k])
            if(sta[k]==st)
            {
                f[k]+= ans;
                f[k]%= MOD;
                return;
            }
        add(st,h,ans);
    }

};


HASHMAP hm[2];
int n, m, K, cha, code[N], tmp[N];
bool g[N][N];
char str[N];

void decode(int *code, int m, LL st)
{
    for(int i=0;i<=m;i++,st>>=3)
        code[i]= st&7;
    cha= st&63;
}
void shift(int *code, int m)
{
    for(int i=m;i>=1;i--)
        code[i]= code[i-1];
    code[0]= 0;
}
LL encode(int *code,int m)
{
    LL st= 0;
    st|= cha;
    mem(tmp,-1);
    tmp[0]= 0;
    int cnt= 1;
    for(int i=m;i>=0;i--)
    {
        st<<=3;
        if(tmp[code[i]]==-1)    tmp[code[i]]= cnt++;
        code[i]= tmp[code[i]];
        st|= code[i];
    }
    return st;
}

bool Wrong(int *code, int j)
{
    int c1(0), c2(0);
    for(int i=0;i<=j-1;i++) if(code[i]) c1++;
    for(int i=j;i<=m;i++)   if(code[i]) c2++;
    if(c1&1 || c2&1)    return true;
    return false;
}

void dp_Blank(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code,m, hm[cur].sta[k]);
        int left= code[j-1], up= code[j];
        if(left&& up)   // 两个插头
        {
            if(left==up)    //形成环， 要保证cha<K
            {
                if(cha<K)
                {
                    code[j-1]= code[j]= 0;
                    cha++;
                    if(Wrong(code,j))   continue;
                    if(j==m)
                        shift(code,m);
                    hm[cur^1].push(encode(code,m), hm[cur].f[k]);
                }
            }
            else    // 合并联通块
            {
                code[j-1]= code[j]= 0;
                for(int t=0;t<=m;t++)
                    if(code[t]==left)   code[t]= up;
                // if(Wrong(code,j))   continue;
                if(j==m)
                    shift(code,m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
        }
        else if(left||up)   //一个插头
        {
            int t=left?left:up;
            if(g[i][j+1])   //Right
            {
                code[j-1]=0; code[j]= t;
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
            if(g[i+1][j])   //Down
            {
                code[j-1]=t; code[j]= 0;
                if(j==m)
                    shift(code,m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
        }
        else    // 没有插头
        {
//            // 跳过
//            code[j]= code[j-1]= 0;
//            if(j==m)    shift(code,m);
//            hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            // 产生 联通块
            if(g[i][j+1] && g[i+1][j])
            {
                decode(code,m, hm[cur].sta[k]);
                code[j]= code[j-1]= 13;
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
        }

    }

}

void dp_Block(int i, int j, int cur)
{
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code,m, hm[cur].sta[k]);
        if(code[j-1] || code[j])    continue;
        code[j]= code[j-1]= 0;
        if(j==m)
            shift(code,m);
        hm[cur^1].push(encode(code,m), hm[cur].f[k]);
    }
}

void solve()
{
    int cur= 0;
    hm[0].init();
    hm[0].push(0,1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            hm[cur^1].init();
            if(g[i][j])
                dp_Blank(i,j,cur);
            else
                dp_Block(i,j,cur);
            cur^=1;
        }
    LL ans=0 ;
    for(int k=0;k<hm[cur].nv;k++)
    {
        decode(code,m, hm[cur].sta[k]);
        if(cha==K)
        {
            ans+= hm[cur].f[k];
            ans%= MOD;
        }
    }
    printf("%I64d\n", ans);

}

void init()
{
    scanf("%d%d%d",&n,&m,&K);
    mem(g,0);
    for(int i=1;i<=n;i++)
    {
        scanf("%s", str);
        for(int j=0;j<m;j++)
            if(str[j]=='.') g[i][j+1]= 1;
    }
}

int main(){

    int nca;
    scanf("%d", &nca);
    while(nca--)
    {
        init();
        solve();
    }

}



