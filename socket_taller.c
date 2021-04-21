#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define _IP_  "142.250.78.142"  //www.youtube.com
#define _PORT_ 80               //www
#define _Error_ -1
#define TAM 3000
 

typedef struct sockaddr_in sockaddr_in; 


int main (void){
 
 unsigned char peticion[]="GET / HTTP/1.1\r\n\r\n";
 unsigned int conections=0;
 unsigned char HTML[TAM]={0};  
 
 printf("inciando el socket\r\n");
 
  int socket_id=socket(PF_INET,SOCK_STREAM,0); 
  sockaddr_in server;
   server.sin_family=AF_INET; 
   server.sin_addr.s_addr=inet_addr(_IP_); 
   server.sin_port=htons(_PORT_); 
 
  conections=connect(socket_id,(struct sockaddr*)&server,sizeof(server)); 
    if(conections==_Error_){
        printf("fallo al conectarse con el servidor  \r\n"); 
        close(socket_id);
        exit(EXIT_FAILURE); 
      }
       printf("conexion realizada con exito\r\n"); 
       
  if(send(socket_id,peticion,sizeof(peticion),0)<0){ 
     printf("fallo al enviar la peticion\r\n"); 
     close(socket_id);
     exit(EXIT_FAILURE);
     }
     printf("peticion enviada\r\n"); 
   

   if( recv(socket_id, HTML , sizeof(HTML), 0) < 0){
     printf("fallo al recibir");
     close(socket_id); 
     exit(EXIT_FAILURE); 
    }  
     
    puts(HTML); 
   
   close(socket_id); 
   printf("socket cerrado\r\n");

  return (0);
}