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

const int N=20000;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    16*16 的数独
    行数 16*16*16 表示 第i行第j列填k
    列数 16*16*4 表示 第i行有k， 第j列有k，第p个大方格有k，格子(i,j)已填


*/

struct node{
    int i, j, k;
    node(){}
    node(int _i, int _j, int _k):i(_i),j(_j),k(_k){}
};



struct DancingLinks
{
    #define N 5005
    #define O 200000
    #define rp(A,i,j) for(int i=A[j];i!=j;i=A[i])
    int n, m, sz;
    int U[O],D[O],L[O],R[O], C[O], X[O];
    int S[N], H[N];
//----------
    int mp[20][20]; // 储存数独
    int vis[N];     // 判断行是否已经被覆盖
    char ch[20];
    node ijk[5000];
//----------

    void init(int _n, int _m)
    {
        mem(S,0);
        mem(H,-1);
        n= _n; m= _m;
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
    /*
        第x行 第y列元素
    */
    void build(int x, int y)
    {
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


    bool dfs(int k)
    {
        if(!R[0]) // 找到解了
        {
            output();
            return 1;
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
            de_row(X[i]);
            if(dfs(k+1))    return 1;
            rp(L,j,i)
                resume(C[j]);
        }
        resume(c);
        return 0;
    }

//-----------------------------------
    void output()
    {
        rep(i,1,16)
        {
            rep(j,1,16)
                printf("%c", (char)mp[i][j]+'A'-1);
            LN;
        }
        puts("");
    }
    void prepro()   // 预处理
    {
        int cnt= 0;
        rep(i,1,16) rep(j,1,16) rep(k,1,16)
            ijk[++cnt]= node(i,j,k);
    }
    void de_row(int p)
    {
        mp[ijk[p].i][ijk[p].j]= ijk[p].k;
    }

    void do_xy(int i, int j, int k, int &r, int &c1, int &c2, int &c3,int &c4)
    {
        r= (i-1)*16*16+(j-1)*16+k;
        c1= (i-1)*16+k;
        c2= 16*16+(j-1)*16+k;
        c3= 16*16*2+ ((i-1)/4*4+(j-1)/4)*16+k;
        c4= 16*16*3+ (i-1)*16+j;
    }

    bool do_sudo()
    {
        int c1, c2, c3, c4,r,cnt=-1;
        mem(vis,0);

        rep(i,1,16)
        {
            if(i!=1)    scanf("%s", &ch[1]);
            rep(j,1,16)
            {
                if(ch[j]=='-')  continue;
                do_xy(i,j,ch[j]-'A'+1,r,c1,c2,c3,c4);
                build(r,c1), build(r,c2), build(r,c3), build(r,c4);
                vis[c1]= vis[c2]= vis[c3]= vis[c4]= 1;
                mp[i][j]= ch[j]-'A'+1;
            }
        }

        rep(i,1,16) rep(j,1,16) rep(k,1,16)
        {
            do_xy(i,j,k,r,c1,c2,c3,c4);
            if(vis[c1]|| vis[c2]|| vis[c3]|| vis[c4]) continue;
            build(r,c1), build(r,c2), build(r,c3), build(r,c4);
        }
        if (!dfs(0))    return 0;
        return 1;
    }

#undef N
#undef O
#undef rp(A,i,j)
};

DancingLinks dlx;
int n,m;

int main(){

    dlx.prepro();
    while(~scanf("%s", &dlx.ch[1]))
    {
        dlx.init(16*16*16,16*16*4);
        dlx.do_sudo();
    }

}
