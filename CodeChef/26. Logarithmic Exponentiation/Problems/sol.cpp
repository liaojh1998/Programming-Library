#include<stdio.h>
unsigned long long int power(long int x,long int n);
int main()
{
    int t;
    long int n;
    unsigned long long int p,x,count,m,count1;
    m=1000000007;
    scanf("%d", &t);
    while(t--)
    {
    scanf("%ld",&n);
    p=0;
    count=0;
    count1=0;
    if(n%2==0){
        p=n/2;
        x=power(2,p);
        count=(3*x)-2;
        count1=count%m;
        }
    else{
        p=(n-1)/2;
        x=power(2,(p+2));
        count=x-2;
        count1=count%m;
        }
        printf("%llu\n",count1);
    }
    return 0;
}
unsigned long long int power(long int x,long int n){
    unsigned long long int k,m1;
    m1=1000000007;
    if(k<0)
        k=k+m1;
    if(n==0)
        return 1;
    else if(n%2==0){
        k=power(x,n/2);
        return (k*k)%m1;
    }
    else{
        k=power(x,(n-1));
        return (k*x)%m1 ; }
} 