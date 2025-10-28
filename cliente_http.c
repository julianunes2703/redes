#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

size_t write_file(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

int main() {
    CURL *curl;
    CURLcode res;
    FILE *fp;
    const char *url = "https://picsum.photos/600/400";
    const char *outfilename = "imagem_paisagem.jpg";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        fp = fopen(outfilename, "wb"); 
        if (!fp) {
            perror("Erro ao abrir o arquivo para escrita");
            return 1;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_file);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); 
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);     

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "Erro ao fazer requisicao: %s\n", curl_easy_strerror(res));
        else
            printf("Download concluido com sucesso!\n");

        fclose(fp);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
