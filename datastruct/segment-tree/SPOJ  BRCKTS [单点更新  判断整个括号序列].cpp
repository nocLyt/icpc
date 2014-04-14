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
const int N=100005;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;


/*
    设 (=-1  )= 1
    本来的思路是： 判断左儿子是否一直<=0， 拿个bool[]来向上传递。
    结果发现， 这个思路没法一直保证 从左向右合并时<=0 。 反例： "())(" ...

    我们应该像合并区间一样，保存一个以当前区间最左为起点的子区间的和的最大值， 只有一直保证最左最大值<=0， 才能保证括号可能成立。

*/

char ch[N];

struct Segment {
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define L(x) (rt<<1)
#define R(x) (rt<<1|1)
#define MID int m= (l+r)>>1;

	int s[N<<2];
    int lmx[N<<2];

	inline void push_up(int rt) {
        s[rt]= s[L(rt)]+ s[R(rt)];
        lmx[rt]= max(lmx[L(rt)], s[L(rt)]+lmx[R(rt)]);
	}
	void build(int l, int r, int rt) {
		s[rt]= 0;
		if(l==r)  {
            lmx[rt]= s[rt]= ch[l]=='('?-1:1;
            return;
		} MID;
        build(lson); build(rson);
        push_up(rt);
	}
	void update(int k, int l, int r, int rt) {
		if(l==r) {
			lmx[rt]= s[rt]= -s[rt];
			return;
		}   MID;
		if(k<=m)    update(k,lson);
		else    update(k,rson);
		push_up(rt);
	}


    bool ok(int l, int r, int rt) {
    	if(l==r)    return lmx[rt]<=0;
    	MID;
    	return (lmx[rt]<=0 && ok(lson));
    }

	bool check(int n) {
		return s[1]==0&& ok(1,n,1);
	}
};

Segment sg;
int n;

int main(){

    int ica(0);
    while(~scanf("%d", &n)) {
        printf("Test %d:\n", ++ica);
    	scanf("%s", &ch[1]);
    	sg.build(1,n,1);
    	isf(Q); DO(Q) {
    		isf(k);
    		if(k) {
                sg.update(k,1,n,1);
    		}else {
    			printf("%s\n", sg.check(n)?"YES":"NO");
    		}
    	}
    }

}
