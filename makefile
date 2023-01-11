main:
	gcc -o main main.c -lmysqlclient

clean:
	rm -f *.o *~ main