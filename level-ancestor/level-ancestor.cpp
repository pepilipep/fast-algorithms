#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct LA_Tree
{
    static const int MAXN = 1e4 + 7;
    int root;
    int n;
    vector<int> children[MAXN], leaves, pi[MAXN], lambda[MAXN];
    int par[MAXN];
    int depth[MAXN];
    int path[MAXN], ind[MAXN];
    int pow[32], deg[MAXN];
    int leaf[MAXN];
    int p[MAXN][32];

    LA_Tree();

    LA_Tree(int _n, int _par[], int _root)
    {
        n = _n;
        root = _root;
        for(int i = 0; i < n; i++)
        {
            par[i] = _par[i];
            if(i != par[i])
                children[par[i]].push_back(i);
        }
    }

    void extractLeaves(int curr, int curDepth)
    {
        depth[curr] = curDepth;
        if(children[curr].size() == 0)
        {
            leaf[curr] = curr;
            leaves.push_back(curr);
        }
        for(int i = 0; i < children[curr].size(); i++)
        {
            extractLeaves(children[curr][i], curDepth + 1);
            leaf[curr] = leaf[children[curr][i]];
        }
    }

    void initLeaves()
    {
        vector<int> cnt[MAXN];
        for(int i = 0; i < leaves.size(); i++)
        {
            cnt[depth[leaves[i]]].push_back(leaves[i]);
        }
        int br = 0;
        for(int i = n - 1; i >= 0; i--)
        {
            for(int j = 0; j < cnt[i].size(); j++)
            {
                leaves[br] = cnt[i][j];
                br++;
            }
        }
    }

    void buildPaths()
    {
        bool mark[MAXN];
        for(int i = 0; i < n; i++)
        {
            mark[i] = false;
        }
        for(int i = 0; i < leaves.size(); i++)
        {
            int v = leaves[i];
            mark[v] = true;
            pi[i].push_back(v);
            while(par[v] != v && !mark[par[v]])
            {
                mark[par[v]] = true;
                pi[i].push_back(par[v]);
                v = par[v];
            }
        }
    }

    void buildLambdas()
    {
        for(int i = 0; i < leaves.size(); i++)
        {
            for(int j = 0; j < pi[i].size(); j++)
            {
                lambda[i].push_back(pi[i][j]);
            }
            int v = pi[i].back();
            for(int j = 0; v!=par[v] && j < pi[i].size(); j++)
            {
                lambda[i].push_back(par[v]);
                v = par[v];
            }
        }

        for(int i = 0; i < leaves.size(); i++)
        {
            reverse(pi[i].begin(), pi[i].end());
            reverse(lambda[i].begin(), lambda[i].end());
            for(int j = 0; j < pi[i].size(); j++)
            {
                path[pi[i][j]] = i;
                ind[pi[i][j]] = j;
            }
        }
    }

    void initPowers()
    {
        pow[0] = 1;
        for(int i = 1; i < 32; i++)
        {
            pow[i] = 2 * pow[i - 1];
        }
        int gr = 0;
        deg[1] = 0;
        for(int i = 2; i <= n; i++)
        {
            if(pow[gr + 1] <= i)
            {
                gr ++;
            }
            deg[i] = gr;
        }

    }

    void buildParents()
    {
        for(int j = 0 ; j < n; j++)
        {
            p[j][0] = par[j];
        }
        for(int i = 1; i < 32; i++)
        {
            for(int j = 0; j < n; j++)
            {
                p[j][i] = p[p[j][i-1]][i-1];
            }
        }
    }

    void init()
    {
        extractLeaves(root, 0);
        initLeaves();
        buildPaths();
        buildLambdas();
        initPowers();
        buildParents();
    }

    int QueryLeaf(int _leaf, int d)
    {
        if(d == 0)
            return _leaf;
        int l = deg[d];
        int d1 = d - pow[l];
        int u = p[_leaf][l];
        int i = path[u];
        int j = ind[u];
        return lambda[i][j - d1];
    }

    int QueryMacro(int v, int d)
    {
        int _leaf = leaf[v];
        int d1 = d + depth[_leaf] - depth[v];
        return QueryLeaf(_leaf, d1);
    }

};

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int par[10] = {0, 0, 0, 1, 1, 2, 2, 3, 5};

	LA_Tree tree(9, par, 0);
	tree.init();
	cout << tree.QueryMacro(3, 2) << endl;
	cout << tree.QueryMacro(3, 1) << endl;
	cout << tree.QueryMacro(8, 0) << endl;
	cout << tree.QueryMacro(7, 2) << endl;

	return 0;
}