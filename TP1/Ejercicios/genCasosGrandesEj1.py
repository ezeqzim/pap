import random as r

with open("testGrandesEj1.in","a") as f:
  f.write(str(r.randint(1, 10**9)))
  f.write(" ")
  N = r.randint(1,40)
  f.write(str(N))
  f.write("\n")
  for i in range(0, N):
    f.write(str(r.randint(0, 10**9)))
    if(i != N-1):
      f.write(" ")
  f.write("\n\n")

