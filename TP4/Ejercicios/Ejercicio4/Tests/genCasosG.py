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
		N = r.randint(1,10**5)
		f.write(str(N))
		f.write(" ")
		R = r.randint(1,10**5)
		f.write(str(R))
		f.write("\n")
		for i in range(0, N):
			f.write(str(r.randint(0,10**5)))
			f.write(" ")
		f.write("\n")
		for i in range(0, R):
			a = 0
			b = 0
			while(a == b):
				a = r.randint(0, N)
				b = r.randint(0, N)
			f.write(str(max(a, b)))
			f.write(" ")
			f.write(str(min(a, b)))
			f.write("\n")
		f.write("\n")
