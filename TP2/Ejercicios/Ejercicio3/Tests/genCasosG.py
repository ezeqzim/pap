import random as r
import sys

def specific():
    filename = "bigTest.in"
    expected = "bigTest.exp"
    N = 10**4
    M = 10**4
    Qa = 10**3
    Qb = (10**5 - Qa) / 2
    Qc = (10**5 - Qa) / 2
    with open(filename, "w") as f:
        f.write(str(N) + " " + str(M) + "\n")
        for i in range(1, M):
            n1 = str(i)
            n2 = str(i + 1)
            f.write(n1 + " " + n2 + "\n")
        f.write("1 " + str(M) + "\n")
        f.write(str(Qa + Qb + Qc))
        for i in range(0, Qa):
            n1 = str(r.randint(1, N))
            n2 = str(r.randint(1, N))
            f.write("A " + n1 + " " + n2 + "\n")
        for i in range(0, Qb):
            n1 = str(r.randint(1, M))
            f.write("B " + n1 + "\n")
        for i in range(0, Qc):
            n1 = str(r.randint(1, N))
            f.write("C " + n1 + "\n")
    with open(expected, "w") as f:
        for i in range(0, Qa):
            f.write("0\n")
        for i in range(0, Qb):
            f.write("0\n")
        for i in range(0, Qc):
            f.write(str(N - 1) + "\n")

def aleatorio(filename):
    filename = filename + ".big"
    with open(filename,"w") as f:
        N = 10**4
        M = 10**5
        Qa = 10**3
        Qb = (10**5 - Qa) / 2
        Qc = (10**5 - Qa) / 2
        f.write(str(N) + " " + str(M) + "\n")
        for i in range(0, M):
            n1 = str(r.randint(1, N))
            n2 = str(r.randint(1, N))
            f.write(n1 + " " + n2 + "\n")
        f.write(str(Qa + Qb + Qc))
        for i in range(0, Qa):
            n1 = str(r.randint(1, N))
            n2 = str(r.randint(1, N))
            f.write("A " + n1 + " " + n2 + "\n")
        for i in range(0, Qb):
            n1 = str(r.randint(1, M))
            f.write("B " + n1 + "\n")
        for i in range(0, Qc):
            n1 = str(r.randint(1, N))
            f.write("C " + n1 + "\n")

if(len(sys.argv) == 1):
    specific()
else:
    aleatorio(sys.argv[1])
