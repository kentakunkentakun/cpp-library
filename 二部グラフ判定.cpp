// 二部グラフ判定
vll color(210);
vvll g(210,vll(0));
bool dfs(ll i,ll p,ll c){　　　　　// i==子  p==親  c==1or2 dfs(1,0,1)で開始　隣接は１originに変換//
    if(color[i]!=0){
        if(color[i]==c)return 1;
        else return 0;
    }
    color[i]=c;
    bool f=1;
    for(auto e:g[i]){
        if(e==p)continue;
        if(c==1){
            f&=dfs(e,i,2);
        }
        else{
            f&=dfs(e,i,1);
        }
    }
    return f;
}
