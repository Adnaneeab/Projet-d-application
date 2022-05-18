#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[])
{
	//KAOUTAAAAAAAAAAR
    // La socket serveur
    int listenfd = 0;
    // La socket client (r�cup�r�e avec accept())
    int connfd = 0;
    // La structure avec les informations du serveur
    struct sockaddr_in serv_addr = {0};
    // Le buffer pour envoyer les donn�es
    char sendBuff[1025] = {0};
    
    // Cr�ation de la socket serveur
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //Initialisation de la structure sockaddr
    serv_addr.sin_family = AF_INET;
    //Accepte les connexions depuis n'importe quelle adresse
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Le port sur lequel la socket va �couter
    serv_addr.sin_port = htons(5000);
    
    // Association de la socket avec la structure sockaddr
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    //La socket �coute pour des connexions
    listen(listenfd, 10);
    
    // R�cup�ration du nom de la machine
    char hostname[128];
    gethostname(hostname, sizeof hostname);
    
    int pid = 0;
    while(1)
    {
        // Accepte la connexion d'une socket client
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        
        // Ex�cution d'un fork pour g�rer la connexion
        /*if((pid=fork())==-1) {
            printf("erreur\n");
            close(connfd);
        }
        else if(pid>0) { // Le processus p�re
            close(connfd);
        }
        else if(pid==0) { // Le processus fils
            snprintf(sendBuff, sizeof(sendBuff), "%s\n", hostname);
            write(connfd, sendBuff, strlen(sendBuff));*/
	    
      char myip[512];
      bzero(myip,512);
      recv(connfd, myip, 512, 0);
      printf("your address is %s\n", myip);           
      FILE *add=fopen("serveur.txt","r+");
      fputs(myip, add);
      fclose(add); 
      close(connfd);
        }
    }
