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

const int N=100005;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

struct State
{
    /* go[0] 表示是否连接结尾. 最小标号从 1开始 */
#define CSON 27
    State *go[CSON],  *par;
    int val;    //  表示可以接收的最大长度的串
    int id;     //
    static int ids;
    //-------
    int cnt;
    int cs[CSON]; // cnt表示从该节点到根的路径数 cs[i]表示儿子i的路径数
    //-----
    State(int _val): par(0), val(_val), cnt(0)
    {
        id= ids++;
        mem(go,0);
        mem(cs,0);
    }
};
int State::ids= 0;

struct SuffixAutomaton
{
/* go[0] 表示是否连接结尾.  最小标号从1开始，最后再插入 '\0' 节点*/
/* 这会导致 root 直接连接 '\0'节点， 重置一下 root->go[0]= 0*/
#define cal(s) (s-'a'+1)
    State *root, *last;
    int n;  // 模板串的长度
    void init()
    {
        root= new State(0);
        last= root;
        n= 0;
    }
    void insert(int w)
    {
        State *p= last, *np= new State(last->val+1);
        for(;p && p->go[w]==0; p=p->par)
            p->go[w]= np;
        if(p==0)
            np->par= root;
        else
        {

            State *q= p->go[w];
            if(p->val+1==q->val)
                np->par= q;
            else {
                State *nq= new State(p->val+1);
                memcpy(nq->go,q->go,sizeof(q->go));
                q->par= np->par= nq;
                nq->par= p;
                for(;p&&p->go[w]==q;p=p->par)
                    p->go[w]= nq;
            }
        }
        last= np;

    }
    int dfs(State *p)
    {
        if(p->val>n)   return 1;   // '\0'节点
        if(p->cnt!=0)   return p->cnt;

        rep(i,0,CSON-1)
        {
            if(p->go[i]==0) continue;
            p->cs[i]= dfs(p->go[i]);
            p->cnt+= p->cs[i];
        }
        return p->cnt;
    }

    void build(char *pat)
    {
        init();
        for(int i=0;pat[i];i++, n++)
            insert(cal(pat[i]));
        insert(0); // 最后插入 '\0'
        root->go[0]= 0; // del root -> '\0'

        dfs(root);
    }

    bool query(char *text)  // 查询是否是子串
    {
        State *p= root;
        for(int i=0;text[i];i++)
        {
            int idx= cal(text[i]);
            if(p->go[idx]==0)
                return false;
            p= p->go[idx];
        }
        return true;
    }



#undef cal
};

SuffixAutomaton sa;
char tmp[100], pat[100];


int main(){

    scanf("%s", pat);
    sa.build(pat);


}
