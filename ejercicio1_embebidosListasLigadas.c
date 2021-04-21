#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define CABEZA 1 

/*tipos de datos astractos*/
typedef struct DirectorioTrabajador{
     unsigned char nombreTrabajador[20];
     unsigned char numeroTelefono[20]; 
     unsigned char direccionTrabajador[20];
}DirectorioTrabajador;

typedef struct NODO{
   DirectorioTrabajador DirectorioTrabajadores; 
   struct NODO* ptr_siguienteNodo;
}nodo; 
/*VARIABLES GLOBALES*/
nodo *colaLista=NULL;
nodo *cabezaLista=NULL;
unsigned char CantidadTrabajadores=0;  
enum {EscribirDatos=1,VerLista,EliminarNodo,BorrarLista,VerArchivo,EliminarContenidoArchivo,limpiar,SalirMenu};

/*PROTOTIPO DE FUNCIONES*/
void ImprimirOpciones();
void limpiarPantalla();
void ImprimirFechaHora();
/*FUNCIONES PARA EL MANEJO DE LAS LISTAS LIGADAS*/
nodo *CrearNodo();
void InsertarEnLista();
void CrearTrabajador(nodo *nodo);  
void VaciarLista();
void ImprimirLista();
unsigned char PocisionEliminar(); 
void EliminarElemento();
/*FUNCINOES PARA EL MANEJO DE ARCHIVOS*/
unsigned char ModoEscrituraDelArchivo();
void GuardarListaEnArchivo();
void ImprimirContenidoArchivo();
void BorrarListaEnArchivo();

/*INCIO DE LA FUNCION PRINCIPAL*/
int main(void){
     
   unsigned char MenuOpcion=0; 
   limpiarPantalla();
   printf("BIENVENIDO....\r\n");

   while(TRUE){

       ImprimirOpciones();
        scanf("%hhd",&MenuOpcion); 
    
    if(MenuOpcion==SalirMenu){ 
        printf("finalizó sesion.Sus datos han sido almacenados correctamente\r\n");
        printf("los datos almacenados fueron:\r\n");
        VaciarLista(); 
        limpiarPantalla();
        ImprimirFechaHora();
        exit(EXIT_SUCCESS);    
       } 

    switch (MenuOpcion){

            case EscribirDatos:limpiarPantalla();
                              InsertarEnLista(); 
                              GuardarListaEnArchivo();
                              break;
            case      VerLista:limpiarPantalla();
                              printf("actualmente se encuentran %d trabajadores.\r\n",CantidadTrabajadores); 
                              ImprimirLista(); 
                              break; 
            
            case EliminarNodo:limpiarPantalla();
                             EliminarElemento(); 
                             break;

            case  BorrarLista:limpiarPantalla();
                             VaciarLista();
                             break;

            case  VerArchivo:limpiarPantalla();
                            ImprimirContenidoArchivo(); 
                            break; 

            case EliminarContenidoArchivo:limpiarPantalla();
                                          BorrarListaEnArchivo();
                                          break; 
            case limpiar : limpiarPantalla();
                            break; 
            default: printf("ingrese una opcion que sea valida\r\n");
                    break;
        }

     }//FIN DEL BUCLE INFINITO
   
    return 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
}//FIN DE LA FUNCION PRINCIPAL


//
nodo* CrearNodo(){
  nodo *NuevoNodo=(nodo*)malloc(sizeof(nodo));
  if(NuevoNodo==NULL)printf("error!... insuficiente espacio en memoria\r\n");
  return(NuevoNodo);
}
//
void CrearTrabajador(nodo* nodo){
      fflush(stdin);
    printf("ingresa el nombre del trabajdor:\r\n");
     scanf("%s",nodo->DirectorioTrabajadores.nombreTrabajador);
      fflush(stdin); 
    printf("ingrese el numero telefonico de %s\r\n",nodo->DirectorioTrabajadores.nombreTrabajador); 
     scanf("%s",nodo->DirectorioTrabajadores.numeroTelefono);
      fflush(stdin);
    printf("ingrese la direccion del trabajaddor %s\r\n",nodo->DirectorioTrabajadores.nombreTrabajador);
     scanf("%s",nodo->DirectorioTrabajadores.direccionTrabajador);
    CantidadTrabajadores++;  
    }
