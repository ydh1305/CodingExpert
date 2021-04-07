#include <iostream>
using namespace std;

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
        arr = new T[c];
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

#define MAX 36
int dist[MAX][MAX];
bool visit[MAX];
int N, M, sol, airport;
_vector<int> hotel, route, sol_route;
_vector<_pair<int, _pair<int, int>>> tour;

void DFS(int cur, int day, int sat, int time, int visited) {
    if(cur == airport && day == M && visited != 0) {
        if(sol < sat) {
            sol = sat;
            sol_route = route;
        }
        return;
    }

    bool tour_ok = false;
    for(int i = 0; i < tour.size(); i++) {
        int next = tour[i].first;
        int spend_time = tour[i].second.first;
        int sat_score = tour[i].second.second;
        int move_time = dist[cur][next];

        if(cur == next) continue;
        if(visit[next] == true) continue;
        if(time + spend_time + move_time > 540) continue;

        tour_ok = true;
        visit[next] = true;
        route.push_back(next);
        DFS(next, day, sat + sat_score, time + spend_time + move_time, visited + 1);
        route.pop_back();
        visit[next] = false;
    }

    if(!tour_ok) {
        if(day == M) {
            if(time + dist[cur][airport] <= 540) {
                route.push_back(airport);
                DFS(airport, day, sat, 0, visited + 1);
                route.pop_back();
            }
        }
        else {
            for(int i = 0; i < hotel.size(); i++) {
                int hotel_no = hotel[i];
                if(time + dist[cur][hotel_no] <= 540) {
                    route.push_back(hotel_no);
                    DFS(hotel_no, day + 1, sat, 0, visited + 1);
                    route.pop_back();
                }
            }
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M;
        hotel.clear(); route.clear(); sol_route.clear(); tour.clear();
        sol = 0; airport = 0;
        for(int j = 1; j <= N; j++)
            for(int k = 1; k <= N; k++)
                dist[j][k] = dist[k][j] = 0;
        for(int j = 1; j <= N; j++) visit[j] = 0;
        for(int j = 1; j <= N - 1; j++) {
            for(int k = j + 1; k <= N; k++) {
                int x; cin >> x;
                dist[j][k] = dist[k][j] = x;
            }
        }
        for(int j = 1; j <= N; j++) {
            char ch; cin >> ch;
            if(ch == 'A') airport = j;
            else if(ch == 'H') hotel.push_back(j);
            else {
                int a, b; cin >> a >> b;
                tour.push_back({j, {a, b}});
            }
        }
        DFS(airport, 1, 0, 0, 0);
        cout << '#' << i << ' ' << sol << ' ';
        if(sol) {
            for(int i = 0; i < sol_route.size(); i++)
                cout << sol_route[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}