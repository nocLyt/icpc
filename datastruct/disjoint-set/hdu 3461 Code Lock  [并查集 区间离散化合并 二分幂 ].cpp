//#pragma comment(linker, "/STACK:102400000,102400000")

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
#define rep(i,a,b)  for(int (i)=(a);(i)<=(b);(i)++)
#define rp(i,n) for(int i=0;i<n;i++)
#define repp(i,a,b,c) for(int i=a;(c>0)?(i<=b):(i>=b);i+=c)
#define isf(x) int x;sf(x);
#define STOP  system("pause")
#define PP printf(" ")
#define mem(x,y) memset(x,y,sizeof(x))
#define LN printf("\n");
#define du freopen("in.txt","r",stdin)
#define chu freopen("out.txt","w",stdout)
#define EPS 1e-8
#define MOD 1000000007
//--------------

//--------
#define FI first
#define SE second
#define PB push_back
#define MP(a,b) make_pair(a,b)
#define VIS vector<string>
#define SZ(x) int(x.size())
#define foreach(i,x) for(__typeof(x.begin()) i=x.begin();i!=x.end();++i)
#define ALL(x) x.begin(),x.end()
template<class T> inline void CLR(T &A) {A.clear();}
#define DO(n) while(n--)
#define DO_C(n) int n____=n;while(n____--)
//----------
typedef long long LL;
inline bool insize(int c,int l,int r){if (c>=l&&c<=r) return true; return false;}
template<class T> inline void checkmin(T &a,T b){if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b){if(a < b)    a = b;}
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int ,int> II;
typedef queue<int> QI;

int dx[] = {0,1,0,-1};//up Right down Left
int dy[] = {1,0,-1,0};
int dblcmp(double x){return fabs(x-0)<EPS?0:x>0?1:-1;}
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
template<class T0, class T1> inline void sf(T0& x, T1& y){sf(x);sf(y);}
// mem 127, 0x7f => 2139062143 => 0x7F7F7F7F
// mem  63, 0x3f => 1061109567 => 0x3f3f3f3f
// mem 255, 0xff => -1
const int N=10000005;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;


/*
【题目大意】
题意是说有N个字母组成的密码锁， 如【wersdfj】,   每一位上的字母可以转动， w可转动变成x， z变成a。但是题目规定， 只能同时转动某个区间上的所有字母， 如【1，3】， 那么第1到第3个的所有字母要同时转动，那么【 wersdfj 】经过一次操作就变成 【 xfssdfj 】.    一共有M 个区间是可以操作的。
题目还规定：If a lock can change to another after a sequence of operations, we regard them as same lock.
就是说， 经过可操作区间进行的操作得到的所有锁情况，都是同一个的。 也就是说，所有不同的锁就是“不可操作区间”的所有组合情况。

【思路】
    这样来看，当我们确定第一个区间，我们可以看作这个区间有一块转轮是“任意转”的(虽然其他转轮跟着它转，但我们认为其他转轮是不转的)
    然后再确定区间时，有可能下一个区间没法再产生一个“任意转”的转轮了， 比如和之前的区间重叠了。
    判断区间是否重叠： 并查集。
    区间重叠要注意： [1,3],[3,5],[1,5] 可以产生三个任意转的转轮。当合并 [1,3],[3,5]后，对于[1,5]可以导致2号转轮或者4号转成为任意转的转轮。
    和线段数离散化差不多的思想, 对于区间[L,R] 我们使L--, => [L-1,R]

    对于n个转轮，有26^n个排列。 我们只需要统计 "任意转"的转轮为x， 结果就是 26^(n-x)

*/

int n, m;
int fa[N];
void init()
{
    rep(i,0,n)
        fa[i]= i;
}
int find(int x)
{
    if(fa[x]==x)    return x;
    return fa[x]= find(fa[x]);
}
bool unionf(int x, int y)
{
    int fx= find(x), fy=find(y);
    if(fx==fy)  return 0;
    fa[fx]= fy;
    return 1;
}

LL solve(int n,int m)   //n^m  Bin
{
    LL sum= 1;
    for(LL p=n;m;m>>=1)
    {
        if(m&1) sum= (sum*p)%MOD;
        p*= p; p%= MOD;

    }
    return sum;
}

int main()
{


    while(~scanf("%d%d", &n,&m))
    {
        init();
        int cnt= 0;
        DO(m)
        {
            int x, y;
            sf(x,y); x--;
            if(unionf(x,y))
                cnt++;
        }
        cout<<solve(26,n-cnt)<<endl;

    }


}

