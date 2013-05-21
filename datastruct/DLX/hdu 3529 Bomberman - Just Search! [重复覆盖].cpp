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

const int N= 20;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    重复覆盖。 题目说一定有解。
    DLX直接搞就行。
*/


struct DancingLinks
{
    #define NR 400
    #define NC 400
    #define O 400
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
char mp[N][N];
int g[N][N];

int main(){

    while(~scanf("%d%d", &n,&m))
    {
        rep(i,0,n-1)
            scanf("%s", mp[i]);
        mem(g,0);
        int numc= 0, numr=0;
        rep(i,0,n-1)
            rep(j,0,m-1)
                if(mp[i][j]=='*')
                    g[i][j]= -1;
                else if(mp[i][j]=='#')
                    g[i][j]= ++numc;

        dlx.init(numc);

        rep(i,1,n-2) rep(j,1,m-2)
            if(g[i][j]==0)
            {
                ++numr;

                for(int x=i, y=j;y>0;y--)    // To Left
                    if(g[x][y]!=0)
                    {
                        if(g[x][y]>0)   dlx.build(numr, g[x][y]);
                        break;
                    }

                for(int x=i,y=j;y<m-1;y++)  // To Right
                    if(g[x][y]!=0)
                    {
                        if(g[x][y]>0)   dlx.build(numr, g[x][y]);
                        break;
                    }

                for(int x=i,y=j;x>0;x--)  // To Up
                    if(g[x][y]!=0)
                    {
                        if(g[x][y]>0)   dlx.build(numr, g[x][y]);
                        break;
                    }

                for(int x=i,y=j;x<n-1;x++)  // To Dpwn
                    if(g[x][y]!=0)
                    {
                        if(g[x][y]>0)   dlx.build(numr, g[x][y]);
                        break;
                    }


            }

        dlx.dfs(0);
        printf("%d\n", dlx.ans);

    }

}

