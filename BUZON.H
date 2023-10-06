                      /*ARCHIVO DE CABEZERA BUZON.H*/

/*Constantes utilizadas a lo largo
  del programa*/
#define  NUM_SDCS                      20 /*Numero maximo de SDCs (casillas)*/
#define  INVITADOSxSDC                 20 /*Numero maximo  de invitados*/
#define  FRENO_BUZON                   10 /*Retardo en el envio de mensajes*/
#define  AJUSTE                        50
#define  NO_HAY_LINEA                0xAA /*MCT fuera de linea*/
#define  MINIMO_DISPONIBLE              5 /*Numero minimo de casillas disponible*/
#define  son_iguales(a,b)     s_comp(a,b) /*Macro rutina para comparaciones*/
#define  no_son_iguales(a,b) !s_comp(a,b) /*Macro rutina para comparaciones*/



/*Formato del registro para la estructura "invitado"
  que es parte de cada nodo de la estructura "nodo_sdc"*/
struct  lista_proveedores
{
   char  nombre_proveedor[41]; /*Nombre del proveedor (proveniente del SIM)*/
   char  rif[11]; /*Numero del RIF (proveniente del SIM)*/
   char  clave_secreta[7]; /*Clave secreta de usuario (generada por MCT)*/
   int  ofertas_entregadas; /*Numero de ofertas entregadas
                              (calculada por el Buzon)*/
}*i_inv;



/*Formato de registro para la estructura "nodo_sdc"*/
struct  registro_sdc
{
   char  sdc[9]; /*Numero de la SDC (proveniente del SIM)*/
   char  fecha_tope[7]; /*Fecha de cierre de la SDC (proveniente del SIM)*/
   struct  lista_proveedores  invitado[INVITADOSxSDC]; /*Lista de invitados
                                                         para la SDC
                                                         (proveniente del SIM)*/
}nodo_sdc[NUM_SDCS+1], /*Estructura principal de informacion del Buzon*/
 *numero_de_sdcs, /*Apuntador al ultimo elemento de la estructura*/
 *i_sdc; /*Apuntador para busquedas a lo largo de la estructura*/



/*Formato de registro utilizado para guardar los datos generales
  de la transaccion mas reciente*/
struct  registro_de_transaccion
{
   char  tipo; /*de la oferta gestionada*/
   char  sdc[9]; /*Numero de la SDC*/
   char  clave_secreta[7]; /*Clave secreta introducida*/
   char  rif[11]; /*Numero de RIF introducido*/
   char  nombre_proveedor[41]; /*Nombre del proveedor aludido*/
   char  nombre_usuario[26]; /*Nombre del usuario que realizo la transaccion*/
   char  fecha_entrega[7]; /*Fecha de la transaccion  "ddmmaa\0"*/
   char  hora_entrega[5]; /*Hora de la transaccion  "hhmm\0"*/
   int  status; /*de la transaccion = 1 --> oferta entregada en fecha
                                      2 --> oferta no entregada
                                      3 --> oferta entregada anteriormente
                                      4 --> oferta entregada en fecha extemporanea*/
   int  casilla; /*asignada para la oferta*/
   int  file_pos; /*del archivo principal de datos*/
}datos;



/*Formato de registro para la estructura de "casillas" donde se
  registra el estado del carrusel. En otras palabras, es el carrusel
  como visto por el programa del Buzon*/
struct  sdc_tipos_casilla
{
   char  sdc[9]; /*Numero de la SDC que ocupa la casilla*/
   char  tipo; /*de oferta que ocupa la casilla.
                 NOTA: cuando este campo se activa a cero, indica
                       que la casilla esta disponible para asignarse*/
}casillas[20]; /*Contiene el estado de las veinte casillas del carrusel*/



/*Formato de registro que contiene el horario de trabajo del Buzon*/
struct  horario_trabajo
{
   char  hora_inicio[5];
   char  hora_finalizacion[5];
}horario;



/*Formato de registro para los puertos
  de comunicacion con los diferentes
  componentes del Buzon Electronico.*/
struct  puertos_io
{
   unsigned  MCT; /*Puerto de comunicacion con el MCT*/
   unsigned  MECANISMO; /*Puerto de comunicacion con el mecanismo
                          de extraccion de sobres*/
   unsigned  MOTORES; /*Puerto de comunicacion para motores*/
   unsigned  TSENSORES; /*Puerto de sensores del tobogan*/
}PUERTO_DE;



/*Acontinuacion esta la lista de nombres de archivos utilizados*/
char  *buzon00="BZ00.\0", /*Archivo intermedio para operaciones*/
      *buzon01="BZ01.\0", /*Contiene los datos de trabajo del Buzon*/
      *buzon02="BZ02.\0", /*Registra una imagen de las casillas*/
      *buzon03="BZ03.\0", /*Archivo de configuracion del Buzon Electronico*/
      *buzon04="BZ04.\0", /*Archivo que contiene las ultimas transacciones*/
      *buzon05="BZ05.\0"; /*Archivo que contiene las direcciones de puerto
                            para los componentes del Buzon Electronico*/



/*Variables utilizadas en comunidad
  por todos los modulos del programa*/
unsigned  backup_casillas, /*Handle para el archivo BZ02*/
          transacciones,   /*Handle para el archivo BZ04*/
          archivo_existente, /*Indica la existencia de
                               transacciones pendientes
                               por enviar al MCT
                               (sin necesidad de abrir el archivo)*/
          fuera_de_servicio, /*Indica el estado del Buzon = 0 -> en servicio
                                                            1 -> fuera de servicio*/
          fuera_de_horario, /*Indica el estado del Buzon =  0 -> en horario
                                                            1 -> fuera de horario*/
          primero_disponible, /*Primera casilla disponible para asignarle
                                un SDC y un tipo de oferta*/
          casilla_permanente, /*Casilla donde esta posicionado el tobogan.
                                Generalmente es la casilla media*/
          casilla_nueva, /*Casilla donde se introducira el sobre durante
                           la transaccion*/
          casillas_disponibles, /*Cuantas casillas quedan disponibles*/
          urgencia_atendida, /*Ordena al Buzon enviar el caracter de advertencia
                               de pocas casillas disponibles ( <= 4)*/
          tipo_de_oferta, /*variable compartida entre los modulos de recepcion
                            y registro de transaccion*/
          numseg, /*Variables utilizadas para instalar
                    la rutina de interrupcion "filtro"*/
          index;
unsigned char  lectores; /*Mapa de bits para los lectores del tobogan*/



/*Prototipos para los procedimientos del programa*/
void  inicializacion_de_archivos();
void  main_buzon_electronico();
int  espera_por_una_accion(int );
int  esta_en_horario();
int  datos_del_usuario();
void  recepcion_de_oferta(char tipo_de_entrega);
int  interfaz_con_MCT();
void  abandonar_transaccion();
void  inicializa_registro_intermedio();
void  registrar_transaccion(int status_de_transaccion);
int  hay_casilla_asignada();
void  imprime_la_etiqueta();
void  imprime_el_comprobante(int estado);
void  envia_comentarios_MCT(register char *cadena);
int  envia_al_MCT_campo(register char *cadena);
int  interpreta_ejecuta_comando(char *linea);
void  datos_al_mecanismo(unsigned int,unsigned char);
unsigned char  datos_del_mecanismo(unsigned int);
void  mover_la_puerta(int,int,int);
int  entrada_de_sobre(int);
int  busca_el_codigo(int,int);
void  busca_la_casilla(int,int);
void  instala_vector_para_filtro();
void  repone_vector_de_filtro();
void  interrupt far filtro();