import random
a = []
upper = 10**12
with open("input.txt", "w") as f:
    for i in range(100):
        r = random.randint(1, upper)
        a.append(r)
        f.write("{}\n".format(r))
print(max(a))

