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
int main()
{
    //read;
    int cas;
    cin>>cas;
    ll a,b,c;
    while(cas--)
    {
        cin>>a>>b>>c;
        ll t1=(2*a-1+1)*a/2;
        ll t2=(2*a+1+2*(a+b-1)+1)*b/2;
        ll t3=(2*(a+b)+1+2*(a+b+c-1)+1)*c/2;
        swap(a,c);
        cout<<t1*300+t2*100+t3*50<<" ";
        t1=(2*a-1+1)*a/2;
        t2=(2*a+1+2*(a+b-1)+1)*b/2;
        t3=(2*(a+b)+1+2*(a+b+c-1)+1)*c/2;
        cout<<t1*50+t2*100+t3*300<<endl;
    }
}
