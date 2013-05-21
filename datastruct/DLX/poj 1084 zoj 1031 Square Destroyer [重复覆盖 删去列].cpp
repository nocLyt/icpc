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
    重复覆盖： 每个火柴一行， 每个正方形一列。
    行数: 2*n*(n+1)   <= 60
    列数: 1^2+2^2+..+n^2<=65

    画一下得出, 对于边长为1的小正方形(i,j)，它的上边火柴编号为k=(i-1)*(2*n+1)+j, 左右下分别为 k+n,k+n+1,k+2*n+1. (第i行第j列)
    然后枚举每个小正方形搞就行啦。

    注意的一点是：
        重复覆盖remove()是不在列头链表中删去当前列的。
    我的方法是先加入 2*n*(n+1)列，当枚举到的正方形的边已经有被删去的了，需要完整的删去该列。
    在remove()后， 还需要在列头链表中删去该列， 我用了一个方法 remove_chead();

*/

struct Square
{
    int u,d,l,r;
    Square(){}
    void set(int i, int j, int n)
    {
        u= (i-1)*(2*n+1)+j;
        l= u+n;
        r= u+n+1;
        d= u+2*n+1;
    }
    void pt()
    {
        printf("U=%d  L= %d  R= %d  D= %d\n", u,l,r,d);
    }
};

struct DancingLinks
{
    #define NR 70
    #define NC 70
    #define O 5000
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

    void remove_chead(int c)    // 在列head链表里删除head
    {
        R[L[c]]= R[c];
        L[R[c]]= L[c];
    }

    #undef NR
    #undef NC
    #undef O
    #undef rp(A,i,j)
};


DancingLinks dlx;
int n,m;
Square sq[30];
bool delv[70];  // delv[i]表示第i根火柴被删除了
VI vis;   // 表示哪根火柴属于正在枚举的正方形的边

int main(){

    int nca;
    sf(nca);
    while(nca--)
    {
        sf(n);
        mem(delv,0);
        for(sf(m);m;m--)
        {
            int x;
            sf(x);
            delv[x]= 1;
        }
        int cnt= 0;
        rep(i,1,n) rep(j,1,n)
            sq[++cnt].set(i,j,n);
        int numc=0, numr=2*n*(n+1), cntc=0;
        rep(i,1,n)
            numc+= i*i;
        dlx.init(numc); // 正方形个数


        rep(len,1,n)    // 枚举正方形边长
        {
            rep(x,1,n-len+1) rep(y,1,n-len+1) // 枚举左上角点
            {
                int xx= x+len-1, yy= y+len-1; // 右下角点 (x,y) -> (xx,yy)
                cntc++;     // 表示当前是哪个正方形

                //printf("i= %d  (%d,%d), (%d,%d)\n", cntc, x,y,xx,yy);

                vis.clear();
                rep(i,x,xx) rep(j,y,yy)
                {
                    int t= (i-1)*n+j;
                    if(i==x)        vis.push_back(sq[t].u);
                    if(i==xx)  vis.push_back(sq[t].d);
                    if(j==y)        vis.push_back(sq[t].l);
                    if(j==yy)  vis.push_back(sq[t].r);
                }
//                rep(i,0,vis.size()-1)
//                    printf("%d ", vis[i]);
//                LN;

                // 然后检验 此正方形上的边是否有被删去的
                bool flag= 0;
                rep(i,0,vis.size()-1)
                    if(delv[vis[i]])
                    {
                        flag= 1;
                        break;
                    }
                if(flag)    // 表示已经有边被删除, 则删除对应的正方形列
                {
                    // 重复覆盖的remove()是不删除列头的
                    dlx.remove_chead(cntc);
                    dlx.remove(cntc);
                    //puts("DEL");
                }
                else    // 否则， 把行加上去
                {
                    rep(i,0,vis.size()-1)
                        dlx.build(vis[i], cntc);
                }

            }

        }
        dlx.dfs(0);
        printf("%d\n", dlx.ans);

    }

}