//
void InsertarEnLista(){
    nodo *NuevoNodo=CrearNodo();
      
  if(cabezaLista==NULL && NuevoNodo!=NULL){
      CrearTrabajador(NuevoNodo);
      cabezaLista=NuevoNodo;
      colaLista=NuevoNodo;
    return; 
    }
  else if(NuevoNodo!=NULL){
          CrearTrabajador(NuevoNodo);
            colaLista->ptr_siguienteNodo=NuevoNodo;
            colaLista=NuevoNodo;  
          return; 
        }  
}
//
void VaciarLista(){
    
  if(cabezaLista==NULL){
      printf("\r\nesta lista es una lista vacia.\r\n");
      return; 
    }
    nodo *eliminarNodo=cabezaLista; 
    nodo *auxiliar=NULL; 
  while(eliminarNodo!=NULL){
        auxiliar=eliminarNodo->ptr_siguienteNodo;
      free(eliminarNodo); 
        eliminarNodo=auxiliar;     
      }
      cabezaLista=NULL;
      colaLista=NULL;
      CantidadTrabajadores=0; 
  printf("la lista se ha vaciado correctamente\r\n\r\n"); 
}

//
void ImprimirLista(){
    
  if(cabezaLista==NULL){
      printf("esta lista es una lista vacia, por favor primero ingrese valores en ella\r\n");
     return;
    }
    nodo *RecorrerNodo=cabezaLista;
  while(RecorrerNodo!=NULL){
        printf("\n\nnombre: %s\n numero telefonico: %s\ndireccion: %s\r\n",
                RecorrerNodo->DirectorioTrabajadores.nombreTrabajador,
                RecorrerNodo->DirectorioTrabajadores.numeroTelefono,
                RecorrerNodo->DirectorioTrabajadores.direccionTrabajador);
        RecorrerNodo=RecorrerNodo->ptr_siguienteNodo;
      }     
}

void EliminarElemento(){
  unsigned char posicion=PocisionEliminar();
    unsigned char MoverPosicion=1; 
    nodo *buscarElemento=cabezaLista; 
    nodo *NodoAuxiliar=NULL;

  for(MoverPosicion=1; MoverPosicion!=posicion && buscarElemento->ptr_siguienteNodo!=NULL;MoverPosicion++){
      NodoAuxiliar=buscarElemento;
      buscarElemento=buscarElemento->ptr_siguienteNodo;         
    }
  if(MoverPosicion!=posicion || buscarElemento==NULL){
      printf("la posicion que desea buscar no se encuentra\\\
              \r\nen la lista o la lista está vacia");
      return;  
    }
  if(MoverPosicion==CABEZA) cabezaLista=buscarElemento->ptr_siguienteNodo; 
    else NodoAuxiliar->ptr_siguienteNodo=buscarElemento->ptr_siguienteNodo; 
            
  free(buscarElemento);
    CantidadTrabajadores--; 
}

void ImprimirOpciones(){
      printf("\n\nIngrese una opcion:\\\
      \n(%d) para insertar datos en la lista.\\\
      \n(%d) para ver los datos que hay en la lista.\\\
      \n(%d) para eliminar un elemento de la lista.\\\
      \n(%d) para eliminar todos los elementos de la lista.\\\
      \n(%d) para visualizar el contenido del archivo.\\\
      \n(%d) para eliminar el contenido del archivio.\\\
      \n(%d) para limpiar la pantalla,\\\
      \n(%d) para final sesion en del menu\r\n",EscribirDatos,
      VerLista,EliminarNodo,BorrarLista,VerArchivo,EliminarContenidoArchivo,limpiar,SalirMenu);
}


