#include <iostream>
using namespace std;

#define MAX 1000000000

template <typename T>
class _vector {
public:
    int s;
    int c;
    T *arr;

    _vector() {
        s = 0;
        c = 32;
        arr = new T[c];
    }
    _vector(int k) {
        s = k;
        c = k;
        arr = new T[c];
    }
    ~_vector() {
        delete[] arr;
    }
    void clear() {
        delete[] arr;
        s = 0;
        c = 32;
        arr = new T[c];
    }
    bool empty() {
        return s == 0;
    }
    int size() {
        return s;
    }
    void resize(int k) {
        T *temp = new T[k];
        for(int i = 0; i < s; i++)
            temp[i] = arr[i];
        delete[] arr;
        arr = temp;
        s = c = k;
    }
    int push_back(T v) {
        if(s == c) {
            resize(s * 2);
            s /= 2;
        }
        arr[s++] = v;
        return 1;
    }
    int pop_back() {
        if(empty()) return 0;
        s--;
        return 1;
    }
    int INV() {
        if(empty()) return 0;
        long long tmp = back(); pop_back();
        push_back(-tmp);
        return 1;
    }
    int DUP() {
        if(empty()) return 0;
        push_back(back());
        return 1;
    }
    int SWP() {
        if(s >= 2) {
            long long v1 = back(); pop_back();
            long long v2 = back(); pop_back();
            push_back(v1);
            push_back(v2);
            return 1;
        }
        return 0;
    }
    int ADD() {
        if(s >= 2) {
            long long v1 = back(); pop_back();
            long long v2 = back(); pop_back();
            if(abs(v2 + v1) > MAX) return 0;
            push_back(v1 + v2);
            return 1;
        }
        return 0;
    }
    int SUB() {
        if(s >= 2) {
            long long v1 = back(); pop_back();
            long long v2 = back(); pop_back();
            if(abs(v2 - v1) > MAX) return 0;
            push_back(v2 - v1);
            return 1;
        }
        return 0;
    }
    long long abs(long long n) {
        if(n < 0) return n * -1;
        return n;
    }
    int MUL() {
        if(s >= 2) {
            long long v1 = back(); pop_back();
            long long v2 = back(); pop_back();
            if(abs(v1 * v2) > MAX) return 0;
            push_back(v2 * v1);
            return 1;
        }
        return 0;
    }
    int DIV() {
        if(s >= 2) {
            int cnt = 0;
            long long v1 = back(); pop_back();
            long long v2 = back(); pop_back();
            if(v1 == 0) return 0;
            if(v1 < 0) cnt++; 
            if(v2 < 0) cnt++;
            long long sol = v2 / v1;
            if(cnt == 1) sol = -(abs(sol));
            else sol = abs(sol);
            push_back(sol);
            return 1;
        }
        return 0;

    }
    int MOD() {
        if(s >= 2) {
            int cnt = 0;
            long long v1 = back(); pop_back();
            long long v2 = back(); pop_back();
            if(v1 == 0) return 0;
            if(v2 < 0) cnt++;
            long long sol = v2 % v1;
            if(cnt == 1) sol = -(abs(sol));
            else sol = abs(sol);
            push_back(sol);
            return 1;
        }
        return 0;
    }
    T& back() {
        return arr[s - 1];
    }
    T& operator [](int idx) {
        return arr[idx];
    }
    T operator [](int idx) const {
        return arr[idx];
    }
    void operator =(const _vector<T> &v) {
        delete[] arr;
        s = v.s;
        c = v.c;
        for(int i = 0; i < s; i++)
            arr[i] = v[i];
    }
};

template <typename A, typename B>
struct _pair {
    A first;
    B second;
    _pair(A a, B b):first(a), second(b) {}
    _pair() {}
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    while(true) {
        _vector<_pair<string, long long>> p;
        while(true) {
            string str; cin >> str;
            long long n = 0;
            if(str == "QUIT") return 0;
            if(str == "END") break;
            if(str == "NUM") cin >> n;
            p.push_back({str, n});
        }

        int N; cin >> N;
        for(int i = 0; i < N; i++) {
            int num; cin >> num;
            _vector<long long> v;
            v.push_back(num);
            bool ret = true;
            for(int j = 0; j < p.size(); j++) {
                if(!ret) break;
                if(p[j].first == "NUM") ret = v.push_back(p[j].second);
                else if(p[j].first == "POP") ret = v.pop_back();
                else if(p[j].first == "INV") ret = v.INV();
                else if(p[j].first == "DUP") ret = v.DUP();
                else if(p[j].first == "SWP") ret = v.SWP();
                else if(p[j].first == "MOD") ret = v.MOD(); 
                else if(p[j].first == "DIV") ret = v.DIV();
                else if(p[j].first == "MUL") ret = v.MUL();
                else if(p[j].first == "SUB") ret = v.SUB();
                else if(p[j].first == "ADD") ret = v.ADD();
            }
            if(ret == false || v.size() != 1)
                cout << "ERROR" << '\n';
            else
                cout << v.back() << '\n';
        }
        cout << '\n';
    }
    return 0;
}
