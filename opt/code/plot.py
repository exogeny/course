import numpy as np
import matplotlib.pylab as plt
from sympy import symbols

from steepest import SteepestDescent
from conjugate import ConjudateGradient

dx = 0.01
dy = 0.01
x = np.arange(-0.5, 1.5, dx)
y = np.arange(-0.5, 1.5, dy)

X, Y = np.meshgrid(x, y)

def fx(x, y):
  return (1 - x) ** 2 + 2 * (x ** 2 - y) ** 2

levels=[-0.1, 0.0, 0.1, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 100]
C = plt.contour(X, Y, fx(X, Y), levels = levels, colors = 'black')
plt.contourf(X, Y, fx(X, Y), levels = levels, colors = 'white')
plt.clabel(C, inline = 0.5, fontsize = 10)

x, y = symbols('x, y')
z = (1 - x) ** 2 + 2 * (x ** 2 - y) ** 2

def plot_result(f, p, t, c):
  d = f([x, y, z], p, t)
  r = d.fit([0, 0])
  xv, yv, vv, vi = [], [], [], []
  for xi, yi in r:
    xv.append(xi)
    yv.append(yi)
    vi.append(len(vi))
    vv.append(fx(xi, yi))

  plt.figure(1)
  plt.plot(xv, yv, color = c, linewidth = 1.5, alpha = 0.6)

  plt.figure(2)
  plt.plot(vi, vv, color = c)

  print('Final Result[', len(vi) - 1 ,']:' , vv[-1])

cmap = plt.cm.get_cmap('hsv', 5)
plot_result(SteepestDescent, 1, 1e-4, cmap(0))
plot_result(SteepestDescent, 2, 1e-4, cmap(1))
plot_result(SteepestDescent, np.inf, 1e-4, cmap(2))
plot_result(ConjudateGradient, ConjudateGradient.FR_alpha_func, 1e-4, cmap(3))
plot_result(ConjudateGradient, ConjudateGradient.PRP_alpha_func, 1e-4, cmap(4))

plt.show()
