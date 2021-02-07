// Union Find
 
template<typename T>
struct UnionFind
{
	vector<T> par;
	vector<T> rank;
	vector<T> sizes;
	UnionFind(T n):par(n),rank(n,0),sizes(n,1){
	   for(T i=0;i<n;i++){
	     par[i]=i;
	   }
	}
	T root(T x){
	  return par[x]==x?x:par[x]=root(par[x]);
	}
 
	bool unite(T x,T y){
	  if(x==y) return false;
	  x=root(x); y=root(y);
	  if(x==y) return false;
	  if(rank[x]<rank[y]) swap(x,y);
	  if(rank[x]==rank[y]) rank[x]++;
	  par[y]=x;
	  sizes[x]=sizes[x]+sizes[y];
	  return true;
	}
	bool same(T x,T y){
	  return root(x)==root(y);
	}
	T size(T x){
	  return sizes[root(x)];
	}
};
