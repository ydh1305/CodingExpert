#include <iostream>
#include <stdlib.h>

using namespace std;

int main(void) {
    int arr[6] = { 1,2,3,4,5,6 };
    cout << "lower_bound(6) : " << lower_bound(arr, arr + 6, 6) - arr;

    return 0;
}
