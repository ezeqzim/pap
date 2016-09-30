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
		N = r.randint(1,10**4)
		f.write(str(N))
		f.write(" ")
		M = r.randint(1, 10**5)
		f.write(str(M))
		f.write("\n")
		for i in range(0, M):
			f.write(str(r.randint(1, N)))
			f.write(" ")
			f.write(str(r.randint(2, N)))
			f.write("\n")
		Q = r.randint(1,10**4)
		f.write(str(Q))
		f.write("\n")
		for i in range(0, Q):
			f.write(str(r.randint(1, N)))
			f.write(" ")
			f.write(str(r.randint(2, N)))
			f.write("\n")
