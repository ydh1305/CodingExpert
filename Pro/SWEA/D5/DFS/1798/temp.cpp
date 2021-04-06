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
        T& operator [](int idx) const {
            return arr[idx];
        }
        void operator=(const _vector<T> &tVc) {
            c = tVc.c;
            s = tVc.s;
            delete[] arr;
            arr = new T[c];
            for (int i = 0; i < s; i++)
                arr[i] = tVc[i];
        }
};

template <typename A, typename B>
struct _pair {
    A first;
    B second;
    _pair(A a, B b):first(a), second(b) {}
    _pair() {}
};

#define endl "\n"
#define MAX 40
using namespace std;

int N, M, Airport, Answer;
int Distance[MAX][MAX];
bool Visit[MAX];
_vector<int> Hotel;
_vector<int> Answer_Route;

struct tour {
    int idx;
    int time;
    int sat;
};
struct tour T[MAX];
int T_cnt;
//_vector<_pair<int, _pair<int, int>>> Tour;

int Max(int A, int B) { if (A > B) return A; return B; }

void Initialize()
{
    Hotel.clear();
    Answer_Route.clear();
    //Tour.clear();
    for(int i = 1; i <= N; i++) {
        T[i].idx = 0;
        T[i].time = 0;
        T[i].sat = 0;
    }
    T_cnt = 0;
    Answer = 0;
    for(int i = 1; i <= N; i++) Visit[i] = 0;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            Distance[i][j] = Distance[j][i] = 0;
}

void Input()
{
    cin >> N >> M;
    for (int i = 1; i <= N - 1; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            int a; cin >> a;
            Distance[i][j] = a;
            Distance[j][i] = a;
        }
    }
    for (int i = 1; i <= N; i++)
    {
        char C; cin >> C;
        if (C == 'A') Airport = i;
        else if (C == 'H') Hotel.push_back(i);
        else
        {
            int a, b; cin >> a >> b;
            //Tour.push_back( {i, {a, b}} );
            T[T_cnt].idx = i;
            T[T_cnt].time = a;
            T[T_cnt++].sat = b;
        }
    }
}

void DFS(int Cur, int Day, int Satisfy, int Time, int Depth, _vector<int>& Route)
{
    if (Cur == Airport && Day == M && Depth != 0)
    {
        if (Satisfy > Answer)
        {
            Answer = Satisfy;
            Answer_Route = Route;
        }
        return;
    }

    bool Flag = false;
    for (int i = 0; i < T_cnt; i++)
    {
        int Next = T[i].idx;
        int Play_Time = T[i].time;
        int nSatisfy = T[i].sat;
        int Move_Time = Distance[Cur][Next];

        if (Visit[Next] == true || Cur == Next) continue;
        if (Time + Move_Time + Play_Time > 540) continue;

        Flag = true;
        Visit[Next] = true;
        Route.push_back(Next);
        DFS(Next, Day, Satisfy + nSatisfy, Time + Move_Time + Play_Time, Depth + 1, Route);
        Route.pop_back();
        Visit[Next] = false;
    }

    if (Flag == false)
    {
        if (Day == M)
        {
            if (Time + Distance[Cur][Airport] <= 540)
            {
                Route.push_back(Airport);
                DFS(Airport, Day, Satisfy, Time + Distance[Cur][Airport], Depth + 1, Route);
                Route.pop_back();
            }
        }
        else
        {
            for (int i = 0; i < Hotel.size(); i++)
            {
                int Hotel_Num = Hotel[i];
                if (Time + Distance[Cur][Hotel_Num] <= 540)
                {
                    Route.push_back(Hotel_Num);
                    DFS(Hotel_Num, Day + 1, Satisfy, 0, Depth + 1, Route);
                    Route.pop_back();
                }
            }
        }
    }
}

void Solution()
{
    int Start = Airport;
    _vector<int> V;
    DFS(Start, 1, 0, 0, 0, V);
}

void Solve()
{
    int Tc; cin >> Tc;
    for (int T = 1; T <= Tc; T++)
    {
        Initialize();
        Input();
        Solution();

        cout << "#" << T << " ";
        cout << Answer << " ";
        if (Answer != 0)
        {
            for (int i = 0; i < Answer_Route.size(); i++)
            {
                cout << Answer_Route[i] << " ";
            }
            cout << endl;
        }
        else cout << endl;
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();
    return 0;
}
