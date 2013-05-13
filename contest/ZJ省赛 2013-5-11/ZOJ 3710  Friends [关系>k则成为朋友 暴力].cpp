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
const int N=20000;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

struct node  {
	double ans;
	string name;
	bool operator<(const node &b) const  {
		if(ans==b.ans)  return name<b.name;
		return ans>b.ans;
	}
};

node a[N];
int idt[N];
bool is_prime[N];
int n, m;
VI v;
map<string, int> xsai;


void solve(int id) {
    double ans= 0.0;
	cin>>a[id].name;
	string team; cin>> team;

//	cout<<"name= "<<a[id].name<<"  team="<<team<<endl;
//    cout<<"xsai  "<<xsai[team]<<endl;

	if(xsai[team]==1) ans+= 36;
	else if(xsai[team]==2)    ans+= 27;
	else if(xsai[team]==3)    ans+= 18;

    char ch[5]; scanf("%s",ch);
    if(ch[0]=='F')  ans+= 33;

    int x, y; sf(x,y);
    DO(x) {
    	isf(t);
    	if(idt[t]==1)   ans+= 2.5;
    	else if(idt[t]==2)  ans+= 1.5;
    	else  {
    		if (is_prime[t])    ans+= 1;
    		else ans+= 0.3;
    	}
    }
    CLR(v);
    DO_C(y) {
        isf(t);
    	v.PB(t);
    }
    sort(ALL(v));
    if(y>=3)    ans+= max(0.0, (double)(v[SZ(v)-3]-1200)/100) *1.5;
    a[id].ans= ans;
}




int P[N];
int Prime[N];
int PNums;
void findPrime(){
    mem(is_prime,0);

    int lim=(sqrt(N*1.0)-1)/2;
    int maxIndex=(N-1)/2;
    int n,t,k;
    for(n=1;n<lim;n++){
        if(P[n]==0){
            t=2*n+1;
            for(k=2*n*(n+1);k<=maxIndex;k+=t)
                P[k]=1;
        }
    }
    Prime[0]=2;
    PNums=1;
    for(n=1;n<maxIndex;n++){
        if(P[n]==0)
            Prime[PNums++]=2*n+1, is_prime[2*n+1]=1;
    }
}


int main() {

    findPrime();
    isf(nca);DO_C(nca) {
    	mem(idt,-1);
        sf(n,m);
        isf(R); DO(R) {
        	isf(x); idt[x]= 1;
        }
        isf(S); DO(S) {
        	isf(x); idt[x]= 2;
        }
        xsai.clear();
        isf(Q); DO(Q) {
            string str; int x;
            cin>> str; sf(x);
        	xsai[str]= x;
        }

        rep(i,1,n)
            solve(i);
        sort(a+1,a+1+n);
        rep(i,1,m){
            cout<<a[i].name;printf(" %.3lf\n", a[i].ans);
        }

    }

}
