/*
    题意：给一个字符串S，令F(x)表示S的所有长度为x的子串中，出现次数的最大值。求F(1)..F(Length(S))

    根据字符串S建SAM。  
    SAM上的每个状态到last的一条路经就代表S的一个子串，
    每个状态都有一个val值，表示这个状态所能表示的最长子串的长度。
    则题目就是：求出每个val上对应状态中最大的路径数。

    PS: 看到 dp[val]=max(dp[val],dp[val+1]) 我感觉这是没必要的，假设长度为val+1的子串出现n次，那么长度为val的子串出现的次数必然不会少于n次。

*/

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

const int N=1000010;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;


struct State
{
    State *suf, *go[26], *next; //next 前式链向星
    int val;
    //---
    int cnt;    // 表示该节点代表的子串，出现的次数
    //---
    State() : suf(0), next(0), cnt(0)
    {
        mem(go,0);
    }
};

struct SuffixAuto
{
    #define LENPOOL 1000010
    #define MAXN 1000010
    State statePool[LENPOOL], *cur;
    State *firstVal[LENPOOL];   // 像 前式链向星那样储存
    State *root, *last;
    //----

    int dp[MAXN];
    //----
    State* newState(int _val)   // 从内存池中分配结点
    {
        cur->cnt= 0;
        cur->suf= 0;
        mem(cur->go,0);
        cur->val= _val;
        cur->next= firstVal[_val];
        firstVal[_val]= cur;
        return cur++;
    }
    void init() // 初始化，内存池，首尾结点
    {
        cur= statePool;
        root= last= newState(0);
    }
    void extend(int w)  // 插入一个结点
    {
        State *p= last;
        State *np= newState(p->val+1);
        for(;p&&!p->go[w];p=p->suf)
            p->go[w]= np;
        if(!p)
            np->suf= root;
        else
        {
            State *q= p->go[w];
            if(p->val +1== q->val)
                np->suf= q;
            else
            {
                State *nq= newState(p->val+1);
                memcpy(nq->go, q->go,sizeof q->go);
                nq->suf = q->suf;
                q->suf= np->suf= nq;
                for(;p&&p->go[w]==q;p=p->suf)
                    p->go[w]= nq;
            }
        }
        last= np;
    }
    bool query(char *str)   // 查询是否是子串
    {
        State *p= root;
        for(int i=0;str[i];i++)
        {
            int w= str[i]-'a';
            if(!p->go[w])
                return 0;
            p= p->go[w];
        }
        return 1;
    }

    void solve(char *str)
    {
        int L= strlen(str);
        init();
        rep(i,0,L-1)
            extend(str[i]-'a');

        State* p= root;
        rep(i,0,L-1)    // 顺着路径，把路过的状态路径数+1.
            (p=p->go[str[i]-'a'])->cnt++;

        mem(dp,0);
        for(int i=L;i>=0;i--)
        {
            for(State *p=firstVal[i];p;p=p->next)
            {
                checkmax(dp[i], p->cnt);
                if(p->suf)
                    p->suf->cnt+= p->cnt;
            }

        }
        rep(i,1,L)
            printf("%d\n", dp[i]);

    }

};

SuffixAuto sa;
char str[N];

int main(){

    scanf("%s", str);
    sa.solve(str);

}





