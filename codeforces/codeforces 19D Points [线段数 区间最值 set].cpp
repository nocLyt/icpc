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
const int N= 200005;       // 点数
const int E= 200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    在 (x>=0 && y>=0)的区域内增加一些点，支持删除某一个点。然后对于一个询问(x,y), 求出(x1,y1)(x1>x,y1>x)，在保证x1最小的前提下y1最小。

    解法： 离散化x,对于每个x维护一个 set。然后再维护一个单点更新区间最值线段树，来求大于x的含有>y的的最左边的点x1
    然后在 set[x1]中二分既可。

*/

struct Question  {
	int x,y, k;
	void init() {
	    char ch[10];
		scanf("%s%d%d",ch,&x,&y);
		if(ch[0]=='a')  k=0;
		else if(ch[0]=='f') k=1;
		else k= 2;
	}
};

struct SegTree  {   //单点更新 单点查询
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define MID int mid= (l+r)>>1;
#define L(x) (x<<1)
#define R(x) (x<<1|1)
#define maxn 800000
    int mx[maxn];
    void build(int l, int r, int rt) {
        mx[rt]= -1;
        if(l==r)    return;
        MID;
        build(lson);
        build(rson);
    }
    void push_up(int rt) {
    	mx[rt]= max(mx[L(rt)], mx[R(rt)]);
    }
    void update(int x, int c, int l,int r,int rt) {
    	if(l==r) {
            mx[rt]= c;
            return;
    	}
    	MID;
    	if(x<=mid)  update(x,c,lson);
    	else update(x,c,rson);
    	push_up(rt);
    }
    int query(int x, int c, int l, int r, int rt) { //要在 [x,r]上找 >=c的 最靠左的x
        if(l==r) {
        	if(mx[rt]<c)    return -1;
        	else return l;
        }
    	MID;
    	if(mx[rt]<c)    return -1;
    	int ans= -1;
    	if(x<=mid)  ans=query(x,c,lson);
    	if(ans==-1) //左半边可能不符合，要算一下右半边.
            ans= query(x,c,rson);
        return ans;
    }

};

Question que[N];
int n,m, X[N];
SegTree st;
set<int> ss[N];

int main(){

    sf(n);  rp(i,n) { que[i].init(); X[i]= que[i].x;}   sort(X,X+n);
    m= unique(X,X+n)-X;     //返回的是数组长度
    rep(i,0,m)  CLR(ss[i]);
    st.build(1,m+1,1);

    //rp(i,m) printf("X[%d]= %d\n", i,X[i]);

    rp(i,n) {
    	int x= lower_bound(X,X+m,que[i].x)-X+1, k= que[i].k, y=que[i].y;


        int tmp= (SZ(ss[x])==0)?-1:(*(--ss[x].end()));
//        printf("k= %d  x= %d  y= %d\n", k,x,y);
//        printf("tmp= %d\n", tmp);

    	if(k==0) {
    	    if(tmp<y)
                st.update(x,y,1,m+1,1);
    	    ss[x].insert(y);

    	}else if(k==1) {
            int pos= st.query(x+1,y+1,1,m+1,1);
            if(pos==-1)
                puts("-1");
            else
                printf("%d %d\n", X[pos-1], *ss[pos].upper_bound(y) );

    	}else  {
            if(tmp==y) {
                int c;
                if(SZ(ss[x])==1)    c= -1;
                else    c= *(--(--ss[x].end()));
                st.update(x,c,1,m+1,1);
            }
            ss[x].erase(ss[x].find(y));
    	}
    }

}
