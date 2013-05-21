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
template<class T> inline void checkmin(T &a,T b)	{if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b)	{if(a < b)	a = b;}
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

const int N= 65;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;


/*
    要保证每个城镇PowerStation只开一次，并且开连续的天数。
    精确覆盖。
    每个Town每天要安排一列，保证每个城镇PowerStation 只用一次， 再加n列。

    根据每个PowerStation的Work区间， 枚举具体的Work区间(最多15个)。
    因为保证每个Town当且仅当选一次，每个Town还要增加单独的一行，
    这一行只标记上后n列中自己对应的列，表示自己的PowerStation在D天一次也不用
    这样以来，每个Town 最多16行

    行数  60*16
    列数  60*5+60

    我用 RInfo rfo[] 离散化存储行的信息。还挺方便

    最后判断是否有解时多加了个! 导致自己Debug()半天没找到为什么 No solution
    自己竟然要怀疑模板的正确性了。。罪过啊。。

*/


struct RInfo
{
    int id,l,r;
    static int cnt;
    RInfo(){}
    RInfo(int _id, int _l, int _r): id(_id),l(_l),r(_r){}
    bool operator <(const RInfo &r) const
    {
        return id<r.id;
    }
};

struct DancingLinks
{
    #define NR 1000
    #define NC 500
    #define O 200000
    #define rp(A,i,j) for(int i=A[j];i!=j;i=A[i])
    int sz;
    int U[O],D[O],L[O],R[O], C[O], X[O];
    int S[NC], H[NR];
//----------
    int ans[NR];
//----------

    void init(int m)
    {
        mem(S,0);
        mem(H,-1);
        mem(ans,0);
        // 初始化每列的头
        rep(i,0,m)
        {
            U[i]= D[i]= i;
            L[i]= i-1;
            R[i]= i+1;
        }
        L[0]= m; R[m]= 0;
        sz= m+1;
        //-----
    }

    void build(int x, int y)
    {

        //--------------
        C[sz]= y, X[sz]= x, S[y]++;
        D[sz]= D[y];
        U[D[y]]= sz;
        D[y]= sz;
        U[sz]= y;
        if(H[x]==-1)    // 该行第一个元素
            H[x]= L[sz]= R[sz]= sz;
        else
        {
            int t= H[x];
            R[sz]= t;
            R[L[t]]= sz;
            L[sz]= L[t];
            L[t]= sz;
        }
        sz++;
    }

    void remove(int y)
    {
        R[L[y]]= R[y];
        L[R[y]]= L[y];
        rp(D,i,y)
        {
            rp(R,j,i)
            {
                U[D[j]]= U[j];
                D[U[j]]= D[j];
                S[C[j]]--;
            }
        }

    }

    void resume(int y)
    {
        R[L[y]]= L[R[y]]= y;
        rp(U,i,y)
        {
            rp(L,j,i)
            {
                U[D[j]]= D[U[j]]= j;
                S[C[j]]++;
            }
        }
    }


    int dfs(int k)
    {
        if(!R[0])
        {
            return k;
        }
        int c=0, tmp=N;
        rp(R,i,0)
            if(S[i]<tmp)
                tmp=S[c=i];
        remove(c);
        rp(D,i,c)
        {
            rp(R,j,i)
                remove(C[j]);
            ans[k]= X[i];
            int t= dfs(k+1);
            if(t)   return t;
            rp(L,j,i)
                resume(C[j]);
        }
        resume(c);
        return 0;
    }

//-----------------------------------

#undef N
#undef O
#undef rp(A,i,j)
};


DancingLinks dlx;
int n,m,d;
int g[N][N];
RInfo rfo[1000];
RInfo ans[65];
int RInfo::cnt= 0;

int main(){

    while(~scanf("%d%d%d",&n,&m,&d))
    {
        dlx.init(n*d+n);
        RInfo::cnt= 0;
        mem(g,0);
        rep(i,1,m)
        {
            int x, y;
            scanf("%d%d",&x,&y);
            g[x][y]= g[y][x]=1;
        }

        rep(i,1,n)
        {
            g[i][i]= 1;
            int x,y;
            scanf("%d%d", &x,&y);
            // 使用 i， 枚举天数区间[s,t]
            rep(s,x,y) rep(t,s,y)
            {
                rfo[++RInfo::cnt]= RInfo(i,s,t);
                rep(j,1,n) // 枚举每条边
                    if(g[i][j])
                        rep(day,s,t)    // 枚举区间每天
                        {
                            dlx.build(RInfo::cnt, (j-1)*d+day);
                        }
                dlx.build(RInfo::cnt, n*d+i);
            }
            // 不使用i
            rfo[++RInfo::cnt]= RInfo(i,0,0);
            dlx.build(RInfo::cnt, n*d+i);
        }

        // 计算
        int ret= dlx.dfs(0);
        if (!ret)
        {
            puts("No solution");
        }
        else
        {
            rep(i,1,n)
                ans[i]= RInfo(i,0,0);
            rep(i,0,ret-1)
            {
                int x= dlx.ans[i];
                int id= rfo[x].id;
                ans[id]= rfo[x];
            }
            sort(ans+1,ans+1+n);
            rep(i,1,n)
                printf("%d %d\n", ans[i].l, ans[i].r);
        }
        puts("");


    }

}

