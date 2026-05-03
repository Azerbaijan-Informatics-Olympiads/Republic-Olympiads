import sys

sys.setrecursionlimit(1000)

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    
    try:
        t_str = next(iterator)
    except StopIteration:
        return
    t = int(t_str)
    
    out = []
    
    for _ in range(t):
        n = int(next(iterator))
        m = int(next(iterator))
        k = int(next(iterator))
        
        head = [-1] * (k + 1)
        nxt = [-1] * m
        eu = [0] * m
        ev = [0] * m
        
        for i in range(m):
            eu[i] = int(next(iterator))
            ev[i] = int(next(iterator))
            l = int(next(iterator))
            if l <= k:
                nxt[i] = head[l]
                head[l] = i
        
        parent = list(range(n + 1))
        sz = [1] * (n + 1)
        comps = n
        
        history_v = [0] * (n + 1)
        history_u = [0] * (n + 1)
        hist_ptr = 0
        
        def unite(u, v):
            nonlocal comps, hist_ptr
            
            while u != parent[u]:
                u = parent[u]
            while v != parent[v]:
                v = parent[v]
                
            if u == v:
                return
                
            if sz[u] < sz[v]:
                u, v = v, u
                
            history_v[hist_ptr] = v
            history_u[hist_ptr] = u
            hist_ptr += 1
            
            parent[v] = u
            sz[u] += sz[v]
            comps -= 1

        def rollback(target_ptr):
            nonlocal comps, hist_ptr
            while hist_ptr > target_ptr:
                hist_ptr -= 1
                v = history_v[hist_ptr]
                u = history_u[hist_ptr]
                
                sz[u] -= sz[v]
                parent[v] = v
                comps += 1

        ans = bytearray(b'1' * k)
        
        def check_connectivity(L, R):
            nonlocal comps
            if L == R:

                if comps > 1:
                    ans[L - 1] = 48 
            else:
                mid = (L + R) // 2
                
                sp = hist_ptr
                for i in range(mid + 1, R + 1):
                    curr = head[i]
                    while curr != -1:
                        unite(eu[curr], ev[curr])
                        curr = nxt[curr]
                        
                check_connectivity(L, mid)
                rollback(sp)

                sp = hist_ptr
                for i in range(L, mid + 1):
                    curr = head[i]
                    while curr != -1:
                        unite(eu[curr], ev[curr])
                        curr = nxt[curr]
                        
                check_connectivity(mid + 1, R)
                rollback(sp)
        
        if k > 0:
            check_connectivity(1, k)
            
        out.append(ans.decode('ascii'))
        
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == '__main__':
    solve()