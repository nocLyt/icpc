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

const int N= 15;       // 点数
const int E= 20002;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

const int H_SIZE= 30007;
const int S_SIZE= 1000010;

/*
    最小表示法 n<=12， 联通块所用序号应该是 [0, n/2] , 则用 2^3即可表示

*/

struct HASHMAP
{
    int head[H_SIZE],next[S_SIZE],nv;
    long long state[S_SIZE];
    long long f[S_SIZE];
    void init()
    {
        nv=0;
        memset(head,-1,sizeof(head));
    }
    void push(long long st,long long ans)
    {
        int i;
        int h=st%H_SIZE;
        for(i=head[h];i!=-1;i=next[i])//这里要注意是next
          if(state[i]==st)
          {
              f[i]+=ans;
              return;
          }
        state[nv]=st;
        f[nv]=ans;
        next[nv]=head[h];
        head[h]=nv++;
    }
};

int code[N], n, m, g[N][N], ex, ey, tmp[N];
HASHMAP hm[2];

void init()
{
    char str[N];
    memset(g,0,sizeof(g));
    scanf("%d%d", &n,&m);
    ex=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",&str);
        for(int j=0;j<m;j++)
        {
            if(str[j]=='.')
            {
                ex=i;
                ey=j+1;
                g[i][j+1]=1;
            }
        }
    }
}


void decode(int *code,int m,long long  st)
{
    for(int i=m;i>=0;i--)
    {
        code[i]=st&7;
        st>>=3;
    }
}
LL encode(int *code,int m)//最小表示法
{
    memset(tmp,-1,sizeof(tmp));
    tmp[0]= 0;
    int cnt= 1;// =1!!
    LL st= 0;
    for(int i=0;i<=m;i++)
    {
        if(tmp[code[i]]==-1)
            tmp[code[i]]= cnt++;
        code[i]= tmp[code[i]];
        st<<=3;
        st|= code[i];
    }
    return st;
}
void shift(int *code, int m)
{
    for(int i=m;i>=1 ;i--)
        code[i]=code[i-1];
    code[0]=0;
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
        int left= code[j-1], up= code[j];
        if(left && up)
        {
            if(left==up)    // 两个相同的联通块要联通， 只能发生在最后一个非障碍格子上
            {
                if(i==ex && j==ey)
                {
                    code[j-1]= code[j]= 0;
                    if(j==m)
                        shift(code, m);
                    hm[cur^1].push(encode(code,m), hm[cur].f[k]);
                }
            }
            else    // 不是同一个联通分量则合并， 并修改 up的另一头为left
            {
                code[j]= code[j-1]= 0;
                for(int t=0;t<=m;t++)
                    if(code[t]==up)
                        code[t]= left;
                if(j==m)
                    shift(code, m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }

        }
        else if(left || up) // 保持原来的联通分量
        {
            int t= (left)?left:up;
            if(g[i][j+1])
            {
                code[j]= t; code[j-1]= 0;
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }
            if(g[i+1][j])
            {
                code[j-1]= t; code[j]= 0;
                if(j==m)
                    shift(code,m);
                hm[cur^1].push(encode(code,m), hm[cur].f[k]);
            }

        }
        else    // 无插头， 构造联通快
        {
            if(g[i+1][j] && g[i][j+1])
            {
                code[j-1]= code[j]= 13;
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
    printf("%I64d\n", ans);
}

int main(){

    init();
    if(ex<0)
    {
        puts("0");
        return 0;
    }
    solve();

}




