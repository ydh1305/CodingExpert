#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, string> a, pair<int, string> b){
    return a.first < b.first;
}

int main(void){
    vector<pair<int, string>> v;
    v.push_back(pair<int, string>(90, "윤동현"));
    v.push_back(pair<int, string>(70, "천중현"));
    v.push_back(pair<int, string>(75, "김종현"));
    v.push_back(pair<int, string>(80, "이한울"));
    v.push_back(pair<int, string>(85, "김종국"));
    sort(v.begin(), v.end(), compare);
    for(int i = 0; i < v.size(); i++){
        cout << v[i].second << ' ';
    }
    return 0;
}
