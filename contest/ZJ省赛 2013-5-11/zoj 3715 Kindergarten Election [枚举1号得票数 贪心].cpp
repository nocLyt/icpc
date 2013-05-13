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
#define foreach(i,x) for(__typeof(x.begin()) i=x.begin();i!=x.end();++i)
#define ALL(x) x.begin(),x.end()
template<class T> inline void CLR(T &A) {
    A.clear();
}
#define DO(n) while(n--)
#define DO_C(n) int n____=n;while(n____--)
//----------
typedef long long LL;
inline bool insize(int c,int l,int r) {
    if (c>=l&&c<=r) return true;
    return false;
}
template<class T> inline void checkmin(T &a,T b) {
    if(a == -1 || a > b)a = b;
}
template<class T> inline void checkmax(T &a,T b) {
    if(a < b)    a = b;
}
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int ,int> II;
typedef queue<int> QI;

int dx[] = {0,1,0,-1};//up Right down Left
int dy[] = {1,0,-1,0};
int dblcmp(double x) {
    return fabs(x-0)<EPS?0:x>0?1:-1;
}
template<class T> inline void sf(T& x) {
    char c;
    int mul = 1;
    while((c = getchar()) != EOF) {
        if(c == '-')mul = -1;
        if(c >= '0' && c <= '9') {
            x = c-'0';
            break;
        }
    }
    if(c == EOF) {
        x = EOF;
        return;
    }
    while((c = getchar())) {
        if(c >= '0' && c <= '9') {
            x = (x<<1)+(x<<3)+(c-'0');
        } else break;
    }
    x *= mul;
}
template<class T0, class T1> inline void sf(T0& x, T1& y) {sf(x);sf(y);}
template<class T0, class T1, class T2> inline void sf(T0& x, T1& y, T2& z) {sf(x);sf(y);sf(z);}

// mem 127, 0x7f => 2139062143 => 0x7F7F7F7F
// mem  63, 0x3f => 1061109567 => 0x3f3f3f3f
// mem 255, 0xff => -1
const int N=505;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

int n, ans;
int fa[N], cnt[N], val[N];
VI v, p;
vector<II> piao[N];
bool vis[N];

void solve(int x) { // x表示 1号同学要精确收买多少人。
    int op= x-cnt[1];
    int sum= 0; mem(vis, 0);
    // 然后收买人。
    rep(i,2,n) {
        if(cnt[i]<x)    continue;
    	int t= cnt[i]-x+1;  //对于 *i 我要收买你 t个人
    	rp(k,t) {
    		int v= piao[i][k].SE;
    		vis[v]= 1;
    		sum+= val[v];
    		op--;
    	}
    }

    if(op<0)    return; // 不成立

    // 剩下的人就随便贪心了。  注意，给1投票的人还要打上标记
    rep(i,2,n)  if(fa[i]==1)    vis[i]=1;
    CLR(p);
    rep(i,2,n)  if(!vis[i]) p.PB(val[i]);

    sort(ALL(p));
    rp(i,op)
        sum+= p[i];

    checkmin(ans, sum);
}

bool isok() {
	rep(i,2,n)  if(cnt[i]>=cnt[1])  return 0;
	return 1;
}

int main() {

    isf(nca); DO(nca) {
        sf(n);
        mem(cnt,0);
        rep(i,2,n)  sf(fa[i]); rep(i,2,n)   sf(val[i]), ans+= val[i]; rep(i,1,n)    CLR(piao[i]);
        rep(i,2,n)  {
        	cnt[fa[i]]++;
            piao[fa[i]].PB(MP(val[i],i));
        }
        rep(i,2,n)  if(SZ(piao[i])) sort(ALL(piao[i]));

        if(isok()) {
        	puts("0");
        	continue;
        }

        rep(i,cnt[1]+1,n) {
        	solve(i);
        }

        printf("%d\n", ans);
    }

}
