import random as r

def modo_de_uso():
    print "Modo de uso:"
    print "1. Ejecutar con nombre de archivo de salido deseado, la extension sera .big"
    sys.exit()

if(len(sys.argv) == 1):
  modo_de_uso()
else:
  filename = sys.argv[1] + ".big"
  with open(filename,"w") as f:
    f.write(str(r.randint(1, 10**9)))
    f.write(" ")
    N = r.randint(1,40)
    f.write(str(N))
    f.write("\n")
    for i in range(0, N):
      f.write(str(r.randint(0, 10**9)))
      if(i != N-1):
        f.write(" ")
    f.write("\n")
