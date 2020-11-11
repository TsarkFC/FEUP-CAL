import matplotlib.pyplot as plt
from math import log2

x = [i for i in range(10, 101, 10)]
ver = [i*i for i in x]
are = [4*i*(i-1) for i in x]
y = [(ver[i] + are[i])* log2(ver[i]) for i in range(0, len(x))]

print(y)

results = [50, 160, 500, 908, 1370, 1466, 2222, 2433, 3149, 3874]
results = [i*1000 for i in results]

plt.plot(x, y)
plt.plot(x, results)
plt.show()