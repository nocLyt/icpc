#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <vector>
#include <bitset>
#include <cstdio>
#include <string>
#include <numeric>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long  ll;
typedef unsigned long long ull;

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};//up down left right
bool inmap(int x,int y,int n,int m){if(x<1||x>n||y<1||y>m)return false;return true;}
int hashmap(int x,int y,int m){return (x-1)*m+y;}

#define eps 1e-8
#define inf 0x7fffffff
#define debug puts("BUG")
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define read freopen("in.txt","r",stdin)
#define write freopen("out.txt","w",stdout)
#define maxn 205
bool vis[maxn];
int d[5]={0,-1,1};
int num[5];
void cal(int dep,int ans)
{
    if(dep==3)
    {
        vis[abs(ans)]=1;
        return ;
    }
    for(int i=0;i<3;++i)
        cal(dep+1,ans+num[dep]*d[i]);
}
int main()
{
    //read;
    int cas,a,b;
    scanf("%d",&cas);
    while(cas--)
    {
        scanf("%d%d",&a,&b);
        int ans=0;
        for(int i=1;i<a;++i)
        {
            int t1=i,t2=a-i,t3=b;
            num[0]=t1,num[1]=t2,num[2]=t3;
            memset(vis,0,sizeof(vis));
            cal(0,0);int tot=0;
            for(int i=1;i<maxn;++i)
                tot+=vis[i];
            ans=max(ans,tot);
        }
        for(int i=1;i<b;++i)
        {
            int t1=i,t2=b-i,t3=a;
            num[0]=t1,num[1]=t2,num[2]=t3;
            memset(vis,0,sizeof(vis));
            cal(0,0);int tot=0;
            for(int i=1;i<maxn;++i)
                tot+=vis[i];
            ans=max(ans,tot);
        }
        printf("%d\n",ans);
    }
    return 0;
}
