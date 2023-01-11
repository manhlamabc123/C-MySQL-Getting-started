main: mysql.o
	gcc -o main main.c mysql.o -lmysqlclient

mysql.o:
	gcc -c mysql/mysql.c

clean:
	rm -f *.o *~ main