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
const int N=200005;       // 点数
const int E=200055;   //边数
const int INF= 0x3f3f3f3f;
const long long  LINF= 0x3F3F3F3F3F3F3F3FLL;

struct node;
node* nul;  //表示空， 别忘了初始化, sz=0
int idx;

struct node  {
#define L son[0]
#define R son[1]
    node *son[2], *fa;
    int sz, key;
    int sum, lmx, rmx, mx;

    node (int c=0, node* baba=nul) {
        sum= lmx= rmx= mx= key= c;
        L= R= nul;
        sz= 1;
        fa= baba;
    }
    inline void up() {
        sz= 1+L->sz+R->sz;
        sum= key+ L->sum+ R->sum;
        mx= key+ max(0, L->rmx)+ max(0, R->lmx);
        if(L!=nul) {
        	checkmax(mx, L->mx);
            lmx= max(L->lmx, L->sum+key+max(0,R->lmx));
        } else  {
        	lmx= key+ max(0, R->lmx);
        }
        checkmax(mx, lmx);
        if(R!=nul) {
        	checkmax(mx, R->mx);
        	rmx= max(R->rmx, R->sum+key+max(0,L->rmx));
        }else  {
        	rmx= key+ max(0, L->rmx);
        }
        checkmax(mx, rmx);
    }
    inline void down() {}

#undef L
#undef R
};

int val[N];

struct SPlay {
#define L(x) x->son[0]
#define R(x) x->son[1]
#define KEYTREE root->son[1]->son[0]
    node *root;
    void Rotate(node *x, int c) {
    	node *y= x->fa;
    	y->son[!c]= x->son[c];
    	x->son[c]->fa= y;
    	x->fa= y->fa;
    	if (x->fa!=nul)
            x->fa->son[ R(x->fa)==y ]= x;
        x->son[c]= y;
        y->fa= x;
        y->up();
        if(root==y) root=x;
    }
    inline void Splay(node* x, node* f) {
    	while(x->fa!= f) {
            if(x->fa->fa==f) {
            	Rotate(x, L(x->fa)==x );
            } else  {
            	node *y= x->fa, *z= y->fa;
            	int k= (L(z)==y);
            	if(y->son[k] ==x )
                    Rotate(x, !k), Rotate(x, k);
                else
                    Rotate(y, k), Rotate(x, k);
            }
    	}
    	x->up();
    	if(f==nul)    root= x;
    }
    inline void Rto(int k, node* f) {
    	node* x= root;
    	while( L(x)->sz!=k ) {
    		if(k< L(x)->sz) {
    			x= L(x);
    		} else  {
    			k-= L(x)->sz+1;
    			x= R(x);
    		}
    	}
    	Splay(x, f);
    }

//-----------------------
    inline void del_root() {
    	node *tmp= root;
    	if(R(root)!=nul) {
    		root= R(root);
    		root->fa= nul;
    		Rto(0, nul);
    		L(root)= L(tmp);
    		if(L(tmp)!=nul)
                L(tmp)->fa= root;
    	} else  {
            root= L(root);
            root->fa= nul;
    	}
    	if(root!=nul)
            root->up();
    }
    inline void make_tree(node* &rt, int l, int r, node* baba) {
    	if(l>r) return;
    	int m= (l+r)>>1;
    	rt= new node(val[m], baba);
    	make_tree(L(rt),l,m-1,rt);
    	make_tree(R(rt),m+1,r,rt);
    	rt->up();
    }
    inline void init(int n) {
        nul= new node(0);   nul->sz= 0;
    	root= new node(0, nul);
    	R(root)= new node(0, root);
        rp(i,n) sf(val[i]);
        make_tree(KEYTREE, 0, n-1, R(root));
        R(root)->up();
        root->up();
    }

    inline void insert() {
    	int k, c; sf(k,c);
    	Rto(k-1,nul);
    	Rto(k, root);
    	KEYTREE= new node(c,R(root));
    	R(root)->up();  //pf(R(root));
    	root->up();     // pf(root);
    }
    inline void query() {
    	int l,r; sf(l,r);
    	Rto(l-1,nul);  // pf(root);
    	Rto(r+1,root); // pf(R(root));
    	printf("%d\n", KEYTREE->mx);
    }
    inline void replace() {
    	int k,c; sf(k,c);
    	Rto(k-1,nul); Rto(k+1,root);
    	KEYTREE= new node(c,R(root));
    	R(root)->up(); root->up();
    }
    inline void del() {
    	isf(d); Rto(d,nul);
    	del_root();
    }

    void debug() {

    }
};

int n;
char op[5];
SPlay sp;


int main(){
    // freopen("in.txt","r",stdin);

    sf(n); sp.init(n);

    isf(Q); DO(Q) {
    	scanf("%s", op);
    	// printf("%s\n", op);
    	if(op[0]=='I') {    // insert
    		sp.insert();
    	}else if(op[0]=='Q') {  // query
            sp.query();
    	}else if(op[0]=='R') {  // replace
            sp.replace();
    	}else  {    //delete
            sp.del();
    	}
    }

}



