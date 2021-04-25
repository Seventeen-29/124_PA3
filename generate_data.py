import random
a = []
upper = 10**12
with open("input.txt", "w") as f:
    for i in range(100):
        f.write("{}\n".format(random.randint(1, upper)))

