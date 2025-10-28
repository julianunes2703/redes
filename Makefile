CC = gcc
CFLAGS = -Wall
LIBS = -lcurl -lws2_32

cliente_http: cliente_http.c
	$(CC) $(CFLAGS) -o cliente_http cliente_http.c $(LIBS)

servidor_http: servidor_http.c
	$(CC) $(CFLAGS) -o servidor_http servidor_http.c $(LIBS)

clean:
	rm -f cliente_http servidor_http
