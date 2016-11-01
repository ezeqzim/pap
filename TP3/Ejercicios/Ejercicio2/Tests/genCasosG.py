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
    N = r.randint(1, 10**3)
    f.write(str(N)+"\n")
    for i in range(0, N):
      S = r.randint(2, 10**3)
      for i in range(0, S):
        if(r.randint(0,1) % 2 == 0):
          f.write(str(unichr(r.randint(65, 90))))
        else:
          f.write(str(unichr(r.randint(97, 122))))
      f.write(" "+str(r.randint(1,S-1)))
      f.write("\n")
