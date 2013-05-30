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
const int N=1000005;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;


/*

学习： http://blog.sina.com.cn/s/blog_70811e1a01014esn.html

    首'(' 尾')' 和中间'#' 都插入不同的字符
    性质： str[i]='#' if i%2==0
*/
struct Manacher {
    char str[N];    //插入处理字符串
    int r[N];
    void init(char *ss) {
        int l= strlen(ss);
        rp(i,l) {
        	str[(i<<1)+1]= ss[i];
        	str[(i<<1)+2]= '#';
        }
        str[0]= '('; str[l<<1]= ')'; str[l<<1|1]=0;
    }
    void cal(char *ss) {// ss为原字符串
        int ans=-1, head=-1;    //回文串长度ans, 起点head
        for(int i=1;str[i]!=')';i++){
            int t= (r[i]+(i%2))/2;
            int m= i/2;
            int l= m-t+(i%2);
            int r= m+t- 1;
            if((r-l+1)>ans) {
            	ans= r-l+1;
            	head= l;
            }
        }
        for(int i=head;ans;ans--,i++)
            printf("%c", ss[i]);
        puts("");
    }
    void manacher(char *ss) {
        init(ss);
        int l= strlen(str);  rp(i,l)r[i]= 1;
        // i表示 处理到哪里了,  str[i-j+1..i+j-1]是回文串
        for(int i=1,j=r[1],k; i<l; i+=k,j=max(r[i],j-k)) {
            for(;str[i-j]==str[i+j];j++)    ;
            r[i]= j;
            for(k=1;k<j&& r[i]-k!=r[i-k]; k++) r[i+k]=min(r[i]-k, r[i-k]);
        }
        cal(ss);
    }
};

Manacher ma;
char str[N];

int main(){
    // du;
    while(~scanf("%s", str)) {
        ma.manacher(str);
    }


}
