import copy
import numpy as np
from sympy import symbols, diff
from linear_search import linear_search

class ConjudateGradient:
  def __init__(self, function, alpha_func, threshold):
    self.X_ = function[:-1]
    self.FX_ = function[-1]
    self.DFX_ = []
    for d in self.X_:
      self.DFX_.append(diff(self.FX_, d))

    self.alpha_func_ = alpha_func
    self.threshold_ = threshold

  def dx(self, values):
    kv = lambda x : {var : val for var, val in zip(self.X_, x)}
    dx = lambda x : np.array([dfx.subs(kv(x)) for dfx in self.DFX_], np.double)
    return dx(values)

  def fit(self, start_values):
    start_values = np.array(start_values)
    assert len(start_values) == len(self.X_)

    result = [start_values]
    x = copy.deepcopy(start_values)
    x = np.array(x, np.double)

    d = 0
    alpha = 0
    for i in range(1000):
      d = -self.dx(x) + alpha * d
      if np.linalg.norm(d) < self.threshold_:
        break
      l = linear_search(x, self.X_, self.FX_, d, self.threshold_ / 10)
      x0 = np.copy(x)
      x = x + l * d
      result.append(x)
      alpha = self.alpha_func_(self.dx, x0, x)
    return result

  @staticmethod
  def FR_alpha_func(dx, x0, x1):
    alpha = np.linalg.norm(dx(x1)) / np.linalg.norm(dx(x0))
    return alpha * alpha

  @staticmethod
  def PRP_alpha_func(dx, x0, x1):
    dx0 = dx(x0)
    dx1 = dx(x1)
    dd = np.linalg.norm(dx(x0))
    return np.dot(dx1, (dx1 - dx0)) / (dd * dd)


if __name__ == '__main__':
  x, y = symbols('x, y')
  z = (1 - x) ** 2 + 2 * (x ** 2 - y) ** 2
  cd = ConjudateGradient([x, y, z], ConjudateGradient.PRP_alpha_func, 1e-4)
  r = cd.fit([0, 0])
  print(r[-1])
