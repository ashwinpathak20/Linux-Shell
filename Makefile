compile: os.o cd.o pwd.o echo.o read_line.o token1.o execute.o signal.o pinfo.o jobs.o killallbg.o kjobs.o piping.o
	gcc os.o cd.o pwd.o echo.o read_line.o token1.o execute.o signal.o pinfo.o jobs.o killallbg.o kjobs.o piping.c

os.o: os.c
	gcc -c os.c

cd.o: cd.c
	gcc -c cd.c

echo.o: echo.c
	gcc -c echo.c

pwd.o: pwd.c
	gcc -c pwd.c

read_line.o: read_line.c
	gcc -c read_line.c

token1.o: token1.c
	gcc -c token1.c

execute.o: execute.c
	gcc -c execute.c

signal.o:signal.c
	gcc -c signal.c

pinfo.o: pinfo.c
	gcc -c pinfo.c

jobs.o: jobs.c
	gcc -c jobs.c

killallbg.o: killallbg.c
	gcc -c killallbg.c

kjobs.o: kjobs.c
	gcc -c kjobs.c

piping.o: piping.c
	gcc -c piping.c

clean: os.o cd.o pwd.o echo.o read_line.o token1.o execute.o signal.o pinfo.o jobs.o killallbg.o kjobs.o piping.o
	rm *.o
