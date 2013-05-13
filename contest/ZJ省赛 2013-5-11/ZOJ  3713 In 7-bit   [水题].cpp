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
#define maxn 3000005
string ss;
void gao(int len)
{
    while(len)
    {
        int t=len&0X7f;
        len>>=7;
        if(len)t|=0X80;
        printf("%02X",t);
    }
}
int main()
{
    //read;
    int cas;
    scanf("%d",&cas);
    getchar();
    while(cas--)
    {
        getline(cin,ss);
        int len=ss.length();
        if(len==0){puts("00");continue;}
        gao(len);
        for(int i=0;i<len;++i)
            printf("%X",ss[i]);
        puts("");
    }
}
