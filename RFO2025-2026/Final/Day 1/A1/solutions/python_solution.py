import sys

def is_composite(n: int) -> bool:
    # 0 and 1 are not composite. 2 and 3 are prime.
    if n <= 3:
        return False
    
    # Quick checks for multiples of 2 and 3
    if n % 2 == 0 or n % 3 == 0:
        return True
    
    # Check remaining odd numbers up to the square root of n
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return True
        i += 6
        
    return False

def solve(s: str) -> str:
    # Find the index of the last '*'
    last_star_idx = s.rfind('*')

    # If there are no '*' to replace, check if the integer is composite
    if last_star_idx == -1:
        if is_composite(int(s)):
            return s
        else:
            return "-1"

    # Edge case: single character
    if s == "*":
        return "4"

    # Convert string to list for mutability
    s_list = list(s)

    # Replace all '*' except the last one
    for i in range(len(s_list)):
        if s_list[i] == '*' and i != last_star_idx:
            if i == 0:
                s_list[i] = '1' # Prevent leading zeros
            else:
                s_list[i] = '0' # Minimize sum

    # Calculate the sum of all known digits
    current_sum = 0
    for i in range(len(s_list)):
        if i != last_star_idx:
            current_sum += int(s_list[i])

    # Find a valid digit for the final '*' to make the whole number % 3 == 0
    start_digit = 1 if last_star_idx == 0 else 0
    for d in range(start_digit, 10):
        if (current_sum + d) % 3 == 0:
            s_list[last_star_idx] = str(d)
            break

    # Join the list back into a string
    return "".join(s_list)

if __name__ == '__main__':
    # Read all input from standard input
    input_data = sys.stdin.read().split()
    if input_data:
        # Solve for the first token (the string sequence)
        print(solve(input_data[0]))