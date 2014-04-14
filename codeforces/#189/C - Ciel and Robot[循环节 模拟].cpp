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
    scanf("%d", &x);

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

// U R D L
int sx, sy, x, y, ddx, ddy, sbx, sby;
char ch[200];

bool test() {
    // 现在位置是 sbx, sby
    // 目的位置是 sx sy
    if(sbx==sx && sby==sy && ddx==0 && ddy==0) {
    	return 1;
    }
    int disx= sx- sbx, disy= sy-sby;
    if(ddx!=0 && disx/ddx>=0 && disx%ddx==0 ) {
        if(ddy!=0 && disy%ddy==0&& disy/ddy==disx/ddx) {
        	return 1;
        }else if(ddy==0&& disy==0) {
            return 1;
        }
    }
    if(ddy!=0 && disy/ddy>=0 && disy%ddy==0 ) {
        if(ddx!=0 && disx%ddx==0&& disx/ddx== disy/ddy){
            return 1;
        }else if(ddx==0 && disx==0) {
        	return 1;
        }
    }
    return 0;
}

int main() {
    // cout<<0%3<<endl;

    map<char, int>  mp;
    mp['U']= 0; mp['R']=1; mp['D']= 2; mp['L']= 3;
    sf(sx,sy);
    cin>> ch; int l= strlen(ch);
    x= y= ddx= ddy= sbx= sby= 0;
    rp(i,l) {
        int idx= mp[ch[i]];
        ddx+= dx[idx];
        ddy+= dy[idx];
    }
    // ddx ddy 是增量
//    if(ddx==0 && ddy==0) {
//    	if(sx==sy && sx==0) {
//    		puts("Yes");
//    	}else  {
//    		puts("No");
//    	}
//    	return 0;
//    }

    bool flag= 0;
    rp(i,l+1) {
        if(test()) {
        	flag= 1;
        	break;
        }
        if(i==l)    break;
        int idx= mp[ch[i]];
        sbx+= dx[idx];
        sby+= dy[idx];
    }
    if(flag)    puts("Yes");
    else puts("No");

}



