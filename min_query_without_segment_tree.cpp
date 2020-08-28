#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
#include <functional> 
#define ff first 
#define endl "\n"
#define ss second 
#define vi vector<int>
#define ll long long int
#define pii pair<int,int>
#define eb emplace_back
#define mp make_pair
#define pb push_back
#define setbits(x) __builtin_popcountll(x)
#define custom  pair<int,pair<int,int> >
using namespace std;using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> pbds; 
int ax[4]={1,-1,0,0};int ay[4]={0,0,-1,1};
const int sz=1e5+5;
int arr[sz];
int segment[4*sz];
void buildtree(int i,int j,int idx){
    if(i==j){
        segment[idx]=arr[i];return;
    }
    int m=(i+j)/2;
    buildtree(i,m,idx*2);
    buildtree(m+1,j,idx*2+1);
    segment[idx]=min(segment[2*idx],segment[2*idx+1]);
}
int query(int i,int j,int s,int e,int idx){
    if(i>e || j<s)return INT_MAX;
    if(s>=i && e<=j)return segment[idx];
    int m=(s+e)/2;
    int left=query(i,j,s,m,2*idx);
    int right=query(i,j,m+1,e,2*idx+1);
    return min(left,right);
}
void solve(){
    int a;
    int i,j,x,y;
    int n,q;
    cin>>n>>q;
    for(int i=1;i<n+1;i++){
        cin>>arr[i];
    }
    buildtree(1,n,1);
    while(q--){
        int i,j;cin>>i>>j;
        cout<<query(i,j,1,n,1)<<endl;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t=1;
    //cin>>t;
    while(t--){
        solve();
    }
    return 0;
}