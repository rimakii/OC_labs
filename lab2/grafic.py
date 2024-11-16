import matplotlib.pyplot as plt

threads_list = [1, 2, 4, 6, 8, 10]  
matrix_sizes = [
    (100, 100),
    (500, 500),
    (1000, 1000),
    (1500, 1500),
    (3000, 3000),
    (5000, 5000),
] 

results = []  

results = [[0.382102, 0.457993, 0.461317, 0.537068, 0.556773, 0.637237], [0.741649, 0.959638, 0.864994, 0.904580, 0.949112, 1.330998], [0.805446, 0.926853, 0.909046, 0.867714, 1.059120, 1.434389], [1.381630, 1.450624, 1.285419, 1.227109, 1.428087, 1.799338], 
           [2.581338, 1.753810, 1.415278, 1.378781, 1.390255, 1.603618], [2.699733, 1.911416, 1.204721, 1.096515, 1.151535, 1.281259]]

plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
for i, times in enumerate(results):
    acceleration = [times[0] / t for t in times]  
    plt.plot(threads_list, acceleration, marker='o', label=f"Matrix {matrix_sizes[i][0]}x{matrix_sizes[i][1]}")

plt.title("Acceleration vs. Threads")
plt.xlabel("Threads")
plt.ylabel("Acceleration")
plt.legend()
plt.grid()

plt.subplot(1, 2, 2)
for i, times in enumerate(results):
    acceleration = [times[0] / t for t in times]
    efficiency = [acc / p for acc, p in zip(acceleration, threads_list)]  
    plt.plot(threads_list, efficiency, marker='o', label=f"Matrix {matrix_sizes[i][0]}x{matrix_sizes[i][1]}")

plt.title("Efficiency vs. Threads")
plt.xlabel("Threads")
plt.ylabel("Efficiency")
plt.legend()
plt.grid()

plt.tight_layout()
plt.show()