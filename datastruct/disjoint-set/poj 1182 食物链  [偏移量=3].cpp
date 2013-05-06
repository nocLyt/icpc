
/*

        0 ： x 与 fa[x] 同类
        1 :  x 被 fa[x] 吃
        2 ： x 吃 fa[x]

        向量运算！！
        举个例子吧：

         0   1   2              (0+1+2)%3= 0
        x-->y-->z-->root  ==》 x-->root
        说明 x和root 是同类！

        如果

        x-->fx , x-->y , y--> fy

        那么 fx 和 fy的关系怎么确定呢~！ 嘿嘿  x-->fx 反过来就行啦。

        好东西，　自己一定用手画一下！
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <bitset>
using namespace std;
#define sqr(x) ((x)*(x))
#define two(x)            ((LL)1<<(x))
#define include(a,b)        (((a)&(b))==(b))
#define L(x) ((x)<<1)
#define R(x) ((x)<<1|1)
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define MID ((l+r)>>1)
#define BUG1 puts("BUG11\n")
#define BUG2 puts("BUG22\n")
#define LgLg int
#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a>b?b:a)
#define FOR(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define FF(i,a) for(int i=0;i<a;i++)
#define FD(i,a,b) for(int i=a;i>=b;i--)
#define STOP  system("pause")
#define PD(x) printf("%d",(x))
#define PP printf(" ")
#define SD(x) scanf("%d", &(x))
#define SF(x) scanf("%lf", &(x))
#define SS(x) scanf("%s", &(x))
#define SET(x,y) memset(x,y,sizeof(x))
#define LN printf("\n");
#define SWAP(a,b) a=a xor b;b= a xor b;a=a xor b;
#define INF 0x7FFFFFFF
#define PI acos(-1.0)
#define LL __int64
#define du freopen("in.txt","r",stdin)
#define chu freopen("out.txt","w",stdout)
#define US freopen("buylow.in","r",stdin)
#define ACO freopen("buylow.out","w",stdout)
#define EPS 1e-6
int inSize(int c,int x, int y) {if (c>=x && c<=y) return true; return false;}
int dx[]= {-1,0,1,0};//up Right down Left
int dy[]= {0,1,0,-1};
//int wx[]= {0,1,-1,1,-1,0,1,-1};
//int wy[]= {1,1,1,0,0,-1,-1,-1};
//int tx[]= {-1,-2,-2,-1,1,2,2,1};
//int ty[]= {2,1,-1,-2,-2,-1,1,2};
typedef pair<int, int> II;
const int maxn= 50005;

int n, K, ans;
int fa[maxn], rank[maxn];


int findSet(int x){
    if (fa[x]==x)   return x;

    int tmp= fa[x];
    fa[x]= findSet(fa[x]);
    rank[x]= (rank[x]+rank[tmp])%3;

    return fa[x];
}

void unionSet(int x, int y, int r){

    int fx= findSet(x);
    int fy= findSet(y);
    if (fx==fy) return;

    int tmp= 0;
    if (rank[x]==2) tmp= 1;
    else if (rank[x]==1) tmp= 2;

    rank[fx]= (tmp+r+rank[y])%3;
    fa[fx]= fy;

}

bool isTrue(int x, int y , int r){

    int fx= findSet(x);
    int fy= findSet(y);

    if (fx!= fy)    return true;

    int tmp= 0;
    if (rank[y]== 1) tmp= 2;
    else if (rank[y]==2)    tmp= 1;

    int tmp2= (tmp+rank[x])%3;
    if (tmp2==r)    return true;
    return false;

}

int main(){
    SD(n); SD(K);
    FOR(i,0,n){
        rank[i]= 0;
        fa[i]= i;
    }
    ans= 0;
    while(K--){
        int d, x, y;
        scanf("%d%d%d",&d,&x,&y);
        int r= d==1?0:2;

        if (x>n || y>n ||(r==2 && x==y))    ans++;
        else if (isTrue(x,y,r))  unionSet(x,y,r);
        else    ans++;

    }

    printf("%d\n",ans);

    return 0;
}