unsigned char  PocisionEliminar(){
    unsigned char numero=0;
    printf("ingrese el numero del elemento que desea eliminar");
    scanf("%hhd",&numero);
   return(numero); 
}

unsigned char ModoEscrituraDelArchivo(){
  unsigned char modo=0;
  do{printf("\r\n ingrese el modo de escritura sobre el archivio \"a\" para \\\
          \nescribir al final del archivo o \"w\" para sobre escribir el archivo\r\n");
            getchar(); 
            scanf("%c",&modo);
            if(modo=='a' || modo=='w')return(modo); 
    }while(TRUE);        
                                                                                                   
  }

void GuardarListaEnArchivo(){
      unsigned char modo=ModoEscrituraDelArchivo();
      FILE *ptr_Archivo=NULL;
      if(modo=='w')ptr_Archivo=fopen("DatosTrabajadores-txt","w");
      else ptr_Archivo=fopen("DatosTrabajadores-txt","a");
                
    if(ptr_Archivo==NULL){
      printf("error al intentar abrir el archivo...\r\n");
      exit(EXIT_FAILURE); 
      }
    nodo *RecorrerLista=cabezaLista;
    fprintf(ptr_Archivo,"NOMBRE\tTELEFONO\tDIRECCION\r\n");
    while(RecorrerLista!=NULL){
          fprintf(ptr_Archivo,"%s\t%s\t%s\r\n",
                  RecorrerLista->DirectorioTrabajadores.nombreTrabajador,
                  RecorrerLista->DirectorioTrabajadores.numeroTelefono,
                  RecorrerLista->DirectorioTrabajadores.direccionTrabajador);
          RecorrerLista=RecorrerLista->ptr_siguienteNodo;
        }
 fclose(ptr_Archivo);   
 BorrarListaEnArchivo();  
}


void BorrarListaEnArchivo(){
    unsigned char guardar_borrar=0; 
    printf("desea eliminar todos los datos del archivo??\r\n"); 
  do{
      printf("para borrar ingrese 'y' para continuar ingrese 'n'\r\n"); 
      getchar(); //macro getc(stdin);
      scanf("%c",&guardar_borrar); 
    if(guardar_borrar=='y'){
      FILE *ptr_archivo=fopen("DatosTrabajadores-txt","w");
       if(ptr_archivo==NULL){
         printf("fallo al abrir el archivo\r\n");
         exit(EXIT_FAILURE); 
          }
        fclose(ptr_archivo); 
        printf("elementos eliminados correctamente"); 
      return;
      }
    if(guardar_borrar=='n'){
      printf("elemento guardado\r\n");
      return; 
      }
    }while(TRUE); 
}

void ImprimirContenidoArchivo(){
    FILE *ptr_Archivo=fopen("DatosTrabajadores-txt","r");
  if(ptr_Archivo==NULL){
      printf("error al intentar abrir el archivo...\r\n");
      exit(EXIT_FAILURE); 
      }
      DirectorioTrabajador DirectorioAuxiliarImprision;   
      while(!feof(ptr_Archivo)){
       fscanf(ptr_Archivo,"%s\t%s\t%s\r\n",DirectorioAuxiliarImprision.nombreTrabajador,
                                        DirectorioAuxiliarImprision.numeroTelefono,
                                        DirectorioAuxiliarImprision.direccionTrabajador);
      printf("%s\t%s\t%s\r\n",DirectorioAuxiliarImprision.nombreTrabajador,
                              DirectorioAuxiliarImprision.numeroTelefono,
                              DirectorioAuxiliarImprision.direccionTrabajador);                                   

      }     
}

void limpiarPantalla(){
  unsigned char i=0; 
  for(i=0;i<40;i++)printf("\r\n");
}
void ImprimirFechaHora(){
printf("el programa ejecutado en %s a las %s ha terminado\r\n",__DATE__,__TIME__);
}
