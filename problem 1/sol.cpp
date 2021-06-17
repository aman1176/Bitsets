
/*
AUTHOR: Aman Raj
College:IIT JODHPUR
Branch:CSE
LANG: C++
*/

using namespace std;

typedef     long long ll;
#include <bits/stdc++.h>


//setbase - cout << setbase (16); cout << 100 << endl; Prints 64
//setfill -   cout << setfill ('x') << setw (5); cout << 77 << endl; prints xxx77
//setprecision - cout << setprecision (14) << f << endl; Prints x.xxxx
//cout.precision(x)  cout<<fixed<<val;  // prints x digits after decimal in val
#define fast  ios_base::sync_with_stdio(false); cin.tie(0);  cout.tie(0);
#define all(a) a.begin(),a.end()
#define allr(a) a.rbegin,a.rend()
//#define mod 998244353





#define inf 1e18
//#define mod 3
#define flush fflush(stdout)

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef cc_hash_table<ll, ll, hash< ll > > ht;

// find_by_order()  // order_of_key
typedef tree<
    pair<ll,ll>,
    null_type,
    less<pair<ll,ll> >,
    rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;




ll mod=1e9+7;

ll power1(ll a, ll b)//a raised to power b
   {  if(b<=0) return 1; if(b==1) return a;
       ll c=power1(a,b/2);
        c*=c;c%=mod;if(b%2==1) c*=a;c%=mod;
        return c;
   }
   ll mi(ll a)
   { ll c= power1(a,mod-2);

     return c;
   }



 struct less_then_greater {
    template<typename T, typename U>
    bool operator()(T const& lhs, U const& rhs) const {
        if (lhs.first < rhs.first) return true;
        if (rhs.first < lhs.first) return false;
        return lhs.second > rhs.second;
    }
};

 /*std::priority_queue<std::pair<int, int>,
                    std::vector<std::pair<int, int>>,
                    less_then_greater
                    > pq;*/
ll gcd(ll a,ll b)
{
    if(b==0)return a;
    return gcd(b,a%b);
}
//cout<<"Case #"<<tt<<": "<<ans<<endl;

void self_max(ll &a,ll b)
{
    a=max(a,b);
}
// trie implementation
 const int K = 2;

struct Vertex {

    int next[K];
    bool leaf = false;
     //set<ll> s;

    Vertex() {
        fill(begin(next), end(next), -1);

    }
};



void add_string(ll const& s,ll msb,vector<Vertex> &triee) {
    //cout<<"add "<<s<<endl;
    int v = 0;// index
    for (ll i=msb;i>=0;i--) {
        int c;
            if(((1ll<<i)&s)==0 )c=0;else c=1;
         //cout<<c<<endl;
        if (triee[v].next[c] == -1) {
            triee[v].next[c] = triee.size();
            triee.emplace_back();
        }
        //triee[v].s.insert(c);
        v = triee[v].next[c];

    }
    triee[v].leaf=true;



}
 void construct(vector<ll> &v,ll msb,vector<Vertex> &triee )
 {

     for(auto x:v)
     {
         add_string(x,msb,triee);
     }
 }
// void dfs(ll a)
// {
//     for(ll i=0;i<2;i++)
//     {
//         if(triee[a].next[i]!=-1)
//         {
//             cout<<i<<" ";dfs(triee[a].next[i]);
//         }
//     }
//     if(triee[a].leaf)cout<<endl;
//
// }
ll solveeven(vector<ll> v);
ll solve(vector<ll> v);
ll solveodd(vector<ll> v);
ll solveodd(vector<ll> v )
{
    vector<Vertex> triee(1);
    ll msb=0;
    sort(v.rbegin(),v.rend());
    for(ll i=0;(1ll<<i)<=v[0];i++)
    {
        if(((1ll<<i)&v[0])>0)msb=i;
    }
     vector<ll> v1,v2;
   for(auto x:v)if(((1ll<<msb)&x)==0)v2.push_back(x);else v1.push_back(x);
    construct(v2,msb,triee);

    //for(auto x:v1)cout<<x<<" ";cout<<endl;for(auto x:v2)cout<<x<<" ";cout<<endl;
    //dfs(0);
    ll ans=inf;
    for(auto x:v1)
    {
        ll ans2=0;
         ll v=0;
        for(ll i=msb;i>=0;i--)
        { //cout<<i<<" ";
            ll a;if(((1<<i)&x)==0)a=0;else a=1;

            if(triee[v].next[a]==-1)
            {  //cout<<"hello"<<" ";
                ans2+=(1ll<<i);
                v=triee[v].next[1-a];
            }
            else v=triee[v].next[a];
            //cout<<ans2<<endl;
        }
        //cout<<endl;
        ans=min(ans,ans2);

    }

    return ans;
}
ll solveeven(vector<ll> v)
{
    if(v.size()==0)return 0;
    sort(v.rbegin(),v.rend());
     if(v[0]==0)return 0;
    ll msb=0;
    for(ll i=0;(1ll<<i)<=v[0];i++)
    {
        if(((1ll<<i)&v[0])>0)msb=i;
    }


     vector<ll> v1,v2;// v1 all even except last and v2 remaining

    for(auto x:v)
    {
        if(((1ll<<msb)&x)==0)v2.push_back(x);
        else v1.push_back((x-(1ll<<msb)));
    }
    ll ans= max(solve(v1),solve(v2));
    return ans;


}
ll solve(vector<ll> v)
{
    if(v.size()==0)return 0;
    sort(v.rbegin(),v.rend());
   //count most significant bit ,if even then xor it else find
   //minimum value among pair with other remaining
   if(v[0]==0)return 0;
   ll ans=inf;
   ll msb=0;


       for(ll i=0;(1ll<<i)<=v[0];i++)
       {
           if(((1ll<<i)&v[0])!=0)msb=i;
       }
       ll ct=0;
       for(auto x:v)if(((1ll<<msb)&x)!=0)ct++;
       if(ct%2==0)
       {
           ans= solveeven(v);
       }
       else ans= solveodd(v);

       return ans;


}

int main()
{  fast;
   //ifstream cin("ts1_input.txt");
   ll n;cin>>n;
   vector<ll> v(2*n);
   for(auto &x:v)cin>>x;

   cout<<solve(v);



   //cout<<msb<<endl;


    return 0;
}
