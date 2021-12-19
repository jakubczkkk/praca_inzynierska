import random as r
import math as m

def monte_carlo_pi(n: int) -> float:

    import random as r
    import math as m

    i = 0
    for _ in range(n):
        x = r.random()
        y = r.random()
        if m.sqrt(x ** 2 + y ** 2) <=1:
            i += 1

    return 4 * i / n


n = [ 10 ** i for i in range(1, 8) ]
for i in n:
    print(f"n = {i}, pi = {monte_carlo_pi(i)}")

