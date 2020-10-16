#include <iostream>
#include <vector>
#define pb push_back
#define ll long long int
#define fi first
#define se second
#define vi std::vector<int>
#define vl vector<ll>
#define vd vector<long double>
#define vvd vector<vector<long double> >
#define vvi std::vector<vi>
#define pii pair<int,int>
#define pll pair<ll,ll>
using namespace std;
ll k,m,t,n; // where k = total types of shops opening in one time slot in one market, t = time slots available, m = number of parallel markets, n = types of shops
long double c; // c= trade-off constant
vector<vector<long double> >v; // list of distances between a type of shop and rest others.
vector<vector<vector<ll> > > A,ans; // A corresponds to initial state and ans corresponds to final state
long double goodness() // to calculate the goodness value
{
    long double distance =0, similarities=0;
    ll i,j;
    // To calculate the similarities of all pairs within a single time slot in the same market
    for(i=0;i<m;i++){
        for(j=0;j<t;j++){
            for(ll kk=0;kk<k;kk++){
                for(ll jj=kk+1;jj<k;jj++){
                    similarities+=(1-v[A[i][j][kk]-1][A[i][j][jj]-1]);
                }
            }
        }
    }
    //To calculate the distances of all pairs within a single time slot in the parallel market
    for(i=0;i<m;i++){
        for(j=0;j<t;j++){
            for(ll kk=0;kk<k;kk++){
                for(ll jj=i+1;jj<m;jj++){
                  for(ll kkk=0;kkk<k;kkk++)
                   distance+=v[A[i][j][kk]-1][A[jj][j][kkk]-1];
                }
            }
        }
    }
    // goodness value is c*distance+similarities
    return c*distance+similarities;
}
int main()
{
      cin>> k>>m >>t>>c; // taking inputs of k,m,t,c
      n=k*m*t;
      ll i,j;
      // To take input as a list of distances between a type of shop and rest others as a 3D array of m,t,k Size.
      for(i=0;i<n;i++){
          vd temp;
          for(j=0;j<n;j++){
              double xx;
              cin>> xx;
              temp.pb(xx);
          }
          v.pb(temp);
      }
     ll cnt=1;
     // Choosing the initial state
     for(i=0;i<m;i++){
         vector<vector<ll> > B(t,vector<ll>(k));
         for(j=0;j<t;j++){
             for(ll kk=0;kk<k;kk++){
                 B[j][kk]=cnt++;
             }
         }
         A.pb(B);
     }

     long double mini= goodness(); // calculating goodness value for initial state

     ans=A; // Initializing ans as the initial state

     //Applying Greedy Hill Climb Algorithm
     for(i=0;i<1000000;i++){
        ll i1=rand()%m,j1=rand()%t,k1=rand()%k; //randomly selecting any state
        ll i2=rand()%m,j2=rand()%t,k2=rand()%k; //randomly selecting any state
        swap(A[i1][j1][k1],A[i2][j2][k2]); //swapping randomly selected states
        long double local_max=goodness(); //calculating goodness value corresponding state
        // if the current state has goodness value greater, then updating the ans as that state, and also updating the mini value to the current local max
        if(local_max>mini){
            mini=local_max;
            ans=A;
        }
        // else if goodness value is not greater than we keep iterating over the best state achieved till now.
        else
        {
            A=ans;
        }
    }

    //Printing the output in the required format
    for(i=0;i<m;i++){
        for(j=0;j<t;j++){
            for(ll kk=0;kk<k;kk++){
                cout<<ans[i][j][kk];
                    cout<<" ";
            }
            if(j!=t-1){
                cout<<"| ";
            }
        }
        cout<<endl;
    }
  return 0;
}
