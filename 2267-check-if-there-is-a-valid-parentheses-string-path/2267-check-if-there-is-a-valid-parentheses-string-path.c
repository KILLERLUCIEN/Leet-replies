#include <stdbool.h>
#include <stdlib.h>

bool hasValidPath(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int maxBalance = m + n;

    // Path length must be even for a valid parentheses string.
    if ((m + n - 1) % 2 != 0)
        return false;

    // dp[j][balance] = whether this balance is reachable
    // at the current cell in column j.
    bool** dp = malloc(n * sizeof(bool*));

    for (int j = 0; j < n; j++) {
        dp[j] = calloc(maxBalance + 1, sizeof(bool));
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            if (i == 0 && j == 0) {
                // The first character must be '('.
                if (grid[0][0] == '(')
                    dp[0][1] = true;

                continue;
            }

            bool* current = calloc(maxBalance + 1, sizeof(bool));

            // From the cell above.
            if (i > 0) {
                for (int balance = 0; balance <= maxBalance; balance++) {
                    if (dp[j][balance]) {
                        int newBalance =
                            balance + (grid[i][j] == '(' ? 1 : -1);

                        if (newBalance >= 0)
                            current[newBalance] = true;
                    }
                }
            }

            // From the cell on the left.
            if (j > 0) {
                for (int balance = 0; balance <= maxBalance; balance++) {
                    if (dp[j - 1][balance]) {
                        int newBalance =
                            balance + (grid[i][j] == '(' ? 1 : -1);

                        if (newBalance >= 0)
                            current[newBalance] = true;
                    }
                }
            }

            // Replace dp[j] with the current cell's states.
            free(dp[j]);
            dp[j] = current;
        }
    }

    bool result = dp[n - 1][0];

    for (int j = 0; j < n; j++)
        free(dp[j]);

    free(dp);

    return result;
}
