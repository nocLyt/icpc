#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

#define isf(x) int x;sf(x);

#define DO(n) while(n--)
//----------
template<class T> inline void checkmax(T &a,T b){if(a < b)    a = b;}

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
const int N=50005;       // 点数
const int INF= 0x3f3f3f3f;


/*
    线段树操作连续的区间。 要考虑 从区间最左开始， 从区间最右开始，和该区间的两个子区间合并处。

    在查询的时候，发现没法保证合并两个子区时也维护性质。
    这时候需要一个量， 来保存已经查询过的子区间的从最右开始往左的最大连续子序列和。(因为查询是从左向右遍历区间的)

*/

struct Segment {
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define L(x) (x<<1)
#define R(x) (x<<1|1)
#define MID int m=(l+r)>>1
    int sum[N<<2], lmx[N<<2], rmx[N<<2], mx[N<<2];

    static int wtf; // query() 时来保存查询过的子区间的从最右往左的最大连续子序列和。

    void push_up(int rt) {
        //区间和
        sum[rt]= sum[L(rt)]+ sum[R(rt)];

        mx[rt]= mx[L(rt)];      // 忘传左右儿子的mx[] 而WA了。
        checkmax(mx[rt], mx[R(rt)]);
        checkmax(mx[rt], rmx[L(rt)]+ lmx[R(rt)]);
        // do: lmx
        lmx[rt]= lmx[L(rt)];
        checkmax(lmx[rt], sum[L(rt)]+lmx[R(rt)]);
        checkmax(mx[rt], lmx[rt]);
        // do: rmx
        rmx[rt]= rmx[R(rt)];
        checkmax(rmx[rt], rmx[L(rt)]+ sum[R(rt)]);
        checkmax(mx[rt], rmx[rt]);
        // over
    }

    void build(int l, int r, int rt) {
        lmx[rt]= rmx[rt]= mx[rt]= -INF;
        if(l==r) {
        	sf(sum[rt]); lmx[rt]= rmx[rt]= mx[rt]= sum[rt];
        	return;
        }   MID;
        build(lson); build(rson);
        push_up(rt);
    }

    int query(int L, int R, int l, int r, int rt) {
    	if(L<=l && r<=R) {
    		int ans= max(mx[rt], wtf+lmx[rt]);
    		wtf= max(rmx[rt], wtf+sum[rt]);
    		return ans;
    	} MID;
    	int ans= -INF;
    	if(L<=m)    checkmax(ans, query(L,R,lson));
    	if(m<R)     checkmax(ans, query(L,R,rson));

    	return ans;
    }

};

Segment sg;
int n;
int Segment::wtf=0;


int main(){
    sf(n); sg.build(1,n,1);
    isf(Q); DO(Q) {
        int l, r; sf(l,r);
        Segment::wtf= 0;
        printf("%d\n", sg.query(l,r,1,n,1));
    }

}



