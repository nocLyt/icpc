/*
    经典 LCS问题
    对于A 串建SAM， 然后 B串在A的SAM中转移， 匹配不动则按suf向上转移。 过程中更新长度，并记录最大值
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
    State *suf, *go[26], *next;
    int val;
    State(): suf(0), next(0), val(0)
    {
        mem(go,0);
    }
};


struct SuffixAuto
{
    #define LENPOOL 1000010
    State statePool[LENPOOL], *cur;
    State *firstVal[LENPOOL];
    State *root, *last;
    State *newState(int _val)
    {
        cur->suf= 0;
        mem(cur->go,0);
        cur->val= _val;
        cur->next= firstVal[_val];
        firstVal[_val]= cur;
        return cur++;
    }
    void init()
    {
        cur= statePool;
        root= last= newState(0);
    }
    void extend(int w)
    {
        State *p= last;
        State *np= newState(p->val+1);
        for(;p&& !p->go[w];p=p->suf)
            p->go[w]= np;
        if(!p)
            np->suf= root;
        else
        {
            State *q= p->go[w];
            if(p->val+1==q->val)
                np->suf= q;
            else
            {
                State *nq= newState(p->val+1);
                memcpy(nq->go, q->go, sizeof q->go);
                nq->suf= q->suf;
                q->suf= np->suf= nq;
                for(;p&&p->go[w]==q;p=p->suf)
                    p->go[w]= nq;
            }
        }
        last= np;
    }

    void solve(char *str)
    {
        init();
        int L= strlen(str);
        rep(i,0,L-1)
            extend(str[i]-'a');

        scanf("%s", str);
        State *p= root;
        int l= 0, ans= 0;
        for(char *pt=str;*pt;pt++)
        {
            int w= *pt-'a';
            for(;p&& !p->go[w]; p=p->suf, l=p?p->val:0)  ;
            if(!p)
                p=root, l= 0;
            else
                p=p->go[w], checkmax(ans, ++l);

        }

        printf("%d\n", ans);
    }

};

SuffixAuto sa;
char str[N];

int main(){
    scanf("%s", str);
    sa.solve(str);

}





