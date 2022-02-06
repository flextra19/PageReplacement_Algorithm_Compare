import numpy as np
import matplotlib.pyplot as plt

file1 = open("output.txt","r")
outputs = file1.readlines()
fifo = []
lru = []
opt = []
clock = []
size = []

for i, output in enumerate(outputs) :
    if i > 0 :
        size.append(i+1)
        x = output.split(" : ")
        fifo.append(float(x[1]))
        lru.append(float(x[2]))
        opt.append(float(x[3]))
        clock.append(float(x[4]))

print(size, fifo, opt, lru)


plt.plot(size, fifo, linestyle='-', marker='*', color='red', label='FIFO')
plt.plot(size, lru, linestyle='-', marker='*', color='blue', label='LRU')
plt.plot(size, opt, linestyle='-', marker='*', color='purple', label='OPT')
plt.plot(size, clock, linestyle='-', marker='*', color='green', label='CLOCK')

plt.xlabel("Number of frames allocated")
plt.ylabel("Page faults per 1000 references")
plt.title("Comparison of Fixed-Allocation,Local Page Replacement Algorithms")

plt.legend()

plt.show()