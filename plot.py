import matplotlib.pyplot as plt

n = [5, 20, 100, 1000, 5000, 10000, 50000, 100000]
algorithm_1_runtime = [0.0229496, 0.139276, 0.910125, 11.6883, 107.785, 250.403, 1391.08, 2471.65]
algorithm_2_runtime = [0.0679317, 0.211327, 0.718279, 5.6998, 54.4164, 115.542, 526.137, 1241.46]
BF_runtime = [0.00072415, 0.00521126, 0.112844, 8.70552, 192.817, 852.816, 24779.1, 62397.7]

figure = plt.figure(dpi=300)
plt.plot(n, algorithm_1_runtime)
plt.plot(n, algorithm_2_runtime)
# plt.plot(n, BF_runtime)

plt.legend(['Algorithm 1','Algorithm 2'])
plt.xlabel('Polynomial Size')
plt.ylabel('Runtime (ms)')
plt.title('Runtime among different Algorithms')
plt.xscale('log')
# plt.yscale('log')

figure.savefig('compare.png')