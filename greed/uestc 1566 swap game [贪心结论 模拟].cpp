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

//--------------

//--------
#define FI first
#define SE second
#define PB push_back
#define MP(a,b) make_pair(a,b)
#define VIS vector<string>
#define SZ(x) int(x.size())
#define feach(i,x) for(__typeof(x.begin()) i=x.begin();i!=x.end();++i)
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

int dx[] = {0,1,0,-1, 1, 1, -1, -1};//up Right down Left
int dy[] = {1,0,-1,0, 1, -1, 1, -1};
int sig(double x){return fabs(x-0)<EPS?0:x>0?1:-1;}
template<class T> inline void sf(T& x){
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
template<class T0, class T1> inline void sf(T0& x, T1& y) {sf(x);sf(y);}
template<class T0, class T1, class T2> inline void sf(T0& x, T1& y, T2& z) {sf(x);sf(y);sf(z);}
// mem 127, 0x7f => 2139062143 => 0x7F7F7F7F
// mem  63, 0x3f => 1061109567 => 0x3f3f3f3f
// mem 255, 0xff => -1
const int N=300055;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    我们移动R 移动B 都能得到最优解。 我这里移动R。
    把链长扩增一倍。 枚举中心点。对于一个中心，我们应该把左边多少个R向右移，右边多少个R向左移呢。
    一个贪心的前提就是：
    如果有2x+1个R， 那么就把左边 x个R向右移， 把右边x个R向左移。
    如果有2x个R， 那么就把左边 (x-1)个R向右移， 把右边x个R向左移。
    贪心我不会证，但是画画就能看出来： 如果当前解不是最优解，那么后面一定会出现最优解。。

    很明显，这种情况下，我们需要利用RB之间的关系，O(n)预处理，然后对于每个枚举中心的操作 O(1)。

    lrc[i]表示 i左边有多少个R
    lbc[i]表示 i左边有多少个B
    lm[i]表示 假设i左边的R向由移动到i为止，需要多少步。
    假设 重心为 i, 以i为重心要移动的最左边的R的位置为 lef。
    那么 lm[i]多计算了：lef左边的那些R往i移动的步数=lm[lef]+ lrc[lef]*(lbc[i]-lbc[lef])

    右边同理。
    搞定。
*/

char ch[N];

// 移动R ,跳B

int pos[N], mp[N];         // 位置上是 第几个R
LL lrc[N], lbc[N], rrc[N], rbc[N];
LL lm[N], rm[N];

LL cal(int n) {
    lrc[0]= lbc[0]= rrc[0]= rbc[0]= lrc[2*n+1]= lbc[2*n+1]= rrc[2*n+1]= rbc[2*n+1]= 0;
	rep(i,1,n)  ch[i+n]= ch[i+2*n]= ch[i];
	int nn= 0;    rep(i,0,2*n+1)    pos[i]= mp[i]= 0;
    rep(i,1,2*n)    if(ch[i]=='R')  { pos[i]=++nn; mp[nn]= i;}
    nn/= 2;
    if(nn==0 || nn==n)  return 0;
    int x= (nn-1)/2, y=nn/2;

    rep(i,1,2*n) {
    	lrc[i]= lrc[i-1];
    	lbc[i]= lbc[i-1];
    	lm[i]= lm[i-1];
    	if(ch[i]=='R')  { lrc[i]++; }
    	else { lbc[i]++; lm[i]+= lrc[i]; }
    }
    repp(i,2*n,1,-1) {
    	rrc[i]= rrc[i+1];
    	rbc[i]= rbc[i+1];
    	rm[i]= rm[i+1];
    	if(ch[i]=='R')  { rrc[i]++; }
    	else { rbc[i]++; rm[i]+= rrc[i]; }
    }

    LL ans= -1;
    rep(i,1,2*n) if(ch[i]=='R') {
        if (pos[i]-x<=0 || pos[i]+y>2*n)    continue;
    	LL lef= mp[pos[i]-x], rig= mp[pos[i]+y];
    	if (lef==0 || rig==0)  continue;
        LL tmp= lm[i]-lm[lef]- lrc[lef-1]*(lbc[i]-lbc[lef]);
        tmp+= rm[i]- rm[rig]- rrc[rig+1]*(rbc[i]-rbc[rig]);
        checkmin(ans, tmp);
    }
    return ans;
}

int main(){
    // du;

    int ica(0); isf(nca);DO(nca) {
    	scanf("%s", ch+1);
    	int n= strlen(&ch[1]);
    	printf("Case #%d: ", ++ica);
    	printf("%lld\n", cal(n));
    }

}

