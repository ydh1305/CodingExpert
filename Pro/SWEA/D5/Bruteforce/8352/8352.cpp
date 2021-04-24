#include <bits/stdc++.h>
using namespace std;

int M[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int dp[31];
void cal(int n) {
    if(n == 0) {
        dp[n] = 1;
        return;
    }
    dp[n] = dp[n - 1] * 2;
    return;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 0; i < 30; i++) cal(i);
    for(int i = 1; i <= T; i++) {
        char s1[12]; char s2[9];
        int Y, MM, DD, hh, mm, ss;
        cin >> s1 >> s2;
        char *temp = strtok(s1, "/"); Y = atoi(temp); 
        temp = strtok(NULL, "/"); MM = atoi(temp); 
        temp = strtok(NULL, "/"); DD = atoi(temp);
        temp = strtok(s2, ":"); hh = atoi(temp); 
        temp = strtok(NULL, ":"); mm = atoi(temp); 
        temp = strtok(NULL, ":"); ss = atoi(temp);
        char s3[31];
        cin >> s3;
        int len = strlen(s3);
        long long sum = 0;
        for(int j = len - 1; j >= 0; j--) {
            if(s3[j] == '1') sum = sum + dp[j];
        }
        sum = sum + ss;
        ss = sum % 60;
        sum = sum / 60;

        sum = sum + mm;
        mm = sum % 60;
        sum = sum / 60;

        sum = sum + hh;
        hh = sum % 24;
        sum = sum / 24;

        //int d = sum / 365;
        //Y = Y + d;
        //sum = sum % 365;
        sum = sum + DD;
        int s = MM;
        while(sum > 0) {
            for(int j = 1; j <= 12; j++) {
                if(!(Y % 400) || ((Y % 100) && !(Y % 4))) M[2] = 29;
                else M[2] = 28;
                if(sum > M[s]) {
                    sum = sum - M[s];
                    s++;
                    if(s > 12) {
                        s = 1;
                        Y = Y + 1;
                    }
                    MM = s;
                } else {
                    DD = sum;
                    sum = 0;
                    break;
                }
            }
        }
        printf("#%d %d/%02d/%02d %02d:%02d:%02d\n", i, Y, MM, DD, hh, mm, ss);
    }
    return 0;
}