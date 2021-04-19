#include <iostream>

const int INF = 1000000000;

void insert(int& n, int& m, int** way, int** dp, int** prev1, int**prev2){
    for(int i = 0; i < n + 1; ++i){
        way[i] = new int[n + 1];
        dp[i] = new int[m];
        prev1[i] = new int[m];
        prev2[i] = new int[m];
        way[i][0] = 0;
        for(int j = 1; j < n + 1; ++j) {
            if(i > 0)
                std::cin >> way[i][j];
            else
                way[i][j] = 0;
        }
    }
}

void fill_dp(int& n, int& m, int** way, int** dp, int** prev1, int**prev2){
    for(int i = 0; i < n + 1; ++i){
        for(int mask = 0; mask < m; ++mask)
            dp[i][mask] = INF;
    }
    for(int i = 0; i < n + 1; ++i) {
        dp[i][0] = 0;
    }
    for(int mask = 1; mask < m; ++mask){
        if(mask % 2) {
            for (int i = 0; i < n + 1; ++i) {
                for (int j = 0; j < n + 1; ++j) {
                    int bit_j = 1 << j;
                    int prev_mask = mask ^bit_j;
                    if ((mask >> j) % 2 && dp[j][prev_mask] + way[i][j] <= dp[i][mask]) {
                        dp[i][mask] = dp[j][prev_mask] + way[i][j];
                        prev1[i][mask] = j;
                        prev2[i][mask] = prev_mask;
                    }
                }
            }
        }
    }
}

void restore_ans(int& n, int& m, int** prev1, int** prev2){
    int count = 0, ind = 0, mask = m - 1;
    while(count < n){
        int ind_copy = ind;
        ind = prev1[ind_copy][mask];
        mask = prev2[ind_copy][mask];
        std::cout << ind << " ";
        count++;
    }
}

void free_memory(int& n, int** way, int** dp, int** prev1, int**prev2){
    for(int i = 0; i < n + 1; ++i){
        delete[] way[i];
        delete[] dp[i];
        delete[] prev1[i];
        delete[] prev2[i];
    }
    delete[] way;
    delete[] dp;
    delete[] prev1;
    delete[] prev2;
}

int main() {
    int n;
    std::cin >> n;
    int m = 1<<(n + 1); // 2^(n+1)
    int** way = new int*[n + 1];
    int** dp = new int*[n + 1];
    int** prev1 = new int*[n + 1];
    int** prev2 = new int*[n + 1];
    insert(n, m, way, dp, prev1, prev2);
    fill_dp(n, m, way, dp, prev1, prev2);
    /*for (int mask = 0; mask < m; ++mask) {
        for(int i = 0; i < n + 1; ++i)
            std::cout << dp[i][mask] << " ";
        std::cout << "\n";
    }*/
    std::cout << dp[0][m - 1] << "\n";
    restore_ans(n, m, prev1, prev2);
    free_memory(n, way, dp, prev1, prev2);
    return 0;
}
