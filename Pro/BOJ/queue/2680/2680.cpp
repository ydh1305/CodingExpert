#include <iostream>
using namespace std;

template <typename T>
class _queue {
public:
    struct Node {
        T v;
        Node *next;
        Node(T v):v(v), next(0) {}
        Node() {}
    };
    Node *head;
    Node *tail;
    int s;

    _queue() {
        head = tail = 0;
        s = 0;
    }
    void push(T v) {
        Node *temp = new Node(v);
        if(head == 0)
            head = tail = temp;
        else {
            tail->next = temp;
            tail = temp;
        }
        s++;
    }
    void pop() {
        Node *temp = head;
        head = head->next;
        delete temp;
        s--;
    }
    T front() {
        return head->v;
    }
    T back() {
        return tail->v;
    }
    bool empty() {
        return s == 0;
    }
    int size() {
        return s;
    }
};

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
    void push_back(T v) {
        if(s == c) {
            resize(s * 2);
            s /= 2;
        }
        arr[s++] = v;
    }
    void pop_back() {
        s--;
    }
    bool empty() {
        return s == 0;
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
        for (int i = 0; i < s; i++)
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

#define NUMERIC 1
#define ALPHANUMERIC 2
#define BYTECHARIC 4
#define KANJI 8
#define TERNIMATION 0

char d2c[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:";

_vector<int> v;

void convert_to_binary(_queue<int> &q, char a, char b) {
    int x, y;
    v.clear();
    if(a >= 'A') x = a - 'A' + 10;
    else x = a - '0';
    for (int i = 0; i < 4; i++) {
        v.push_back(x % 2);
        x /= 2;
    }
    while(!v.empty()) {
        q.push(v.back());
        v.pop_back();
    }
    if(b >= 'A') y = b - 'A' + 10;
    else y = b - '0';
    for (int i = 0; i < 4; i++) {
        v.push_back(y % 2);
        y /= 2;
    }
    while(!v.empty()) {
        q.push(v.back());
        v.pop_back();
    }
}

int get_value(_queue<int> &q, int cnt) {
    int num = 0, s = 1;
    for(int i = 0; i < cnt - 1; i++) s = s * 2;
    for(int i = 0; i < cnt; i++) {
        num = num + (q.front() * s); q.pop();
        s /= 2;
    }
    return num;
}

_pair<int, int> get_charcode(int v) {
    int s = 0, e = 44;
    _pair<int, int> d = { 0, 0 };
    while(s <= e) {
        d.first = (s + e) / 2;
        d.second = v - (d.first * 45);
        if(d.second >= 0 && d.second <= 44) {
            return d;
        }
        else if(d.second < 0) {
            e = d.first - 1;
        } else {
            s = d.first + 1;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        char str[40]; cin >> str;
        _queue<int> q;
        _vector<char> sol;
        sol.clear();
        int total_count = 0;
        for(int j = 0; j <= 36; j = j + 2) convert_to_binary(q, str[j], str[j + 1]);
        while(!q.empty()) {
            if(q.size() <= 3) {
                while(!q.empty()) q.pop();
                break;
            }
            int mode = get_value(q, 4);
            if (mode == NUMERIC) {
                int count = get_value(q, 10);
                total_count = total_count + count;
                int d, r;
                d = count / 3;
                r = count % 3;
                for (int j = 0; j < d; j++) {
                    int val = get_value(q, 10);
                    int s = 100;
                    for(int k = 0; k < 3; k++) {
                        int x = val / s;
                        char ch = '0' + x;
                        sol.push_back(ch);
                        val = val % s; s /= 10; 
                    }
                }
                if (r == 1) {
                    int val = get_value(q, 4);
                    char ch = '0' + val;
                    sol.push_back(ch);
                }
                else if (r == 2) {
                    int val = get_value(q, 7);
                    int x = val / 10;
                    char ch = '0' + x;
                    sol.push_back(ch);
                    x = val % 10;
                    ch = '0' + x;
                    sol.push_back(ch);
                }

            }
            else if (mode == ALPHANUMERIC) {
                int count = get_value(q, 9);
                total_count += count;
                int d, r;
                d = count / 2;
                r = count % 2;
                for(int j = 0; j < d; j++) {
                    int val = get_value(q, 11);
                    _pair<int, int> code = get_charcode(val);
                    char ch1 = d2c[code.first];
                    sol.push_back(ch1);
                    char ch2 = d2c[code.second];
                    sol.push_back(ch2);
                }
                if(r == 1) {
                    int val = get_value(q, 6);
                    char ch1 = d2c[val];
                    sol.push_back(ch1);
                }
            }
            else if (mode == BYTECHARIC) {
                int count = get_value(q, 8);
                total_count += count;
                for(int j = 0; j < count; j++) {
                    int val = get_value(q, 8);
                    if(val >= 32 && val <= 126) {
                        char ch = val;
                        sol.push_back(ch);
                    }
                    else {
                        int d = val / 16;
                        int r = val % 16;
                        sol.push_back('\\');
                        sol.push_back(d2c[d]);
                        sol.push_back(d2c[r]);
                    }
                }
            }
            else if (mode == KANJI) {
                int count = get_value(q, 8);
                total_count += count;
                for (int j = 0; j < count; j++) {
                    int val = get_value(q, 13);
                    if(val >= 32 && val <= 126) {
                        char ch = val;
                        sol.push_back(ch);
                    }
                    else {
                        sol.push_back('#');
                        int s = 16 * 16 * 16;
                        for (int k = 0; k < 3; k++) {
                            int d = val / s;
                            sol.push_back(d2c[d]);
                            val %= s; s /= 16;
                        }
                        sol.push_back(d2c[val]);
                    }
                    
                }
            }
            else {
                int q_size = q.size();
                for(int j = 0; j < q_size; j++) q.pop();
                break;
            }
        }
        cout << total_count << ' ';
        for(int j = 0; j < sol.size(); j++) cout << sol[j];
        cout << '\n';
    }
    return 0;
}
