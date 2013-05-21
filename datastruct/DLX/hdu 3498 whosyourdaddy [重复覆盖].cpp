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

const int N= 60;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    重复覆盖问题。  求最少点。

    怎么跑这么慢啊。。

*/


struct DancingLinks
{
    #define NR 60
    #define NC 60
    #define O 3600
    #define rp(A,i,j) for(int i=A[j];i!=j;i=A[i])
    int sz;
    int U[O],D[O],L[O],R[O], C[O], X[O];
    int S[NC], H[NR];
//---------------
    int ans;
//---------------
    void init(int m)
    {
        mem(H,-1);
        mem(S,0);
        rep(i,0,m)
        {
            U[i]= D[i]= i;
            L[i]= i-1;
            R[i]= i+1;
        }
        L[0]= m, R[m]= 0;
        sz= m+1;
        //-----
        ans= NR;
    }

    void remove(int c)
    {
        rp(D,i,c)
        {
            L[R[i]]= L[i];
            R[L[i]]= R[i];
            S[C[i]]--;
        }
    }
    void resume(int c)
    {
        rp(U,i,c)
        {
            L[R[i]]= R[L[i]]= i;
            S[C[i]]++;
        }
    }
    void dfs(int k)
    {
        if(k+Hash()>=ans)   return;
        if(!R[0])
        {
            ans= k;
            return;
        }

        int tmp= NR, c=0;
        rp(R,i,0)
        {
            //if(S[i]==0) return;     // ??
            if(S[i]<tmp)
                tmp= S[c=i];
        }
        rp(D,i,c)
        {
            remove(i);
            rp(R,j,i)  remove(j);
            dfs(k+1);
            rp(L,j,i)  resume(j);
            resume(i);
        }

    }
    int Hash()
    {
        int ret= 0;
        bool hash[NC]= {0};
        rp(R,c,0)
        {
            if(!hash[c])
            {
                hash[c]= 1;
                ret++;
                rp(D,i,c)
                    rp(R,j,i)
                        hash[C[j]]= 1;
            }
        }
        return ret;
    }
    void build(int r, int c)
    {
        S[c]++; C[sz]=c;X[sz]=r;
        D[sz]= D[c];
        U[D[c]]= sz;
        D[c]= sz;
        U[sz]= c;
        if(H[r]==-1)
            H[r]= L[sz]= R[sz]= sz;
        else
        {
            int h= H[r];
            R[L[h]]= sz;
            L[sz]= L[h];
            R[sz]= h;
            L[h]= sz;
        }
        sz++;
    }

    #undef NR
    #undef NC
    #undef O
    #undef rp(A,i,j)
};


DancingLinks dlx;
int n,m;
bool g[N][N];

int main(){

    while(~scanf("%d%d",&n,&m))
    {
        mem(g,0);
        rep(i,1,m)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            g[x][y]= g[y][x]= 1;
        }
        dlx.init(n);
        rep(i,1,n)
        {
            g[i][i]= 1;
            rep(j,1,n)
                if(g[i][j])
                    dlx.build(i,j);

        }
        dlx.dfs(0);
        printf("%d\n",dlx.ans);

    }

}

