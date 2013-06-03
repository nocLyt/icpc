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
template<class T0, class T1,class T2> inline void sf(T0& x, T1& y, T2& z) {sf(x);sf(y);sf(z);}
template<class T0, class T1> inline void sf(T0& x, T1& y) {sf(x);sf(y);}
typedef long long LL;

const int N=100005;       // 点数
const int INF= 0x3f3f3f3f;

/*
    max(sum)<= 10^8 , 最多六次连续平方根, 就变成1了。
    这就是入手点。
    对于平方根，我们暴力更新，每个点最多更新 六次。
    然后如果区间全部是1， 那么就不必再开根了， 直接输出区间长度。
    最大值线段树来判断一个区间是否全1。
*/

struct Segment {
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define L(x) (x<<1)
#define R(x) (x<<1|1)
#define MID int m=(l+r)>>1

	LL mx[N<<2], sum[N<<2];
	void push_up(int rt) {
		mx[rt]= max(mx[L(rt)], mx[R(rt)]);
		sum[rt]= sum[L(rt)]+ sum[R(rt)];
	}
	void build(int l, int r, int rt) {
		if(l==r) {
			sf(mx[rt]);     sum[rt]= mx[rt];
			return;
		}  MID;
		build(lson); build(rson);
		push_up(rt);
	}
	LL query(int L, int R, int l, int r, int rt) {
		if(L<=l && r<=R) {
			return sum[rt];
		} MID;
		LL ans=0;
		if(L<=m)    ans+= query(L,R,lson);
		if(m<R)     ans+= query(L,R,rson);
		return ans;
	}
	void update(int L, int R, int l, int r, int rt) {
		if(L<=l && r<=R&& mx[rt]==1 )   return;
        if(l==r) {
            if(mx[rt]==1)  return;
            mx[rt]= sum[rt]= sqrt(sum[rt]*1.0);
            // printf("l= %d    %lld\n", l, sum[rt]);
            return;
        }   MID;
        if(L<=m)    update(L,R,lson);
        if(m<R)     update(L,R,rson);
        push_up(rt);
	}

};

int n;
Segment sg;

int main(){
    // freopen("in.txt","r",stdin);

    int ica(0);
    while(~scanf("%d", &n)) {
        printf("Case #%d:\n", ++ica);
    	sg.build(1,n,1);
        isf(Q); DO(Q) {
        	int k,l,r; sf(k,l,r);

        	if(l>r) swap(l,r); //!! 存在，L>R的情况。。

        	if(k) {
        		printf("%lld\n", sg.query(l,r,1,n,1));
        	}else  {
        		sg.update(l,r,1,n,1);
        	}
        }

    	puts("");
    }

}



