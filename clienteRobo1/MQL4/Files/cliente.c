#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define TAMANHO_STRING 50

int main (void){
    void *contexto = zmq_ctx_new ();
    void *requisicao = zmq_socket (contexto, ZMQ_REQ);
    FILE *arquivo;
    char conteudoServidor[10];
    int n = 1;
 
    zmq_connect (requisicao, "tcp://192.168.1.4:5555");
    printf ("Conectando com o servidor...\n");

    while(n!=0) {
	arquivo = fopen("mediaMovel.txt","wt");	
        zmq_send (requisicao, "mediaMovel", 10, 0);
        zmq_recv (requisicao, conteudoServidor, 5, 0);

        printf ("Conteudo recebido %d:  %s\n", n, conteudoServidor);
	
	fprintf(arquivo, "%s",conteudoServidor);
	fclose(arquivo);
	n++;
    }
    
    zmq_close (requisicao);
    zmq_ctx_destroy (contexto);
    return 0;
}

