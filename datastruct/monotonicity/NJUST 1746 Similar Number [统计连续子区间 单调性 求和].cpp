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
#define EPS 1e-9

//--------------
//
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

int dx[] = {0,1,0,-1, 1, 1, -1, -1};//up Right down Left
int dy[] = {1,0,-1,0, 1, -1, 1, -1};
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
const int N=100005;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    利用 单调性来二分。

    又是这种 对于一个区间，问有多少连续的子区间满足balabala的性质。
    2013GCJ R1C的A题也是这类问题。
    这类问题有个明显的特点：固定左端点后，依次增加右端点，会有一个终止点，使终止点左右是不同的状态。并且向右会一直满足这个状态。
    这样的话， 我们只需要考虑 左端点和终止点。。。。balabala....

    首先预处理出对于每个数，右邻的相似数的位置 r[i]： 方法是，把字符串sort()一下(一个string也可sort @_@)，用map映射下。
    然后对于点i，求出右边最近的位置one[i], 使[i,j]包含一个相似对。
    右边最近的意思就是： [i,one[i]-1] 不包含相似对， [i,one[i]]包含, [i,one[i]] ... [i,n]都最少包含一个相似对。
    这也就是上面所说的"终止点"。
    然后对于点i, 求出右边最近的位置two[i]， 区间[i,two[i]]恰好包含两个相似对。
    很容易发现, one[i] two[i] 满足单调不减的性质。

    对于one[i] 和 two[i]的：
    one[i]= min(one[i+1], r[i])
    two[i]= min(two[i+1],  r[r[i]], max(one[i+1], r[i]) );

    对于查询：
    for(int i=l;i<=r;i++)  if(one[i]<=r)   sum+=r-one[i]+1;
    for(int i=l;i<=r;i++)  if(two[i]<=r)    sum-=r-two[i]+1;
    这样的话 求区间和， 对于r二分就出来了。

*/

LL r[N], n, m, a[N];
map<string, int> mp;
LL one[N], two[N];
LL sone[N], stwo[N];

int main(){

    while(~scanf("%lld%lld",&n,&m)) {
        mp.clear();
    	rep(i,1,n)  sf(a[i]);
    	repp(i,n,1,-1) {
    		int x= a[i];
    		string s= "";
    		for(;x;x/=10)   s+= (char)(x%10+'0');
    		sort(ALL(s));
    		if(mp.find(s)==mp.end())
                r[i]= n+1;
            else
                r[i]= mp[s];
            mp[s]= i;
    	}
    	// rep(i,1,n)  printf("%lld ", r[i]); LN;
        r[n+1]= one[n+1]= two[n+1]= n+1;
    	repp(i,n,1,-1) {
    		one[i]= min(one[i+1], r[i]);
            two[i]= min(two[i+1], r[r[i]]);
            two[i]= min(two[i], max(r[i], one[i+1]));
    	}

//    	rep(i,1,n)
//    		printf("i=%d  one= %lld  two= %lld\n",i, one[i], two[i]);

    	sone[0]= stwo[0]= 0;
    	rep(i,1,n+1) {
    		sone[i]= sone[i-1]+ one[i];
    		stwo[i]= stwo[i-1]+ two[i];
    	}

//    	rep(i,1,n)
//            printf("i=%d  sone=%lld   stwo= %lld\n",i,sone[i], stwo[i]);

    	LL last=0;
    	DO(m) {
    	    LL l, r, sum;
    		sf(l,r);
    		l+= last; r-=last;
    		int t= upper_bound(one+l, one+r, r)- one- 1;
            sum= (t-l+1)*(r+1)-(sone[t]-sone[l-1]);
            t= upper_bound(two+l, two+r, r)- two- 1;
            sum-= (t-l+1)*(r+1)-(stwo[t]-stwo[l-1]);
            printf("%lld\n", sum);
            // printf("l= %lld  r= %lld %lld\n", l, r, sum);
            last= sum;
    	}

    }

}
