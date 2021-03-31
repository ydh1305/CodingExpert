#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<string, pair<int, int>> a,
             pair<string, pair<int, int>> b){
    if(a.second.first == b.second.first)
        return a.second.second > b.second.second;
    else
        return a.second.first < b.second.first; 
}

int main(void){
    vector<pair<string, pair<int, int>>> v;
    v.push_back(pair<string, pair<int, int>>("윤동현", pair<int, int>(100, 19880630)));
    v.push_back(pair<string, pair<int, int>>("김종국", pair<int, int>(90, 19680230)));
    v.push_back(pair<string, pair<int, int>>("한기우", pair<int, int>(95, 19700430)));
    v.push_back(pair<string, pair<int, int>>("김용길", pair<int, int>(70, 19200431)));
    v.push_back(pair<string, pair<int, int>>("박용택", pair<int, int>(90, 19880218)));
    sort(v.begin(), v.end(), compare);
    for(int i = 0; i < v.size(); i++)
        cout << v[i].first << ' ';
    return 0;
}
