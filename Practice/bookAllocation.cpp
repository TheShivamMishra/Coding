#include <bits/stdc++.h>
#define ll long long int 
using namespace std;

bool findsol(int a[],int n,int m ,ll ans)
{
    
    int i=0,j=0;
    ll sump=0;//assign the maximum pages
          //that can read which less than equal to ans
   
    while(i<n)
    {
     if(sump+a[i]<=ans)
     {
         sump+=a[i++];
     }else{
         ++j;
         sump=0;
     }
    //No of sudent greater than m to assign all book return false
     if(j>=m)return false;
    }
// at last all check and student equal to  m;
    return true;  
}

// finding ans with binary search
ll binarysearch(int a[],int n,int m,ll end ,ll start)
{
    ll ans=a[n-1];
    while(start<=end)
    {
        ll mid=(start+end)/2;
        if(findsol(a,n,m,mid))
        {
// if mid is valid then assign this to answer
//change the end to mid-1 so minimize the answer till start ==end
            ans=mid;
            end=mid-1;
        }else{
//if mid is not valid then search  between mid+1 and end
            start=mid+1;
        }
       
    }
    return ans;
}

int main() {
    //code
    int t;
    cin>>t;
    while(t--)
    {

       int  n,m;
       ll sum=0;
        cin>>n;
        int a[n];

        for(int i=0;i<n;++i)
        {
            cin>>a[i];
            sum+=a[i];
        }
       
        cin>>m;
       //if no of sudent is greater than book then return -1 as at least one book
       // is allocate every one student
        if(m>n)
        cout<<-1<<endl;
          else if(n==m){
      //if no of student is equal to no of book then return book with  maximum page
            cout<<*max_element(a,a+n)<<endl;
            }
            else{
            cout<<binarysearch(a,n,m,sum,a[0])<<endl;
        }
       
       
    }
    return 0;
}