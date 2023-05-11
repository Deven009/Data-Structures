/* Author : Deven Prajapati */
/* Codeforces : https://codeforces.com/contest/271/problem/D */

#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<int> getPowers(int p, int n, int mod) {
    vector<int> p_pow;
    p_pow.push_back(1);
    for(int i=1;i<=n;i++) p_pow.push_back((p_pow[i-1]*p));
    return p_pow;
}

vector<int> compute_hash_values(string s, int p, int mod) {
    int n = s.length();
    
    vector<int> p_pow = getPowers(p,n,mod);
    
    vector<int> hash_values(n+1,0);
    for(int i=0;i<n;i++) {
        hash_values[i+1] = (hash_values[i] + (((s[i]-'a'+1)*p_pow[i])) );
    }
    return hash_values;
}

int32_t main() {
    string s;
    cin>>s;
    string isBad;
    cin>>isBad;
    int k;
    cin>>k;
    
    int n = s.length();
    
    vector<int> badCount(n+1,0);
    for(int i=0;i<n;i++) if(isBad[s[i]-'a']=='0') badCount[i+1] = 1;
    for(int i=1;i<=n;i++) badCount[i] += badCount[i-1];

    const int p = 13331;
    const int mod = 1e9+7;
    vector<int> p_pow = getPowers(p,n,mod);
    vector<int> hash_values = compute_hash_values(s, p, mod);
    
    int cnt = 0;
    for(int l=1;l<=n;l++) {
        unordered_set<int> ms;
        for(int i=0;i<=n-l;i++) {
            int curr_hash = hash_values[i+l]-hash_values[i];
            curr_hash = curr_hash * p_pow[n-i-1];
            if(badCount[i+l]-badCount[i]<=k) {
                ms.insert(curr_hash);
            }
        }
        cnt += (int)ms.size();
    }
    cout<<cnt;
    return 0;
}
