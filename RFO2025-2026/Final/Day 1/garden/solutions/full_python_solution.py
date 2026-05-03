import sys

# Increase recursion depth for deep segment tree updates

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    q = int(input_data[1])
    k = int(input_data[2])
    
    a = [int(x) for x in input_data[3:n+3]]
    
    # Flat arrays for the Segment Tree
    tree_ans = [[0] * k for _ in range(4 * n)]
    tree_first = [0] * (4 * n)
    tree_last = [0] * (4 * n)
    tree_lazy = [0] * (4 * n)
    
    def build(node, l, r):
        if l == r:
            val = a[l]
            tree_first[node] = val
            tree_last[node] = val
            # tree_ans[node] remains all 0s since a single element has 0 pairs
            return
        
        mid = (l + r) // 2
        left_child = 2 * node
        right_child = 2 * node + 1
        
        build(left_child, l, mid)
        build(right_child, mid + 1, r)
        
        tree_first[node] = tree_first[left_child]
        tree_last[node] = tree_last[right_child]
        
        l_last = tree_last[left_child]
        r_first = tree_first[right_child]
        
        for s in range(k):
            tree_ans[node][s] = tree_ans[left_child][s] + tree_ans[right_child][s]
            if (l_last + s) % k < (r_first + s) % k:
                tree_ans[node][s] += 1

    def apply(node, v):
        # Shifting the segment by 'v' means the new answer for shift 's' 
        # is the old answer for shift '(s + v) % K'
        old_ans = tree_ans[node]
        new_ans = [0] * k
        for s in range(k):
            new_ans[s] = old_ans[(s + v) % k]
        tree_ans[node] = new_ans
        
        tree_first[node] = (tree_first[node] + v) % k
        tree_last[node] = (tree_last[node] + v) % k
        tree_lazy[node] = (tree_lazy[node] + v) % k

    def push_down(node):
        if tree_lazy[node] != 0:
            apply(2 * node, tree_lazy[node])
            apply(2 * node + 1, tree_lazy[node])
            tree_lazy[node] = 0

    def update(node, l, r, ql, qr):
        if ql <= l and r <= qr:
            apply(node, 1)
            return
        
        push_down(node)
        mid = (l + r) // 2
        left_child = 2 * node
        right_child = 2 * node + 1
        
        if ql <= mid:
            update(left_child, l, mid, ql, qr)
        if qr > mid:
            update(right_child, mid + 1, r, ql, qr)
            
        tree_first[node] = tree_first[left_child]
        tree_last[node] = tree_last[right_child]
        
        l_last = tree_last[left_child]
        r_first = tree_first[right_child]
        
        for s in range(k):
            tree_ans[node][s] = tree_ans[left_child][s] + tree_ans[right_child][s]
            if (l_last + s) % k < (r_first + s) % k:
                tree_ans[node][s] += 1

    def query(node, l, r, ql, qr):
        if ql <= l and r <= qr:
            return (tree_ans[node][0], tree_first[node], tree_last[node])
        
        push_down(node)
        mid = (l + r) // 2
        left_child = 2 * node
        right_child = 2 * node + 1
        
        if qr <= mid:
            return query(left_child, l, mid, ql, qr)
        if ql > mid:
            return query(right_child, mid + 1, r, ql, qr)
        
        l_ans, l_first, l_last = query(left_child, l, mid, ql, qr)
        r_ans, r_first, r_last = query(right_child, mid + 1, r, ql, qr)
        
        ans = l_ans + r_ans
        if l_last < r_first:
            ans += 1
            
        return (ans, l_first, r_last)

    build(1, 0, n - 1)
    
    out = []
    idx = n + 3
    limit = len(input_data)
    
    while idx < limit:
        type = int(input_data[idx])
        l = int(input_data[idx+1]) - 1
        r = int(input_data[idx+2]) - 1
        idx += 3
        
        if type == 1:
            update(1, 0, n - 1, l, r)
        else:
            if l == r:
                out.append(0)
            else:
                ans, _, _ = query(1, 0, n - 1, l, r)
                out.append(ans)
                
    sys.stdout.write('\n'.join(map(str, out)) + '\n')

if __name__ == '__main__':
    solve()