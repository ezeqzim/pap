import random as r

with open("testGrandesEj4.in","a") as f:
	N = r.randint(1,10**4)
	f.write(str(N))
	f.write(" ")
	f.write(str(r.randint(1, N)))
	f.write("\n")
	for i in range(0, (N+1)):
		f.write(str(r.randint(0,10006)))
		f.write(" ")
		f.write(str(r.randint(0,10006)))
		f.write(" ")
		f.write(str(r.randint(0,10006)))
		f.write(" ")
		f.write(str(r.randint(0,10006)))
		f.write(" ")
		f.write(str(r.randint(0,10006)))
		f.write(" ")
		f.write(str(r.randint(0,10006)))
		f.write(" ")
		f.write(str(r.randint(0,10006)))
		f.write(" ")
		f.write(str(r.randint(0,10006)))
		f.write(" ")
		f.write(str(r.randint(0,10006)))
		f.write("\n")
	f.write("\n")

