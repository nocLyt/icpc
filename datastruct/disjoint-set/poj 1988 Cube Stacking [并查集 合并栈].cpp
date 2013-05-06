
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
#define foreach(i,x) for(__typeof(x.begin()) i=x.begin();i!=x.end();++i)
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
template<class T> inline void checkmin(T &a,T b){if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b){if(a < b)    a = b;}
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
    while((c = getchar()))
    {
        if(c >= '0' && c <= '9')
        {
            x = (x<<1)+(x<<3)+(c-'0');
        }
        else break;
    }
    x *= mul;
}

const int N=100010;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    储存 栈顶节点下有多少节点(不包括栈顶)   cnt[]
    储存 当前节点到栈顶有多少节点 up[]

*/

int fa[N], cnt[N], up[N];

void init()
{
    rep(i,1,30000)
    {
        fa[i]= i;
        cnt[i]= 0;
        up[i]= 0;
    }
}
int find(int x)
{
    if(fa[x]==x)    return x;
    int p= find(fa[x]);
    up[x]+= up[fa[x]];
    return fa[x]= p;
}

void unionf(int x, int y)   // fax放到 fay上
{
    int fax= find(x);
    int fay= find(y);
    up[fay]+= cnt[fax]+1;
    cnt[fax]+= cnt[fay]+1;
    fa[fay]= fax;
}


int n;

int main()
{
    while(~scanf("%d", &n))
    {
        init();
        char op[5];
        int x, y;
        while(n--)
        {
            scanf("%s", op);
            if(op[0]=='M')
            {
                scanf("%d%d", &x,&y);
                unionf(x, y);
            }
            else
            {
                scanf("%d", &x);
                int fax= find(x);
                printf("%d\n", cnt[fax]-up[x]);

            }

        }

    }

}
