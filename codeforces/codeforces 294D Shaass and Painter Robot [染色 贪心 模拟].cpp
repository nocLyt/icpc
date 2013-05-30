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
template<class T0, class T1> inline void sf(T0& x, T1& y) {sf(x);sf(y);}
template<class T0, class T1, class T2> inline void sf(T0& x, T1& y, T2& z) {sf(x);sf(y);sf(z);}
// mem 127, 0x7f => 2139062143 => 0x7F7F7F7F
// mem  63, 0x3f => 1061109567 => 0x3f3f3f3f
// mem 255, 0xff => -1
const int N=400005;       // 点数
const int E=20055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

/*
    xiaodao: "容易想到一个结论。。。只要所有边界格子都被染色。。那么所有格子就已经被染色。。。必要性显然。。充分性可以对格子归纳得到。。"

    那么， 无解的情况就是一个格子走了好多次。。。唔。。我设的>3次。
    那么就是个模拟了。。

*/

int n,m, sx, sy, flag;
LL ans;
char op[5];
map<II,int> mp;

void change(char *op) {
    if(op[0]=='U'&& sx==1)  op[0]='D';
    if(op[0]=='D'&& sx==n)  op[0]='U';
    if(op[1]=='L'&& sy==1)  op[1]='R';
    if(op[1]=='R'&& sy==m)  op[1]='L';
}

bool go() {
    II p= MP(sx,sy);
    if ( sx==1||sx==n || sy==1 ||sy==m ) {
        int c= ++mp[p];
        if (c==1)   flag--;
        else if(c>3)    { flag= -1; return 0;}
        if(!flag)   return 1;
    }

    int s1= op[0]=='U'?sx-1:n-sx;
    int s2= op[1]=='L'?sy-1:m-sy;
    int s= min(s1,s2);

    ans+= (LL)s;
    sx+= op[0]=='U'?-s:s;
    sy+= op[1]=='L'?-s:s;

    return 1;
}

LL Run() {
	while(flag>0) {
	    if (!go()) break;
        change(op);
	}
    if(!flag)   return ans;
    return -1;
}


int main(){

    sf(n,m); sf(sx,sy); scanf("%s", op);
    ans=1; flag= 0;
    CLR(mp);
    rep(i,1,m)  { if((i+1)%2==0) flag++; if((i+n)%2==0) flag++;}
    rep(i,2,n-1)  { if((i+1)%2==0) flag++; if((i+m)%2==0) flag++;}

    cout<<Run()<<endl;
}
