#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#define REP(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)
 
#define ll long long
#define ull unsigned ll
 
#define M 42424242
#define D 1007
 
char in[220000], str[220000];
int z[220000];
 
ull pw[220000], in_hs[220000];
ull good_hs[220000]; int good_sz;
 
void ullSort(ull d[],int s){int i,j;ull k,t;if(s<=1)return;k=d[0]/2+d[s-1]/2+(d[0]%2+d[s-1]%2)/2;i=-1;j=s;for(;;){while(d[++i]<k);while(d[--j]>k);if(i>=j)break;t=d[i];d[i]=d[j];d[j]=t;}ullSort(d,i);ullSort(d+j+1,s-j-1);}
 
void Z_algorithm(char str[], int len, int z[]){
  int i, k, a=0, b=0;
 
  REP(i,1,len){
    if(i <= b && z[i-a] < b-i+1){ z[i]=z[i-a]; continue; }
    if(i > b) a = b = i; else a = i;
    while(b < len && str[b-a]==str[b]) b++;
    z[i] = b-a; b--;
  }
}
 
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
  int i,j,k,l,m,n;
  int T;
  ll res, mul;
  int used[300], ng_char[300];
  int suf_sz, z_mx;
  int uni_len, mx_len, repeat, rest;
  ull hs1, hs2, tmp;
 
  assert( scanf("%d",&T)==1 );
  assert( T<=10 );
 
  pw[0] = 1;
  REP(i,1,220000) pw[i] = pw[i-1] * D;
 
  while(T--){
    assert( scanf("%s",in) == 1 );
    n = strlen(in);
    assert( n <= 100000 );
    rep(i,n) assert( 'a'<=in[i] && in[i]<='z' );
 
    REP(i,'a','z'+1) used[i] = ng_char[i] = 0;
    rep(i,n) used[in[i]]=1;
 
    k = 0; REP(i,'a','z'+1) k += used[i];
    mul = 1; rep(i,k) mul = (mul*(26-i))%M;
    
    rep(i,n) str[i] = in[n-1-i];
    Z_algorithm(str, n, z);
    suf_sz = 0;
    REP(i,1,n) if(suf_sz < z[i]) suf_sz = z[i];
 
    k = 0;
    REP(i,n-suf_sz-1,n) str[k++] = in[i];
    str[k++] = '|';
    rep(i,n) str[k++] = in[i];
    Z_algorithm(str, k, z);
    z_mx = 1;
    REP(i,suf_sz+2,n+1) if(z_mx <  z[i]) z_mx = z[i];
    REP(i,suf_sz+2,n+1) if(z_mx == z[i]) ng_char[str[i+z[i]]] = 1;
 
    k = 0;
    REP(i,n-suf_sz,n) str[k++] = in[i];
    str[k++] = '|';
    rep(i,n) str[k++] = in[i];
    Z_algorithm(str, k, z);
 
    in_hs[0]=0;
    rep(i,n) in_hs[i+1] = in_hs[i]*D + in[i];
 
    good_sz = 0;
    rep(i,n-suf_sz) if(z[suf_sz+1+i] >= z_mx-1){
      mx_len = n - suf_sz - i;
      uni_len = z_mx - 1;
      repeat = uni_len / mx_len;
      rest   = uni_len % mx_len;
 
      if(ng_char[in[i+rest]]) continue;
 
      if(repeat){
        hs1 = in_hs[i+uni_len] - in_hs[i]*pw[uni_len];
        hs2 = 0;
        tmp = in_hs[i+mx_len] - in_hs[i]*pw[mx_len];
        rep(k,repeat) hs2 = hs2 * pw[mx_len] + tmp;
        hs2 = hs2 * pw[rest] + in_hs[i+rest] - in_hs[i]*pw[rest];
        if(hs1 != hs2) continue;
      }
 
      mx_len = n - suf_sz - i;
      uni_len = suf_sz;
      repeat = uni_len / mx_len;
      rest   = uni_len % mx_len;
 
      hs2 = 0;
      if(repeat){
        tmp = in_hs[i+mx_len] - in_hs[i]*pw[mx_len];
        rep(k,repeat) hs2 = hs2 * pw[mx_len] + tmp;
      }
      hs2 = hs2 * pw[rest] + in_hs[i+rest] - in_hs[i]*pw[rest];
      good_hs[good_sz++] = hs2;
/*      printf("--- %llu (%d)\n",hs2,uni_len);*/
    }
 
    ullSort(good_hs, good_sz);
    res = 1;
    REP(i,1,good_sz) if(good_hs[i]!=good_hs[i-1]) res++;
    res = (res * mul)%M;
    printf("%d\n",(int)res);
  }
 
  return 0;
}
 