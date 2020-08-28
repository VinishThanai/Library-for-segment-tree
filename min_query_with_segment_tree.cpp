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
#define left(i) (2*i + 1)
#define right(i) (2*i + 2)
#define parent(i) ((i-1)/2)


template<typename T>
// 0 based indexing 
class SegmentTree
{
    private:
        //represents the segment tree.
        T *tree;
    
        //builds the segment tree.
        void buildTree(vector<T> data);
        
        //size of the segment tree array.
        int segTreeSize;
    
        //extra nodes must be added to array to make its size a power of 2
        //this is the value to be filled for the those nodes.
        T valueForExtraNodes;
    
        //specifies how to combine child node results to form parent node result.
        T (*combine)(T obj1, T obj2);
        // this depends upon the task we have to perform.
        // example INT_MAX for min queury
    
        //used to calculate the size of array needed to store the tree.
        int calculateSize(int n);
    
        //helps to solve a range query.
        T queryHelper(int l,int r, int st, int ed, int node);
    public:
        //tree constructors.
        SegmentTree(vector<T> data, T value, T (*combine)(T obj1, T obj2));
        SegmentTree(T ar[], int n, T value, T (*combine)(T obj1, T obj2));
        
        //query the range l to r, 0 based array indexing.
        T query(int l, int r);
        
        //update the element at index idx to val.
        void update(int idx, T val);
        ///TODO lazy propagation
    
};
// constructor if someone calls through a vector

template<typename T> SegmentTree<T>::SegmentTree(vector<T> data,
                                                T value, T (*combine)(T obj1, T obj2))
{
   this->combine = combine;
   valueForExtraNodes = value;
   segTreeSize = calculateSize(data.size());
   buildTree(data);
}
// constructor id someone calls through a array
template<typename T> SegmentTree<T>::SegmentTree(T ar[], int n,
                                            T value, T (*combine)(T obj1, T obj2))
{
   this->combine = combine;
   valueForExtraNodes = value;
   segTreeSize = calculateSize(n);

   vector<T> data;
   for(int i = 0; i < n; i++)
         data.push_back(ar[i]);

   buildTree(data);
}


template<typename T> int SegmentTree<T>::calculateSize(int n)
{
    int pow2 = 1;
    while( pow2 < n)
    {
        pow2 = pow2 << 1;
    }
    return 2*pow2 - 1;
}
// vase to maximum value of segment tree should be 4*n but there is wastage of memory.
// if size of the vector/array is power of 2 then there will be no extranodes.

template<typename T> T SegmentTree<T>::query(int l, int r)
{
    int st = 0, ed = segTreeSize/2;
    return queryHelper(l, r, st, ed, 0);
}

template<typename T> T SegmentTree<T>::queryHelper(int l,int r, int st, int ed, int node)
{
    if( (r < st) || (l > ed) || (l > r) )
        return valueForExtraNodes;
    if(st >= l && ed <= r)
        return tree[node];
    int mid=st+ed;
    mid=mid>>1;
    T leftVal = queryHelper(l, r, st, mid , left(node));
    T rightVal = queryHelper(l, r, mid + 1, ed, right(node));
    return combine(leftVal, rightVal);
}

template<typename T> void SegmentTree<T>::buildTree(vector<T> data)
{
   int n = data.size();
   tree = new T[segTreeSize];
   int extraNodes = (segTreeSize/2 + 1) - n;
   for(int i = segTreeSize - 1; i >= 0; i--)
   {
       if(extraNodes>0)
           {
               tree[i] = valueForExtraNodes;
               extraNodes--;
           }
       else if(n>0)
           {
               tree[i] = data[n-1];
               n--;
           }
       else
           tree[i] = combine(tree[left(i)], tree[right(i)]);
   }
}
// just for point queury 
// for range query ya to har point pe query kar ya fir lazy propagation use kar

template<typename T> void SegmentTree<T>::update(int idx, T val)
{
    int segTreeIdx = (segTreeSize/2) + idx;
    tree[segTreeIdx] = val;
    while(parent(segTreeIdx) >= 0)
    {
        segTreeIdx = parent(segTreeIdx);
        if(right(segTreeIdx) < segTreeSize)
          tree[segTreeIdx] = combine(tree[left(segTreeIdx)], tree[right(segTreeIdx)]);
        if(segTreeIdx == 0)
            break;
    }
}
int combine(int a ,int b){
    return min(a,b);
}
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    SegmentTree<int> sg(arr,INT_MAX,combine);
    // making a object of segment tree 
    while(q--){
        int i,j;
        cin>>i>>j;
        cout<<sg.query(i,j)<<endl;
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