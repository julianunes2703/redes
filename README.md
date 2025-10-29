Trabalho Protocolo HTTP - Cliente e Servidor

Este trabalho implementa um cliente HTTP e um servidor HTTP simples em C.

Cliente HTTP: O cliente realiza requisições para um servidor HTTP, baixa arquivos e os salva no disco.

Servidor HTTP: O servidor é capaz de servir arquivos de um diretório específico, e retorna uma lista de arquivos ou um arquivo index.html, se disponível.

Funcionalidades
Parte 1 - Cliente HTTP

O cliente HTTP realiza as seguintes funções:

Acessa uma URL.

Baixa o arquivo da URL e o salva no diretório local.

Se o arquivo não for encontrado, retorna um erro de requisição.

Parte 2 - Servidor HTTP

O servidor HTTP realiza as seguintes funções:

Serve arquivos de um diretório específico.

Se o diretório contiver um arquivo index.html, ele é servido automaticamente.

Caso o diretório contenha outros arquivos, o servidor retorna uma lista de arquivos contidos no diretório.

Como Compilar e Executar
Requisitos

Para compilar e executar o projeto, você precisará de um compilador C e das bibliotecas libcurl e ws2_32 (para Windows).

Instalar o MinGW e libcurl no MSYS2:

Instalar o MinGW e libcurl:

Abra o terminal MSYS2.

Execute o comando:

pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-curl


Compilar o Cliente HTTP:
No terminal, navegue até o diretório onde o arquivo cliente_http.c está localizado e execute:

gcc -o cliente_http cliente_http.c -lcurl


Compilar o Servidor HTTP:
Para compilar o servidor HTTP, execute:

gcc -o servidor_http servidor_http.c -lws2_32

Executando os Programas

Rodando o Cliente HTTP:
Após a compilação, execute o cliente HTTP:

./cliente_http


O cliente tentará acessar a URL configurada no código e salvar o arquivo localmente.

Rodando o Servidor HTTP:
Para rodar o servidor HTTP, execute:

./servidor_http


O servidor ficará ouvindo na porta 8080. Você pode acessá-lo no navegador digitando:

http://localhost:8080


O servidor irá listar os arquivos do diretório onde está sendo executado.

Como adicionar o Makefile (se você usar):
Exemplo de Makefile:
CC = gcc
CFLAGS = -Wall
LIBS = -lcurl -lws2_32

cliente_http: cliente_http.c
	$(CC) $(CFLAGS) -o cliente_http cliente_http.c $(LIBS)

servidor_http: servidor_http.c
	$(CC) $(CFLAGS) -o servidor_http servidor_http.c $(LIBS)

clean:
	rm -f cliente_http servidor_http
