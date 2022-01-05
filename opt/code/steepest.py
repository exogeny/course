import copy
import numpy as np
from sympy import symbols, diff
from linear_search import linear_search

class SteepestDescent:
  """SteepestDescent

  function: [x1, x2, ..., xn, y] minimize y = f(x1, x2, ..., xn)
  norm: 1, 2, ..., and 0 for infinity norm
  threshold
  """
  def __init__(self, function, norm, threshold):
    self.X_ = function[:-1]
    self.FX_ = function[-1]
    self.DFX_ = []
    for d in self.X_:
      self.DFX_.append(diff(self.FX_, d))

    self.norm_ = norm
    self.threshold_ = threshold

  def norm(self, values):
    d = np.zeros_like(values)
    if self.norm_ == 1:
      i = np.argmax(np.abs(values))
      d[i] = np.sign(-values[i])
    elif self.norm_ == 2:
      d = -values / np.linalg.norm(values)
    elif self.norm_ == np.inf:
      d = np.sign(-values)
    else:
      raise ValueError('Only support L1, L2 and Linf norm.')
    return np.array(d, np.double)

  def fit(self, start_points):
    start_points = np.array(start_points)
    assert len(start_points) == len(self.X_)

    result = [start_points]
    points = copy.deepcopy(start_points)
    points = np.array(points, np.double)

    kv = lambda x : {var : val for var, val in zip(self.X_, x)}
    dx = lambda x : np.array([dfx.subs(kv(x)) for dfx in self.DFX_], np.double)

    for i in range(1000):
      d = dx(points)
      if np.linalg.norm(d) < self.threshold_:
        break
      d = self.norm(d)
      alpha = linear_search(points, self.X_, self.FX_, d, self.threshold_ / 10)
      points = points + alpha * d
      result.append(points)
    return result

if __name__ == '__main__':
  x, y = symbols('x, y')
  z = (1 - x) ** 2 + 2 * (x ** 2 - y) ** 2
  sd = SteepestDescent([x, y, z], 2, 1e-4)
  r = sd.fit([0, 0])
  print(r[-1])
