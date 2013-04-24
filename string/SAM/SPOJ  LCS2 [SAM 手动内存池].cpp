
/*
    数组模拟内存池的 后缀自动机。

    求n(<10）个串的 最长公共连续子串
    解法： 先对一个串建后缀自动机。 然后拿每个串在自动机上匹配，求出来每个串对每个状态的最大匹配长度；
    结果就是 所有状态中对于每个串最大匹配长度最小值的最大值 =。=

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

const int N=105;       // 点数
const int E=200555;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;


struct State
{
    State *suf, *go[26], *next; //next 前式链向星
    int val;
    //---
    int len[10];
    //---
    State() : suf(0), next(0)
    {
        mem(len,0);
        mem(go,0);
    }
};

struct SuffixAuto
{
    #define LENPOOL 1000010
    State statePool[LENPOOL], *cur;
    State *firstVal[LENPOOL];   // 像 前式链向星那样储存
    State *root, *last;
    //----
    char str[LENPOOL];
    //----
    State* newState(int _val)   // 从内存池中分配结点
    {
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

    void solve()
    {
        init();
        //-----第一个串加入自动机
        scanf("%s", str);
        int L= strlen(str);
        for(char *pt=str; *pt; pt++)
            extend(*pt-'a');
        //----其余的串，依次在自动机上比较，记录对应的 到达每个状态的最大长度
        int id;
        for(id=0;scanf("%s",str)!=EOF;id++)
        {

            int l= 0;
            State *p= root;
            for(char *pt=str;*pt;pt++)
            {
                int w= *pt-'a';
                for(; p&& !p->go[w]; p=p->suf, l=p?p->val:0) ;
                if(!p)
                    p= root, l= 0;
                else
                    p= p->go[w], checkmax(p->len[id], ++l);
            }
        }
        //----更新对应的长度，min(str[id][s]) 表示id个串，在状态s上最大的匹配长度的最小值 max( min(str[id][s]) );
        int ans= 0;

        for(int i=L;i>=0;i--)
        {
            for(State *p=firstVal[i];p;p=p->next)
            {
                int ret= p->val;
                rep(j,0,id-1)
                {
                    checkmin(ret, p->len[j]);
                    if(p->suf)  // 这个就相当于 AC自动机DP时从失败指针传标记
                        checkmax(p->suf->len[j], p->len[j]);
                }
                checkmax(ans, ret);
            }
        }

        printf("%d\n", ans);
        return ;
    }

};

SuffixAuto sa;

int main(){

    sa.solve();

}





