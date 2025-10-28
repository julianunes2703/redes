#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

// Função para enviar a resposta HTTP
void send_response(SOCKET client_socket, const char *header, const char *body) {
    char response[MAX_BUFFER_SIZE];
    sprintf(response, "%s\n\n%s", header, body);
    send(client_socket, response, strlen(response), 0);
}

// Função para listar arquivos de um diretório no Windows
void list_directory(SOCKET client_socket, const char *path) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char fullPath[MAX_BUFFER_SIZE];
    snprintf(fullPath, MAX_BUFFER_SIZE, "%s\\*", path);  

    // Abrir o diretório
    hFind = FindFirstFile(fullPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        send_response(client_socket, "HTTP/1.1 404 Not Found", "Diretorio nao encontrado.");
        return;
    }

    char body[MAX_BUFFER_SIZE];
    strcpy(body, "<html><body><h1>Conteudo do Diretorio:</h1><ul>");

    do {
        // Verificar se é um arquivo regular (não é '.' ou '..')
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            strcat(body, "<li>");
            strcat(body, findFileData.cFileName);  // Nome do arquivo
            strcat(body, "</li>");
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    strcat(body, "</ul></body></html>");
    FindClose(hFind);

    send_response(client_socket, "HTTP/1.1 200 OK", body);
}

int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_read;

   
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("Erro ao iniciar Winsock");
        return 1;
    }


    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        perror("Erro ao criar socket");
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

 
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("Erro ao fazer bind");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    
    if (listen(server_socket, 10) == SOCKET_ERROR) {
        perror("Erro ao escutar conexoes");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Servidor HTTP ouvindo na porta %d...\n", PORT);

    while (1) {
        
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == INVALID_SOCKET) {
            perror("Erro ao aceitar conexao");
            continue;
        }

   
        bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read == SOCKET_ERROR) {
            perror("Erro ao ler requisicao");
            closesocket(client_socket);
            continue;
        }
        buffer[bytes_read] = '\0';

 
        if (strstr(buffer, "GET / HTTP/1.1") != NULL) {
            list_directory(client_socket, "./");  
        }

      
        closesocket(client_socket);
    }

    
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
