import random as r
import sys

def modo_de_uso():
    print "Modo de uso:"
    print "1. Ejecutar con nombre de archivo de salido deseado, la extension sera .big"
    sys.exit()

if(len(sys.argv) == 1):
  modo_de_uso()
else:
  filename = sys.argv[1] + ".big"
  with open(filename,"w") as f:
    A = r.randint(1, 10**3)
    C = r.randint(1, 10**3)
    Q = r.randint(1, 10**5)
    f.write(str(A))
    f.write(" ")
    f.write(str(C))
    f.write(" ")
    f.write(str(Q))
    f.write("\n")
    for i in range(0, A):
      for i in range(0, C):
        f.write(str(r.randint(0, 10**9)))
        if(i != C-1):
          f.write(" ")
      f.write("\n")
    for i in range(0, Q):
      a1 = r.randint(1, A-1)
      a2 = r.randint(a1, A)
      c1 = r.randint(1, C-1)
      c2 = r.randint(c1, C)
      f.write(str(a1))
      f.write(" ")
      f.write(str(c1))
      f.write(" ")
      f.write(str(a2))
      f.write(" ")
      f.write(str(c2))
      f.write("\n")
