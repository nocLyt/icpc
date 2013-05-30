// 树的重心：子树孩子个数的最大值最小的节点
// pp为重心  ppc表示子树孩子个数的最大值最小  n表示树的节点个数
// tmp来表示 子树u 孩子个数的最大值
// son[i] 表示结点i有多少个孩子
void dfs1(int u, int fa, int& pp, int &ppc, int n) { 

    int tmp= n-son[u];
    rpg(i,u)  {         if((i>>1)==del) continue;
    	int v= g.pnt[i];
        if(v==fa)   continue;
        checkmax(tmp, son[v]);
        dfs1(v,u,pp,ppc,n);
    }
    if(tmp<ppc) {
    	pp= u; ppc= tmp;
    }
}

