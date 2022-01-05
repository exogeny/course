import math
import numpy as np

def linear_search(X, variable, function, d, threshold):
  a = 0.0
  b = 1.0

  xv = lambda alpha : {var : val for var, val in zip(variable, X + alpha * d)}
  fx = lambda alpha : function.subs(xv(alpha))

  n = math.ceil(math.log(threshold / (b - a), 0.618))
  for _ in range(n):
    t1 = a + 0.618 * (b - a)
    t2 = b - 0.618 * (b - a)

    v1 = fx(t1)
    v2 = fx(t2)

    if v1 < v2:
      a = t2
    else:
      b = t1
  return (a + b) / 2
