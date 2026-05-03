import sys
from array import array

def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    a = [0] + data[1:]

    N = n + 1

    dp = [array('H', [0]) * N for _ in range(N)]

    for j in range(1, N):
        dp[0][j] = 1

    for i in range(N):
        row = dp[i]

        if i:
            prev = dp[i - 1]
            for j in range(1, N):
                if prev[j] > row[j]:
                    row[j] = prev[j]

        if i == n:
            break

        nw = [0] * N

        for j in range(1, N):
            best = row[j]

            if row[j - 1] > best:
                best = row[j - 1]

            if j < n and row[j + 1] > best:
                best = row[j + 1]

            nw[j] = best

        earliest = [N] * N

        mn = a[i + 1]
        mx = a[i + 1]
        earliest[mn] = i + 1

        for r in range(i + 2, N):
            old_mn = mn
            old_mx = mx

            if a[r] < mn:
                mn = a[r]
            if a[r] > mx:
                mx = a[r]

            if mn < old_mn:
                for x in range(mn, old_mn):
                    earliest[x] = r

            if mx > old_mx:
                for x in range(old_mx + 1, mx + 1):
                    earliest[x] = r

        for j in range(1, N):
            if nw[j] == 0:
                continue

            r = earliest[j]
            if r == N:
                continue

            val = nw[j] + 1
            if val > dp[r][j]:
                dp[r][j] = val

    best_blocks = max(dp[n]) - 1
    print(n - best_blocks)

solve()