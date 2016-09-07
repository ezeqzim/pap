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
    N = r.randint(1, 18)
    f.write(str(N))
    f.write("\n")
    for i in range(0, N):
      for j in range(0, N):
        f.write(str(r.randint(0, 10**7)))
        if(i != N-1):
          f.write(" ")
      f.write("\n")
