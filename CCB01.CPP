                           /*ARCHIVO PRINCIPAL CCB01.C*/
#include  <estandar.h>
#include  <stdlib.h>
#include  <stdio.h>
#include  <conio.h>
#include  <buzon.h>
#include  <dos.h>



/*[]--------------------------------------------------------------------[]*
 *  Archivo principal del programa de control para el Buzon Electronico.  *
 *  Funciona en ambiente de operacion MS DOS 3.0 y versiones mayores.     *
 *                                                                        *
 *  Librerias utilizadas: ESTANDAR.LIB (E/S en Archivos y dispositivos)   *
 *                                                                        *
 *  Autor: Jose R. Portillo L. 1992                                       *
 *[]--------------------------------------------------------------------[]*/
void main()
{
   instala_vector_para_filtro();
   main_buzon_electronico();
}



/*[]---------------------------------------------[]*
 *  Procedimiento que realiza el estado de espera  *
 *  del Buzon. Desde aqui se hacen las llamadas a  *
 *  los procedimientos que atienden las distintas  *
 *  actividades del programa.                      *
 *                                                 *
 *  Entradas: ninguna                              *
 *  Salidas:  ninguna                              *
 *[]---------------------------------------------[]*/
void main_buzon_electronico()
{
   long int  espera;
   int  reponer;
   char
       cescape,
       *nombre_a =      "BUZON  DE  RECEPCION  DE  OFERTAS",
       *nombre_b =      "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
       *nombre_c =      "≥      COMITE DE MATERIALES     ≥",
       *nombre_d =      "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
       *logo1 =         "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
       *logo2 =         "≥ PEQUIVENPEQUIVENEQ^^VENPEQUIVENPEQUIVE ≥",
       *logo3 =         "≥ PEQUIVENPEQUIVNP      NPEQUIVENPEQUIVE ≥",
       *logo4 =         "≥ PEQUIVENPEQUIEN        PEQUIVENPEQUIVE ≥",
       *logo5 =         "≥ PEQUIVENPEUI^^NP.    .nP^^UIVENPEQUIVE ≥",
       *logo6 =         "≥ PEQUIVENEQ^    ^EQ..PE^    ^VENPEQUIVE ≥",
       *logo7 =         "≥ PEQUIVENE        QUIV        ENPEQUIVE ≥",
       *logo8 =         "≥ PEQIn^^^EQ.    ,E^^^VE.    ,n^^^EQUIVE ≥",
       *logo9 =         "≥ PEU^     ^UI..N^     ^NP..U^     ^UIVE ≥",
       *logo10 =        "≥ EQU       UIVEN       NPEQU       UIVE ≥",
       *logo11 =        "≥ EQUI.   .QU^ ^NP.   .EN^ ^UI.   .QUIVE ≥",
       *logo12 =        "≥ PEQUVENPEQ     PEQUIVE     IVENPEQUIVE ≥",
       *logo13 =        "≥ PEQUIVENE       EQ^IV       VENPEQUIVE ≥",
       *logo14 =        "≥ PEQUIVENEQ.   .PE   QU.   .IVENPEQUIVE ≥",
       *logo15 =        "≥ PEQUIVENPEUIVENP     ENPEQUIVENPEQUIVE ≥",
       *logo16 =        "≥ PEQUIVENPEQUIEN       NPEQUIVENPEQUIVE ≥",
       *logo17 =        "≥ PEQUIVENPEQUIVNP.   .ENPEQUIVENPEQUIVE ≥",
       *logo18 =        "≥ PEQUIVENPEQUIVENPEQUIVENPEQUIVENPEQUIV ≥",
       *logo19 =        "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
       *buzon_trabaja = "* DISCULPE EL BUZON ESTA MOMENTANEAMENTE FUERA DE SERVICIO *",
       *buzon_atiende = "*     OPRIMA LA TECLA [ENTER] PARA INICIAR OPERACIONES     *",
       *empresa1 =      "                       PETROQUIMICA   DE   VENEZUELA, S.A.                      ",
       *empresa2 =      "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒøU.N. OLEFINAS  Y  PLASTICOS⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
       *empresa3 =      "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ  GERENCIA  DE  MATERIALES ¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
       *remitirscr1 =   "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
       *remitirscr2 =   "≥    DIRIJASE AL SECRETARIO DEL COMITE DE MATERIALES    ≥",
       *remitirscr3 =   "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ";


   fuera_de_servicio = 0; /*El Buzon esta en servicio*/
   inicializacion_de_archivos();
   video_tipo(); /*Comprueba el tipo de video instalado*/
   enviar(PUERTO_DE.MCT,0); /*Limpia la linea con MCT*/
   for(reponer = 0;;)
   {
      tipo_cursor(0x2000);
      block(PUERTO_DE.MCT,0); /*Coloca al Buzon en linea con MCT*/
      clrscr();
      delay(1000);
      despliegue(1,1,1,80,0x0B00,0,0,0);
      v_write(1,1,empresa1,0x0B);
      delay(1000);
      despliegue(24,1,25,80,0x0B00,0,0,0);
      v_write(24,1,empresa2,0x0B);
      v_write(25,1,empresa3,0x0B);
      delay(1000);
      for(;;)
      { /*Verifica el horario de trabajo del Buzon*/
         if(!esta_en_horario())
         { /*Mientras no sea el horario de trabajo,
             el Buzon no atiende transacciones*/
            fuera_de_horario = 1; /*Coloca en el estado fuera de horario*/
         }
         else
         {
            fuera_de_horario = 0; /*Coloca en el estado de horario*/
         }
         if(fuera_de_servicio || fuera_de_horario)
         { /*Mensaje de fuera de servicio*/
            v_write(22,11,buzon_trabaja,0x1F);
         }
         else
         { /*Mensaje de inicio de transaccion*/
            v_write(22,11,buzon_atiende,0x0B);
         }
         v_save(3,20,20,61);
         despliegue(3,20,21,61,0x0B00,0,1,2);
         v_write(3,20,logo1,0x0B);
         v_write(4,20,logo2,0x0B);
         v_write(5,20,logo3,0x0B);
         v_write(6,20,logo4,0x0B);
         v_write(7,20,logo5,0x0B);
         v_write(8,20,logo6,0x0B);
         v_write(9,20,logo7,0x0B);
         v_write(10,20,logo8,0x0B);
         v_write(11,20,logo9,0x0B);
         v_write(12,20,logo10,0x0B);
         v_write(13,20,logo11,0x0B);
         v_write(14,20,logo12,0x0B);
         v_write(15,20,logo13,0x0B);
         v_write(16,20,logo14,0x0B);
         v_write(17,20,logo15,0x0B);
         v_write(18,20,logo16,0x0B);
         v_write(19,20,logo17,0x0B);
         v_write(20,20,logo18,0x0B);
         v_write(21,20,logo19,0x0B);
         if(espera_por_una_accion(20) != 0)
         {
            reponer = 0;
            break;
         }
         v_load(3,20,20,61);
         if(espera_por_una_accion(20) != 0)
         {
            reponer = 2;
            break;
         }
         v_save(9,20,16,61);
         despliegue(9,20,16,61,0x0B00,0,1,1);
         v_write(11,24,nombre_a,0x0B);
         v_write(12,24,nombre_b,0x0B);
         v_write(13,24,nombre_c,0x0B);
         v_write(14,24,nombre_d,0x0B);
         if(espera_por_una_accion(20) != 0)
         {
            reponer = 1;
            break;
         }
         v_load(9,20,16,61);
         if(espera_por_una_accion(20) != 0)
         {
            reponer = 2;
            break;
         }
      }
      block(PUERTO_DE.MCT,1); /*Coloca al Buzon fuera de linea con MCT*/
      if(reponer == 1)
      {
         v_load(9,20,16,61);
      }
      else
      {
         if(!reponer)
         {
            v_load(3,20,20,61);
         }
      }
      if(numero_de_sdcs && casillas_disponibles)
      { /*Si hay SDCs registradas y si hay casillas disponibles*/
         delay(1000);
         despliegue(1,1,25,80,0x1FB1,0,0,4);
         delay(1000);
         despliegue(1,1,1,80,0x1B00,0,0,2);
         v_write(1,1,empresa1,0x1B);
         despliegue(4,20,22,61,0x7800,1,0,4);
         v_write(4,20,logo1,0x78);
         v_write(5,20,logo2,0x78);
         v_write(6,20,logo3,0x78);
         v_write(7,20,logo4,0x78);
         v_write(8,20,logo5,0x78);
         v_write(9,20,logo6,0x78);
         v_write(10,20,logo7,0x78);
         v_write(11,20,logo8,0x78);
         v_write(12,20,logo9,0x78);
         v_write(13,20,logo10,0x78);
         v_write(14,20,logo11,0x78);
         v_write(15,20,logo12,0x78);
         v_write(16,20,logo13,0x78);
         v_write(17,20,logo14,0x78);
         v_write(18,20,logo15,0x78);
         v_write(19,20,logo16,0x78);
         v_write(20,20,logo17,0x78);
         v_write(21,20,logo18,0x78);
         v_write(22,20,logo19,0x78);
         despliegue(24,1,25,80,0x1B00,0,0,2);
         v_write(24,1,empresa2,0x1B);
         v_write(25,1,empresa3,0x1B);
         while(datos_del_usuario() == 2)
         {
            ;
         }
      }
      else
      {
         v_save(10,12,17,68);
         despliegue(10,12,12,68,0x5F00,1,0,2);
         v_write(10,12,remitirscr1,0x5F);
         v_write(11,12,remitirscr2,0x5F);
         v_write(12,12,remitirscr3,0x5F);
         delay(12000);
         v_load(10,12,17,68);
         delay(1000);
      }
   }
}



/*[]---------------------------------------------[]*
 *  Procedimiento que verifica un numero de veces  *
 *  la linea con el MCT y el teclado externo por   *
 *  algun requerimiento.                           *
 *                                                 *
 *  Entradas: numero de veces                      *
 *  Salidas:  variable veces codificada            *
 *[]---------------------------------------------[]*/
int espera_por_una_accion(int veces)
{
   char  caracter;


   for(;veces != 0;veces--)
   {
      interfaz_con_MCT();
      if(((caracter = keypressed()) == '\r') &&
         !fuera_de_servicio && !fuera_de_horario)
      {
         veces = 1;
         break;
      }
      if(caracter == 0x1B)
      {
         repone_vector_de_filtro(); /*Vector 1Ch*/
         clrscr();
         block(PUERTO_DE.MCT,0); /*Coloca al BUZON en linea*/
         enviar(PUERTO_DE.MCT,0); /*Limpia la linea con MCT*/
         exit(0); /*Llave maestra para salir del programa*/
      }
   }
   return veces;
}



/*[]-------------------------------------------[]*
 *  Procedimiento que dirige todos los procesos  *
 *  que suceden en una transaccion de entrega    *
 *  de oferta.                                   *
 *                                               *
 *  Entradas: ninguna                            *
 *  Salidas:  opcion del usuario                 *
 *[]-------------------------------------------[]*/
int datos_del_usuario()
{
   long  int  espera;
   short int  numero_caracteres,
              fila = 8,
              columna = 34,
              indice = 0,
              no_mismos_datos,
              fecha_e,
              fecha_t;
   char  opcion,
         sub_rif[12],
         nulo[11] =     "\0\0\0\0\0\0\0\0\0\0\0",
         *ofertarecb1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *ofertarecb2 = "≥  HEMOS RECIBIDO CON ANTERIORIDAD LA OFERTA ECONOMICA  ≥",
         *ofertarecb3 = "≥  DE:  ±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±       ≥",
         *ofertarecb4 = "≥  CON NUMERO DE RIF: ±-±±±±±±±±                        ≥",
         *ofertarecb5 = "≥    Y NUMERO DE SDC: ±±±±±±±±                          ≥",
         *ofertarecb6 = "≥                                                       ≥",
         *ofertarecb7 = "≥      DESEA INTRODUCIR DE NUEVO LOS DATOS S/N( )       ≥",
         *ofertarecb8 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *remitirscr1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *remitirscr2 = "≥    DIRIJASE AL SECRETARIO DEL COMITE DE MATERIALES    ≥",
         *remitirscr3 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *sdc =         "NUMERO DE LA SDC: ±±±±±±±±                        ",
         *rif =         "NUMERO DE RIF   : ±-±±±±±±±±±                     ",
         *nombre =      "SU NOMBRE ES    : ±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±",
         *ayuda1 =      "ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ",
         *ayuda2 =      "EMPRESA: ±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±",
         *ayuda3 =      "         SON CORRECTOS ESTOS DATOS S/N( )         ",
         *ayuda4 =      "ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ",
         *sdcerroneo1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *sdcerroneo2 = "≥ NUM. DE SDC  NO REGISTRADO ≥",
         *sdcerroneo3 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *riferroneo1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *riferroneo2 = "≥ NUM. DE RIF  NO REGISTRADO ≥",
         *riferroneo3 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *cancela1 =    "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *cancela2 =    "≥ESC ->Cancelar≥",
         *cancela3 =    "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ";


   v_save(19,58,21,73);
   despliegue(19,58,21,73,0x1F00,1,0,1);
   v_write(19,58,cancela1,0x1F);
   v_write(20,58,cancela2,0x1F);
   v_write(21,58,cancela3,0x1F);
   delay(1000);
   opcion = 0;
   datos.tipo = 1; /*Oferta economica por defecto*/
   v_save(6,12,18,69);
   despliegue(6,12,18,69,0x1F00,1,1,2);
   tipo_cursor(15);
   v_write(8,16,sdc,0x1F);
   /*Recibe el numero de la SDC*/
   numero_caracteres = recibe_un_dato(datos.sdc,fila,columna,8,0,1,0,0x1F);
   if(!numero_caracteres)
   { /*Si hubo tecla Esc -> regresa status 1*/
      inicializa_registro_intermedio();
      tipo_cursor(0x2000);
      abandonar_transaccion();
      return 1;
   }
   /*i_sdc e i_inv son variables utilizadas como indices
     para accesar las estructuras en memoria*/
   for(i_sdc = nodo_sdc,indice = 0;(no_son_iguales(datos.sdc,i_sdc->sdc)) &&
                                   (i_sdc <= numero_de_sdcs);
                                   i_sdc++,indice++)
   {
      ;
   }
   if(i_sdc > numero_de_sdcs)
   { /*El numero de SDC no esta registrado en el sistema*/
      tipo_cursor(0x2000);
      abandonar_transaccion();
      inicializa_registro_intermedio();
      v_save(12,24,14,53);
      despliegue(12,24,14,53,0x5F00,1,0,0);
      v_write(12,24,sdcerroneo1,0x5F);
      v_write(13,24,sdcerroneo2,0x5F);
      v_write(14,24,sdcerroneo3,0x5F);
      delay(2000);
      v_load(12,24,14,53);
      delay(1000);
      return 0;
   }
   datos.file_pos = indice; /*Registra la posicion dentro del archivo BZ01*/
   fila += 2;
   no_mismos_datos = s_comp(datos.rif,nulo);
   if(no_mismos_datos)
   { /*Es la primera transaccion para este usuario?*/
      v_write(10,16,rif,0x1F);
      numero_caracteres = recibe_un_dato(datos.rif,fila,columna,
                                         11,1,1,0,0x1F);
      if(!numero_caracteres)
      {
         inicializa_registro_intermedio();
         tipo_cursor(0x2000);
         abandonar_transaccion();
         return 1;
      }
   }
   for(i_inv = i_sdc->invitado;(no_son_iguales(i_inv->rif,datos.rif)) &&
                               (no_son_iguales(i_inv->rif,nulo));
                               i_inv++)
   {
      ;
   }
   /*Si el numero de RIF de la sub-estructura invitado es nulo
     entonces se ha encontrado el final de la estructura y por
     lo tanto el numero de RIF introducido, no esta registrado*/
   if(son_iguales(i_inv->rif,nulo))
   { /* RIF no registrado*/
      tipo_cursor(0x2000);
      abandonar_transaccion();
      inicializa_registro_intermedio();
      v_save(12,24,14,53);
      despliegue(12,24,14,53,0x5F00,1,0,0);
      v_write(12,24,riferroneo1,0x5F);
      v_write(13,24,riferroneo2,0x5F);
      v_write(14,24,riferroneo3,0x5F);
      delay(2000);
      v_load(12,24,14,53);
      delay(1000);
      return 0;
   }
   s_copy(i_inv->nombre_proveedor,datos.nombre_proveedor);
   s_copy(datos.rif,sub_rif);
   for(indice = 11;indice > 1;indice--)
   {
      sub_rif[indice] = sub_rif[indice-1];
   }
   sub_rif[1] = '-';
   if(!no_mismos_datos)
   {
      v_write(10,16,rif,0x1F);
      s_copy(datos.rif,sub_rif);
      for(indice = 11;indice > 1;indice--)
      {
         sub_rif[indice] = sub_rif[indice-1];
      }
      sub_rif[1] = '-';
      v_write(fila,columna,sub_rif,0x1F);
   }
   datos.tipo &= 0x0F; /*Verifica el tipo de oferta recibida*/
   tipo_de_oferta = datos.tipo;
   if((i_inv->ofertas_entregadas == 3) ||
      (i_inv->ofertas_entregadas == tipo_de_oferta))
   {
      fila++;
      v_write(11,16,nombre,0x1F);
      /*Recibe el nombre del usuario*/
      numero_caracteres = recibe_un_dato(datos.nombre_usuario,fila,
                                         columna,30,0,0,0,0x1F);
      if(!numero_caracteres)
      { /*Si hubo tecla Esc -> regresa status 1*/
         inicializa_registro_intermedio();
         tipo_cursor(0x2000);
         abandonar_transaccion();
         return 1;
      }
      tipo_cursor(0x2000);
      abandonar_transaccion();
      /*El Buzon muestra el mensaje de oferta recibida anteriormente*/
      v_save(10,12,17,68);
      despliegue(10,12,17,68,0x5F00,1,0,2);
      v_write(10,12,ofertarecb1,0x5F);
      v_write(11,12,ofertarecb2,0x5F);
      v_write(12,12,ofertarecb3,0x5F);
      v_write(12,20,i_inv->nombre_proveedor,0x5F);
      v_write(13,12,ofertarecb4,0x5F);
      v_write(13,34,sub_rif,0x5F);
      v_write(14,12,ofertarecb5,0x5F);
      v_write(14,34,i_sdc->sdc,0x5F);
      v_write(15,12,ofertarecb6,0x5F);
      v_write(16,12,ofertarecb7,0x5F);
      v_write(17,12,ofertarecb8,0x5F);
      gotoxy(59,16);
      /*Desea el usuario introducir denuevo los datos (numero de la SDC)?*/
      for(espera = 400000;((opcion = keypressed()) != 'S') && (opcion != 's') &&
                          (opcion != 'N') && (opcion != 'n') && espera;
                          espera--)
      { /*Espera por una opcion*/
         ;
      }
      v_load(10,12,17,68);
      gotoxy(80,25);
      delay(1000);
      if((opcion == 'S') || (opcion == 's'))
      {
         return 2;
      }
      if((opcion == 'N') || (opcion == 'n'))
      {
         leer_fecha(datos.fecha_entrega); /*Fecha de hoy*/
         leer_hora(datos.hora_entrega); /*Hora de la transaccion*/
         datos.casilla = 0; /*No hay casilla asignada*/
         registrar_transaccion(3); /*Status de oferta recibida antes*/
         inicializa_registro_intermedio();
         return 1;
      }
      else
      { /*No fue oprimida ninguna tecla*/
         return 1;
      }
   }
   /*Presenta el nombre de la empresa y espera la confirmacion
     por el usuario*/
   v_write(13,16,ayuda1,0x1F);
   v_write(14,16,ayuda2,0x1F);
   v_write(14,25,i_inv->nombre_proveedor,0x1F);
   v_write(15,16,ayuda3,0x1F);
   v_write(16,16,ayuda4,0x1F);
   tipo_cursor(0x0607);
   gotoxy(55,15);
   for(espera = 400000;((opcion = keypressed()) != 'S') && (opcion != 's') &&
                       (opcion != 'N') && (opcion != 'n') && espera;
                       espera--)
   { /*Espera por una opcion*/
      ;
   }
   gotoxy(80,25);
   if((opcion == 'N') || (opcion == 'n') ||
      (!espera && (opcion != 'S') && (opcion != 's')))
   { /*Si los datos no estan correctos, remite al usuario
       a la persona indicada dentro del departamento que controla al Buzon*/
      tipo_cursor(0x2000);
      v_load(6,12,18,69);
      delay(1000);
      v_load(19,58,21,73);
      v_save(10,12,17,68);
      despliegue(10,12,12,68,0x5F00,1,0,2);
      v_write(10,12,remitirscr1,0x5F);
      v_write(11,12,remitirscr2,0x5F);
      v_write(12,12,remitirscr3,0x5F);
      inicializa_registro_intermedio();
      delay(12000);
      v_load(10,12,17,68);
      delay(1000);
      return 1;
   }
   tipo_cursor(15);
   if(no_mismos_datos)
   {
      fila++;
      v_write(11,16,nombre,0x1F);
      /*Recibe el nombre del usuario*/
      numero_caracteres = recibe_un_dato(datos.nombre_usuario,fila,
                                         columna,30,0,0,0,0x1F);
      if(!numero_caracteres)
      { /*Si tecla Esc -> regresa status 1*/
         inicializa_registro_intermedio();
         tipo_cursor(0x2000);
         abandonar_transaccion();
         return 1;
      }
   }
   tipo_cursor(0x2000);
   v_load(6,12,18,69);
   gotoxy(80,25);
   delay(1000);
   v_load(19,58,21,73);
   gotoxy(80,25);
   leer_fecha(datos.fecha_entrega); /*Fecha de hoy*/
   leer_hora(datos.hora_entrega); /*Hora de la transaccion*/
   /*Construye los digitos del a§o tope y de entrega*/
   fecha_e = ( (datos.fecha_entrega[4]&0x0F) << 3 ) +
             ( (datos.fecha_entrega[4]&0x0F) << 1 ) +
             (datos.fecha_entrega[5]&0x0F);
   fecha_t = ( (i_sdc->fecha_tope[4]&0x0F) << 3 ) +
             ( (i_sdc->fecha_tope[4]&0x0F) << 1 ) +
             (i_sdc->fecha_tope[5]&0x0F);
   if(fecha_e > fecha_t) /*Comprueba el a§o de entrega*/
   { /*Entrega extemporanea*/
      opcion = 'E';
   }
   else
   {
      if(fecha_e == fecha_t)
      { /*Es igual el a§o de entrega al de la fecha tope?*/
         /*Arma los digitos del mes de entrega y tope*/
         fecha_e = ( (datos.fecha_entrega[2]&0x0F) << 3 ) +
                   ( (datos.fecha_entrega[2]&0x0F) << 1 ) +
                   (datos.fecha_entrega[3]&0x0F);
         fecha_t = ( (i_sdc->fecha_tope[2]&0x0F) << 3 ) +
                   ( (i_sdc->fecha_tope[2]&0x0F) << 1 ) +
                   (i_sdc->fecha_tope[3]&0x0F);
         if(fecha_e > fecha_t)
         { /*Entrega extemporanea*/
            opcion = 'E';
         }
         else
         {
            if(fecha_e == fecha_t)
            { /*Es igual el mes de entrega al de la fecha tope?*/
               /*Arma los digitos del dia de entrega y tope*/
               fecha_e = ( (datos.fecha_entrega[0]&0x0F) << 3 ) +
                         ( (datos.fecha_entrega[0]&0x0F) << 1 ) +
                         (datos.fecha_entrega[1]&0x0F);
               fecha_t = ( (i_sdc->fecha_tope[0]&0x0F) << 3 ) +
                         ( (i_sdc->fecha_tope[0]&0x0F) << 1 ) +
                         (i_sdc->fecha_tope[1]&0x0F);
               opcion = (fecha_e > fecha_t) ? 'E' : 'T'; /*Comprueba el dia*/
            }
            else
            {
               opcion = 'T'; /*Entrega puntual*/
            }
         }
      }
      else
      {
         opcion = 'T'; /*Entrega puntual*/
      }
   }
   recepcion_de_oferta(opcion);
   return 1; /*Finalizada la transaccion*/
}



/*[]---------------------------------------------[]*
 *  Procedimiento que realiza todos los procesos   *
 *  necesarios para que el usuario introduzca el   *
 *  sobre con su oferta dentro del Buzon y ademas  *
 *  validando que el proceso se realize de forma   *
 *  normal.                                        *
 *                                                 *
 *  Entradas: tipo de entrega -> E extemporanea    *
 *                            -> T en fecha        *
 *  Salidas: ninguna                               *
 *[]---------------------------------------------[]*/
void recepcion_de_oferta(char tipo_de_entrega)
{
   long  int  espera;
   char  opcion,
         *figura1 = "⁄‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹ø",
         *figura2 = "≥±±±±±±±±   PEQUIVEN <>   ±±±±±±±±≥",
         *figura3 = "≥‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹≥",
         *figura4 = "≥  _____________________________ /≥",
         *figura5 = "≥ ≥            ⁄ƒƒƒƒø    ⁄ƒƒƒƒø ≥ ≥",
         *figura6 = "≥ ≥ …ÕÕÕÕÕª    ¿ƒƒƒƒŸ    ¿ƒƒƒƒŸ ≥ ≥",
         *figura7 = "≥ ≥ ∫∞∞∞∞∞∫          ⁄ƒƒƒƒƒƒƒƒø ≥ ≥",
         *figura8 = "≥ ≥ ∫∞∞∞∞∞∫          ¿ƒƒƒƒƒƒƒƒŸ ≥ ≥",
         *figura9 = "≥ ≥_»ÕÕÕÕÕº_____________________≥ ≥",
         *figuraa = "≥/  ‹‹‹‹  ‹                       ≥",
         *figurab = "≥ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ≥",
         *figurac = "≥                                 ≥",
         *figurad = "≥                                 ≥",
         *figurae = "≥                                 ≥",
         *figuraf = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *abrirb1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *abrirb2 = "≥ENTER -> Abrir el buzon≥",
         *abrirb3 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *etique1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *etique2 = "≥  RETIRE LA ETIQUETA   ≥",
         *etique3 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *recibo1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *recibo2 = "≥ RETIRE SU COMPROBANTE ≥",
         *recibo3 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *thanks1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *thanks2 = "≥ GRACIAS POR  SU PUNTUALIDAD ≥",
         *thanks3 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *norecb1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *norecb2 = "≥  SU OFERTA NO FUE RECIBIDA  ≥",
         *norecb3 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *extemp1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *extemp2 = "≥  USTED HA ENTREGADO SU OFERTA EN FECHA TARDIA  ≥",
         *extemp3 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ",
         *espere1 = "⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø",
         *espere2 = "≥ INTRODUZCA EL SOBRE Y ESPERE POR SU COMPROBANTE ≥",
         *espere3 = "¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ";


   if(tipo_de_entrega == 'E')
   { /*Mensajes y comprobante de entrega Extemporanea*/
      v_save(12,14,14,63);
      despliegue(12,14,14,63,0x1F00,1,0,1);
      v_write(12,14,extemp1,0x1F);
      v_write(13,14,extemp2,0x1F);
      v_write(14,14,extemp3,0x1F);
      v_save(20,6,22,30);
      despliegue(20,6,22,30,0x1F00,1,0,0);
      v_write(20,6,recibo1,0x1F);
      v_write(21,6,recibo2,0x1F);
      v_write(22,6,recibo3,0x1F);
      v_save(20,46,22,76);
      despliegue(20,46,22,76,0x1F00,1,0,0);
      v_write(20,46,norecb1,0x1F);
      v_write(21,46,norecb2,0x1F);
      v_write(22,46,norecb3,0x1F);
      imprime_el_comprobante(3);
      delay(2000);
      v_load(20,46,22,76);
      v_load(20,6,22,30);
      v_load(12,14,14,63);
      registrar_transaccion(4);
   }
   else
   {
      tipo_cursor(15);
      v_save(3,23,17,57);
      despliegue(3,23,17,57,0x1F00,1,0,2);
      v_write(3,23,figura1,0x1F);
      v_write(4,23,figura2,0x1F);
      v_write(5,23,figura3,0x1F);
      v_write(6,23,figura4,0x1F);
      v_write(7,23,figura5,0x1F);
      v_write(8,23,figura6,0x1F);
      v_write(9,23,figura7,0x1F);
      v_write(10,23,figura8,0x1F);
      v_write(11,23,figura9,0x1F);
      v_write(12,23,figuraa,0x1F);
      v_write(13,23,figurab,0x1F);
      v_write(14,23,figurac,0x1F);
      v_write(15,23,figurad,0x1F);
      v_write(16,23,figurae,0x1F);
      v_write(17,23,figuraf,0x1F);
      v_save(20,6,22,30);
      despliegue(20,6,22,30,0x1F00,1,0,0);
      v_write(20,6,etique1,0x1F);
      v_write(21,6,etique2,0x1F);
      v_write(22,6,etique3,0x1F);
      gotoxy(40,8);
      imprime_la_etiqueta();
      delay(2000);
      despliegue(20,6,22,30,0x1F00,1,0,0);
      v_write(20,6,abrirb1,0x1F);
      v_write(21,6,abrirb2,0x1F);
      v_write(22,6,abrirb3,0x1F);
      gotoxy(48,9);
      for(espera = 800000;((opcion = keypressed()) != 0x0D) && espera;espera--)
      { /*Espera por una opcion*/
         ;
      }
      if(opcion == 0x0D)
      { /*Tecla ENTER oprimida?*/
         v_load(20,6,22,30);
         v_save(20,14,22,64);
         despliegue(20,14,22,64,0x1F00,1,0,1);
         v_write(20,14,espere1,0x1F);
         v_write(21,14,espere2,0x1F);
         v_write(22,14,espere3,0x1F);
         delay(1000);
         if(!hay_casilla_asignada())
         { /*Mensajes y comprobante de transaccion no completada*/
            v_load(20,14,22,64);
            v_save(20,6,22,30);
            despliegue(20,6,22,30,0x1F00,1,0,0);
            v_write(20,6,recibo1,0x1F);
            v_write(21,6,recibo2,0x1F);
            v_write(22,6,recibo3,0x1F);
            v_save(20,46,22,76);
            despliegue(20,46,22,76,0x1F00,1,0,0);
            v_write(20,46,norecb1,0x1F);
            v_write(21,46,norecb2,0x1F);
            v_write(22,46,norecb3,0x1F);
            gotoxy(50,8);
            imprime_el_comprobante(2);
            delay(2000);
            registrar_transaccion(2);
         }
         else
         { /*Mensajes y comprobante de entrega Puntual*/
            v_load(20,14,22,64);
            v_save(20,6,22,30);
            despliegue(20,6,22,30,0x1F00,1,0,0);
            v_write(20,6,recibo1,0x1F);
            v_write(21,6,recibo2,0x1F);
            v_write(22,6,recibo3,0x1F);
            v_save(20,46,22,76);
            despliegue(20,46,22,76,0x1F00,1,0,0);
            v_write(20,46,thanks1,0x1F);
            v_write(21,46,thanks2,0x1F);
            v_write(22,46,thanks3,0x1F);
            gotoxy(50,8);
            imprime_el_comprobante(1);
            delay(2000);
            registrar_transaccion(1);
         }
         v_load(20,46,22,76);
         v_load(20,6,22,30);
      }
      else
      {
         v_load(20,6,22,30);
      }
      v_load(3,23,17,57);
   }
   tipo_cursor(0x2000);
   inicializa_registro_intermedio();
   busca_la_casilla(PUERTO_DE.MOTORES,casilla_permanente);
}



/*[]----------------------------------------------[]*
 *  Procedimiento que dirige todas las acciones de  *
 *  transferencia de registros de transacciones y   *
 *  de recepcion de comandos asi como tambien el    *
 *  envio al MCT de mensajes de advertencia.        *
 *                                                  *
 *  Entradas: ninguna                               *
 *  Salidas:  ninguna                               *
 *[]----------------------------------------------[]*/
int interfaz_con_MCT()
{
   register int  indice=0,
                 intentos,
                 interpretacion;
   long int  espera;
   unsigned char  byte,
                  fd,
                  sd,
                  caracter,
                  comando[80],
                  *buzon_trabaja = "* DISCULPE EL BUZON ESTA MOMENTANEAMENTE FUERA DE SERVICIO *",
                  *buzon_atiende = "*     OPRIMA LA TECLA [ENTER] PARA INICIAR OPERACIONES     *",
                  *prompt =        "\n\rBUZON>",
                  *error_comand =  "\n\rCOMANDO ERRONEO\n",
                  *error_param =   "\n\rPARAMETRO ERRONEO\n",
                  *ayuda_extra =   "\n\rSintaxis: EXTRAER [casilla 1],...,[casilla N]\n",
                  *ayuda_elimi =   "\n\rSintaxis: ELIMINAR [numero de SDC]\n",
                  *ayuda_fecha =   "\n\rSintaxis: FECHA [dia]/[mes]/[a#o]\n",
                  *ayuda_hora =    "\n\rSintaxis: HORA [hora]:[minutos]:[segundos]\n",
                  *ayuda_horar =   "\n\rSintaxis: HORARIO {Hora de inicio=}[hora]:[minutos]:[segundos] {Hora de finalizacion=}[hora]:[minutos]:[segundos]\n",
                  *comandos1 =     "\n\n\rCOMANDOS DEL BUZON:",
                  *comandos2 =     "\n\rELIMINAR          ---> ELIMINAR CUALQUIER REGISTRO BASICO EN EL BUZON.",
                  *comandos3 =     "\n\rEN_SERVICIO       ---> COLOCA AL BUZON EN EL ESTADO FUERA DE SERVICIO.",
                  *comandos4 =     "\n\rEXTRAER           ---> ABRIR CUALQUIER CASILLA QUE ESTE OCUPADA O NO.",
                  *comandos5 =     "\n\rFECHA             ---> ACTUALIZA LA FECHA EN EL SETUP DEL BUZON.",
                  *comandos6 =     "\n\rFUERA_DE_SERVICIO ---> COLOCA AL BUZON EN EL ESTADO FUERA DE SERVICIO.",
                  *comandos7 =     "\n\rHORA              ---> ACTUALIZA LA HORA EN EL SETUP DEL BUZON.",
                  *comandos8 =     "\n\rHORARIO           ---> PERMITE CAMBIAR EL HORARIO DE TRABAJO DEL BUZON.",
                  *comandos9 =     "\n\rVERFECHA          ---> CONSULTAR LA FECHA EN EL SETUP DEL BUZON.",
                  *comandosa =     "\n\rVERHORA           ---> CONSULTAR LA HORA EN EL SETUP DEL BUZON.";


   if((comando[indice] = recibir(PUERTO_DE.MCT)) != NO_HAY_LINEA)
   {
      if((archivo_existente != 0) && (comando[indice] == 0) && !fuera_de_servicio)
      {
         /*Hay transacciones pendientes por enviar y la linea
           esta libre para hacerlo*/
         byte = 0x07;
         enviar(PUERTO_DE.MCT,byte); /*Peticion de transferencia*/
         for(espera = 80000;!(byte = recibir(PUERTO_DE.MCT)) && espera;espera--)
         { /*Espera hasta recibir el reconocimiento*/
            ;
         }
         if(!espera) /*MCT no responde*/
         {
            return 0; /*Aborta la transferencia*/
         }
         if(byte != 0x06) /*Si no es el caracter de reconocimiento*/
         {
            byte = 0x07;
            enviar(PUERTO_DE.MCT,byte); /*Envia la orden critica de transferencia*/
            for(espera = 80000;!(byte = recibir(PUERTO_DE.MCT)) && espera;espera--)
            { /*Espera hasta recibir el reconocimiento*/
               ;
            }
            if(!espera && (byte != 0x06))
            {
               return 0; /*Aborta la transferencia*/
            }
            if(byte != 0x06) /*Si no se recibe reconocimiento*/
            {
               return 0; /*Aborta la transferencia*/
            }
         }
         v_write(22,11,buzon_trabaja,0x1F);
         for(intentos = 2;!(transacciones = open_file(buzon04,0)) && intentos;intentos--)
         {
            ;
         }
         /*Transfiere el archivo de transacciones registradas*/
         while(read_file(transacciones,sizeof(datos),&datos))
         {
            byte = datos.tipo | 0x30;
            enviar(PUERTO_DE.MCT,byte); /*Envia el Tipo de Oferta de la Transaccion*/
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Envia el numero de la SDC*/
            if(!envia_al_MCT_campo(datos.sdc))
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Envia el numero de RIF*/
            if(!envia_al_MCT_campo(datos.rif))
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Prepara el nombre del usuario*/
            for(indice = 0;datos.nombre_usuario[indice] != '\0';indice++)
            {
               ;
            }
            while(indice < 25)
            {
               datos.nombre_usuario[indice++] = 0x20;
            }
            datos.nombre_usuario[indice] = '\0';
            /*Envia el nombre del usuario*/
            if(!envia_al_MCT_campo(datos.nombre_usuario))
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            enviar(PUERTO_DE.MCT,'1'); /*Envia el primer digito del Siglo*/
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            enviar(PUERTO_DE.MCT,'9'); /*Envia el segundo digito del Siglo*/
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Envia el primer digito del a§o*/
            enviar(PUERTO_DE.MCT,datos.fecha_entrega[4]);
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Envia el segundo digito del a§o*/
            enviar(PUERTO_DE.MCT,datos.fecha_entrega[5]);
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Envia el primer digito del dia*/
            enviar(PUERTO_DE.MCT,datos.fecha_entrega[0]);
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Envia el segundo digito del dia*/
            enviar(PUERTO_DE.MCT,datos.fecha_entrega[1]);
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Envia el primer digito del mes*/
            enviar(PUERTO_DE.MCT,datos.fecha_entrega[2]);
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Envia el segundo digito del mes*/
            enviar(PUERTO_DE.MCT,datos.fecha_entrega[3]);
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Envia la hora de la transaccion*/
            if(!envia_al_MCT_campo(datos.hora_entrega))
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            /*Envia digitos de ajuste*/
            enviar(PUERTO_DE.MCT,'0');
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            enviar(PUERTO_DE.MCT,'0');
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            enviar(PUERTO_DE.MCT,'0');
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            enviar(PUERTO_DE.MCT,'0');
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            byte = datos.status | 0x30;
            enviar(PUERTO_DE.MCT,byte); /*Envia el status de la transaccion*/
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            byte = datos.casilla;
            sd = (byte / 10) | 0x30; /*Digito de las decenas*/
            fd = (byte % 10) | 0x30; /*Digito de las unidades*/
            enviar(PUERTO_DE.MCT,sd); /*Envia el numero de casilla*/
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            enviar(PUERTO_DE.MCT,fd);
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            enviar(PUERTO_DE.MCT,'\r'); /*Final de un renglon del archivo*/
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
            enviar(PUERTO_DE.MCT,'\n');
            for(espera = 80000;!recibir(PUERTO_DE.MCT) && espera;espera--)
            {
               ;
            }
            if(!espera && !byte)
            { /*No hay contestacion por el MCT*/
               close_file(transacciones);
               v_write(22,11,buzon_atiende,0x0B);
               return 0;
            }
         }
         enviar(PUERTO_DE.MCT,0x16); /*Envia el caracter de finalizacion*/
         espera = 80000;
         while(!(byte = recibir(PUERTO_DE.MCT)) && espera)
         {
            espera--;
         }
         if(!espera && !byte)
         { /*No hay contestacion por el MCT*/
            close_file(transacciones);
            v_write(22,11,buzon_atiende,0x0B);
            return 0;
         }
         delete_file(buzon04);
         archivo_existente = 0;
         inicializa_registro_intermedio();
         v_write(22,11,buzon_atiende,0x0B);
      }
      else
      {
         if(comando[indice])
         {
            if((comando[indice] != '\r') && (comando[indice] != '?'))
            {
               v_write(22,11,buzon_trabaja,0x1F);
               do
               { /*Recepcion de comandos*/
                  if((comando[indice] >= 'a') && (comando[indice] <= 'z'))
                  {
                     comando[indice] -= 0x20;
                  }
                  enviar(PUERTO_DE.MCT,comando[indice]);
                  ((comando[indice] == 0x08) && indice) ? indice-- : indice++;
                  if(indice >= 80)
                  {
                     indice = 0;
                  }
                  for(espera = 400000;!(comando[indice] = recibir(PUERTO_DE.MCT)) &&
                                       espera;espera--)
                  {
                     ;
                  }
                  if(!espera && !comando[indice])
                  {
                     v_write(22,11,buzon_atiende,0x0B);
                     return 0;
                  }
               }while(comando[indice] != '\r');
               enviar(PUERTO_DE.MCT,'\r');
               delay(2000);
               indice = 0;
               interpretacion = interpreta_ejecuta_comando(comando);
               switch(interpretacion)
               {
                  case 1: envia_comentarios_MCT(error_comand);
                          break;
                  case 2: envia_comentarios_MCT(error_param);
                          break;
                  case 3: envia_comentarios_MCT(ayuda_extra);
                          break;
                  case 4: envia_comentarios_MCT(ayuda_elimi);
                          break;
                  case 5: envia_comentarios_MCT(ayuda_fecha);
                          break;
                  case 6: envia_comentarios_MCT(ayuda_hora);
                          break;
                  case 7: envia_comentarios_MCT(ayuda_horar);
                          break;
               }
               if(fuera_de_servicio)
               {
                  v_write(22,11,buzon_trabaja,0x1F);
               }
               else
               {
                  v_write(22,11,buzon_atiende,0x0B);
               }
            }
            if(comando[indice] == '?')
            {
               envia_comentarios_MCT(comandos1);
               envia_comentarios_MCT(comandos2);
               envia_comentarios_MCT(comandos3);
               envia_comentarios_MCT(comandos4);
               envia_comentarios_MCT(comandos5);
               envia_comentarios_MCT(comandos6);
               envia_comentarios_MCT(comandos7);
               envia_comentarios_MCT(comandos8);
               envia_comentarios_MCT(comandos9);
               envia_comentarios_MCT(comandosa);
            }
            envia_comentarios_MCT(prompt);
         }
         else
         {
            if(casillas_disponibles <= MINIMO_DISPONIBLE && !urgencia_atendida)
            { /*Si el numero de casillas disponibles es menor a cuatro
                y el MCT no responde a la alerta*/
               caracter = 0x18;
               enviar(PUERTO_DE.MCT,caracter);
               for(espera = 80000,caracter = 0;((caracter = recibir(PUERTO_DE.MCT)) != 0x18) &&
                                               espera;espera--)
               {
                  ;
               }
               if(caracter == 0x18)
               { /*El MCT atendio al llamado*/
                  urgencia_atendida = 1;
               }
            }
            else
            {
               delay(100);
            }
         }
      }
   }
   else
   {
      delay(100);
   }
   return 0;
}



void abandonar_transaccion()
{
   v_load(6,12,18,69);
   gotoxy(1,25);
   delay(500);
   v_load(19,58,21,73);
   gotoxy(1,25);
   delay(500);
}



void inicializa_registro_intermedio()
{
   register int i;

   for(i = 0;i < 41;datos.nombre_proveedor[i++] = '\0');
   for(i = 0;i < 26;datos.nombre_usuario[i++] = '\0');
   for(i = 0;i < 11;datos.rif[i++] = '\0');
}



/*[]---------------------------------------[]*
 *  Registro de transacciones con un status  *
 *  que indica:                              *
 *              1 -> Transaccion completada  *
 *              2 ->     ||      no  ||      *
 *              3 -> Oferta entregada antes  *
 *              4 -> Entrega extemporanea    *
 *[]---------------------------------------[]*/
void registrar_transaccion(int status_de_transaccion)
{
   unsigned char  datos_mct;
   int  intentos;


   if(status_de_transaccion == 1)
   { /*Transaccion completada?*/
      i_inv->ofertas_entregadas += tipo_de_oferta;
   }
   for(intentos = 2;!(datos_mct = open_file(buzon01,2)) && intentos;intentos--)
   { /*Abre el archivo principal de datos*/
      ;
   }
   seek_file(datos_mct,sizeof(*i_sdc)*datos.file_pos,0);
   write_file(datos_mct,sizeof(*i_sdc),i_sdc); /*Registra el tipo de oferta*/
   close_file(datos_mct);
   datos.status=status_de_transaccion;
   for(intentos = 2;!(transacciones = open_file(buzon04,2)) && intentos;intentos--)
   { /*Abre el archivo de registros de transacciones*/
      ;
   }
   if(!intentos && !transacciones)
   {
      transacciones = create_file(buzon04);
   }
   seek_file(transacciones,0,2);
   write_file(transacciones,sizeof(datos),&datos); /*Registra la transaccion*/
   close_file(transacciones);
   archivo_existente = 1; /*Hay transacciones por enviar al MCT*/
}



/*[]-------------------------------------------------------[]*
 *  Procedimiento que indica en cual casilla se introducira  *
 *  el sobre con la oferta, buscando primero si para la SDC  *
 *  actual y tipo de oferta actual hay una casilla asignada  *
 *  anteriormente.                                           *
 *                                                           *
 *  Entradas: ninguna                                        *
 *  Salidas:  regresa 1 -> el sobre se introdujo             *
 *                    0 -> el sobre no se introdujo          *
 *[]-------------------------------------------------------[]*/
int hay_casilla_asignada()
{
   register int  indice;
   int  intentos,
        ind_casilla;


   /*Busca la primera casilla disponible o una casilla
     asignada previamente al numero de SDC de la oferta*/
   for(indice = 0;no_son_iguales(datos.sdc,casillas[indice].sdc) &&
                  (indice < 20);
                  indice++);
   if(indice == 20)
   {
      indice = primero_disponible;
   }
   casilla_nueva = indice + 1;
   busca_la_casilla(PUERTO_DE.MOTORES,casilla_nueva);
   if(entrada_de_sobre(PUERTO_DE.MOTORES))
   { /*Registra el numero de casilla donde se deposito*/
      datos.casilla = casilla_nueva;
      if(indice == primero_disponible)
      {
         s_copy(datos.sdc,casillas[indice].sdc);
         casillas[indice].tipo = datos.tipo;
         while(casillas[++primero_disponible].tipo)
         { /*Coloca primero_disponible apuntando a la siguiente casilla disponible*/
            ;
         }
         for(intentos = 2;!(backup_casillas = open_file(buzon02,2)) &&
                          intentos;intentos--)
         {
            ;
         }
         if(!backup_casillas)
         {
            backup_casillas = create_file(buzon02);
            for(ind_casilla = 1;ind_casilla < 20;ind_casilla++)
            {
               casillas[ind_casilla].tipo = 0;
            }
         }
         ind_casilla = 19;
         while(!casillas[ind_casilla].tipo && ind_casilla)
         {
            ind_casilla--;
         }
         casilla_permanente = punto_medio(++ind_casilla);
         for(indice = 0;indice < 20;indice++)
         {
            write_file(backup_casillas,sizeof(casillas[indice]),
                       &casillas[indice]);
         }
         close_file(backup_casillas);
         if(casillas[indice].tipo == 0)
         { /*Esta disponible la casilla?*/
            casillas_disponibles--; /*Una casilla disponible menos*/
         }
         if(casillas_disponibles <= MINIMO_DISPONIBLE)
         { /*Envia nuevamente la advertencia al MCT*/
            urgencia_atendida = 0;
         }
      }
      indice = 1; /*Regresa status 1*/
   }
   else
   {
      datos.casilla = 0;
      indice = 0; /*Regresa status 0*/
   }
   return indice;
}



void imprime_la_etiqueta()
{
   register int  indice_dato,
                 indice_forma,
                 intentos;
   int  longitud_strg,
        impre_etiquetas,
        aetiquetas,
        tercera_parte,
        decimal_hora;
   char  caracter,
         *compr01 =   "               ECONOMICA                ",
         *sdcyrif =   "    XXXXXXXX              YYYYYYYYYYY   ",
         *represe =   "                                        ",
         *fechahr =   "    00/00/00              00:00:00 a.m. ",
         *printer_1 = "COM1",
         *etiquetas = "ETIQUETA.DAT";


   for(intentos = 2;!(aetiquetas = open_file(etiquetas,2)) && intentos;intentos--)
   {
      ;
   }
   seek_file(aetiquetas,0x43,0); /*Posiciona en el campo de tipo de
                                   oferta*/
   write_file(aetiquetas,s_leng(compr01),compr01);
   /*Construye la linea de campos SDC Y RIF*/
   for(indice_dato = 0,indice_forma = 4;
       indice_dato < 8;indice_dato++,indice_forma++)
   {
      sdcyrif[indice_forma] = datos.sdc[indice_dato];
   }
   sdcyrif[26] = datos.rif[0];
   sdcyrif[27] = '-';
   for(indice_dato = 1,indice_forma = 28;
       indice_dato < 10;indice_dato++,indice_forma++)
   {
      sdcyrif[indice_forma] = datos.rif[indice_dato];
   }
   seek_file(aetiquetas,0x9B,0); /*Coloca el numero de la SDC y
                                   el numero del RIF*/
   write_file(aetiquetas,s_leng(sdcyrif),sdcyrif);
   /*Limpia la forma para el nombre de la empresa*/
   for(indice_forma = 0;indice_forma < 40;indice_forma++)
   {
      represe[indice_forma] = ' ';
   }
   /*Construye el nombre de la empresa*/
   longitud_strg = s_leng(datos.nombre_proveedor) - 1;
   tercera_parte = punto_medio(40-longitud_strg) - 1;
   for(indice_forma = 0;indice_forma < indice_dato;indice_forma++)
   {
      represe[indice_forma] = ' ';
   }
   for(indice_forma = tercera_parte,indice_dato = 0;
       indice_forma <= longitud_strg+tercera_parte;
       indice_dato++,indice_forma++)
   {
      represe[indice_forma] = datos.nombre_proveedor[indice_dato];
   }
   seek_file(aetiquetas,0xE9,0); /*Coloca el nombre de la empresa*/
   write_file(aetiquetas,s_leng(represe),represe);
   /*Construye la linea para la fecha y la hora de la transaccion*/
   indice_forma = 4;
   indice_dato = 0; /*Forma los digitos del dia*/
   fechahr[indice_forma++] = datos.fecha_entrega[indice_dato++];
   fechahr[indice_forma] = datos.fecha_entrega[indice_dato++];
   indice_forma += 2; /*Forma los digitos del mes*/
   fechahr[indice_forma++] = datos.fecha_entrega[indice_dato++];
   fechahr[indice_forma] = datos.fecha_entrega[indice_dato++];
   indice_forma += 2; /*Forma los digitos del a§o*/
   fechahr[indice_forma++] = datos.fecha_entrega[indice_dato++];
   fechahr[indice_forma] = datos.fecha_entrega[indice_dato++];
   indice_forma = 26;
   indice_dato = 0;
   decimal_hora = ((datos.hora_entrega[0]&0x0F) << 3) +
                  ((datos.hora_entrega[0]&0x0F) << 1) +
                  (datos.hora_entrega[1]&0x0F);
   if(decimal_hora > 12) /*Forma los digitos de la hora*/
   { /*Expresa la hora en a.m. y p.m.*/
      decimal_hora -= 12;
      fechahr[35] = 'p';
      fechahr[indice_forma++] = (decimal_hora/10) | 0x30;
      fechahr[indice_forma++] = (decimal_hora - (decimal_hora/10)) | 0x30;
      indice_dato = 2;
   }
   else
   {
      fechahr[indice_forma++] = datos.hora_entrega[indice_dato++];
      fechahr[indice_forma++] = datos.hora_entrega[indice_dato++];
      fechahr[35] = 'a';
   }
   fechahr[indice_forma++] = ':'; /*Forma los digitos de los minutos*/
   fechahr[indice_forma++] = datos.hora_entrega[indice_dato++];
   fechahr[indice_forma++] = datos.hora_entrega[indice_dato++];
   fechahr[indice_forma] = ':';
   fechahr[36] = '.';
   fechahr[37] = 'm';
   fechahr[38] = '.';
   seek_file(aetiquetas,0x13B,0);
   write_file(aetiquetas,s_leng(fechahr),fechahr);
   seek_file(aetiquetas,0,0);
   impre_etiquetas = open_file(printer_1,1);
   while(read_file(aetiquetas,1,&caracter))
   {
      write_file(impre_etiquetas,1,&caracter);
   }
   close_file(impre_etiquetas);
   close_file(aetiquetas);
}



/*[]--------------------------------------[]*
 *  El estado de la transaccion puede ser:  *
 *          1 = Transaccion completada      *
 *          2 = Transaccion no completada   *
 *          3 = Extemporanea                *
 *[]--------------------------------------[]*/
void imprime_el_comprobante(int estado)
{
   register int  indice_dato,
                 indice_forma,
                 intentos;
   int  longitud_strg,
        impre_recibos,
        arecibos,
        tercera_parte,
        decimal_hora;
   char  caracter,
         *compr01 =   "               ECONOMICA                ",
         *sdcyrif =   "    XXXXXXXX              YYYYYYYYYYY   ",
         *represe =   "                                        ",
         *fechahr =   "    00/00/00              00:00:00      ",
         *compr03 =   "             EXTEMPORANEA               ",
         *compr04 =   "              COMPLETADA                ",
         *compr05 =   "            NO  COMPLETADA              ",
         *compr06 =   "  ENTREGA POSTERIOR A FECHA DE CIERRE   ",
         *compr07 =   "         GRACIAS POR SU OFERTA          ",
         *compr08 =   " EL SOBRE CON SU OFERTA NO FUE RECIBIDO ",
		   *printer_2 = "COM2",
         *recibos =   "RECIBO.DAT";


   for(intentos = 2;!(arecibos = open_file(recibos,2)) && intentos;intentos--)
   {
      ;
   }
   /*Posiciona en el campo de tipo de oferta*/
   seek_file(arecibos,149,0);
   write_file(arecibos,s_leng(compr01),compr01);
   /*Construye la linea de campos SDC y RIF*/
   for(indice_dato = 0,indice_forma = 4;
       indice_dato < 8;indice_dato++,indice_forma++)
   {
      sdcyrif[indice_forma] = datos.sdc[indice_dato];
   }
   sdcyrif[26] = datos.rif[0];
   sdcyrif[27] = '-';
   for(indice_dato = 1,indice_forma = 28;
       indice_dato < 10;indice_dato++,indice_forma++)
   {
      sdcyrif[indice_forma] = datos.rif[indice_dato];
   }
   /*Coloca el numero de la SDC y el numero del RIF*/
   seek_file(arecibos,237,0);
   write_file(arecibos,s_leng(sdcyrif),sdcyrif);
   /*Construye el nombre del usuario*/
   for(indice_forma = 0;indice_forma < 40;indice_forma++)
   {
      represe[indice_forma] = ' ';
   }
   longitud_strg = s_leng(datos.nombre_usuario) - 1;
   tercera_parte = punto_medio(40-longitud_strg) - 1;
   for(indice_forma = 0;indice_forma < indice_dato;indice_forma++)
   {
      represe[indice_forma] = ' ';
   }
   for(indice_forma = tercera_parte,indice_dato = 0;
       indice_forma <= longitud_strg+tercera_parte;
       indice_dato++,indice_forma++)
   {
      represe[indice_forma] = datos.nombre_usuario[indice_dato];
   }
   seek_file(arecibos,0x139,0); /*Coloca el nombre del usuario*/
   write_file(arecibos,s_leng(represe),represe);
   /*Limpia la forma para el nombre de la empresa*/
   for(indice_forma = 0;indice_forma < 40;indice_forma++)
   {
      represe[indice_forma] = ' ';
   }
   /*Construye el nombre de la empresa*/
   longitud_strg = s_leng(datos.nombre_proveedor) - 1;
   tercera_parte = punto_medio(40-longitud_strg) - 1;
   for(indice_forma = 0;indice_forma < indice_dato;indice_forma++)
   {
      represe[indice_forma] = ' ';
   }
   for(indice_forma = tercera_parte,indice_dato = 0;
       indice_forma <= longitud_strg+tercera_parte;
       indice_dato++,indice_forma++)
   {
      represe[indice_forma] = datos.nombre_proveedor[indice_dato];
   }
   seek_file(arecibos,0x187,0); /*Coloca el nombre de la empresa*/
   write_file(arecibos,s_leng(represe),represe);
   /*Construye la linea para la fecha y la hora de la transaccion*/
   indice_forma = 4;
   indice_dato = 0; /*Forma los digitos del dia*/
   fechahr[indice_forma++] = datos.fecha_entrega[indice_dato++];
   fechahr[indice_forma] = datos.fecha_entrega[indice_dato++];
   indice_forma += 2; /*Forma los digitos del mes*/
   fechahr[indice_forma++] = datos.fecha_entrega[indice_dato++];
   fechahr[indice_forma] = datos.fecha_entrega[indice_dato++];
   indice_forma += 2; /*Forma los digitos del a§o*/
   fechahr[indice_forma++] = datos.fecha_entrega[indice_dato++];
   fechahr[indice_forma] = datos.fecha_entrega[indice_dato++];
   indice_forma = 26;
   indice_dato = 0;
   decimal_hora = ((datos.hora_entrega[0]&0x0F) << 3) +
                  ((datos.hora_entrega[0]&0x0F) << 1) +
                  (datos.hora_entrega[1]&0x0F);
   if(decimal_hora > 12)
   {
      decimal_hora -= 12;
      fechahr[35] = 'p';
      fechahr[indice_forma++] = (decimal_hora/10) | 0x30;
      fechahr[indice_forma++] = (decimal_hora - (decimal_hora/10)) | 0x30;
      indice_dato = 2;
   }
   else
   {
      fechahr[indice_forma++] = datos.hora_entrega[indice_dato++];
      fechahr[indice_forma++] = datos.hora_entrega[indice_dato++];
      fechahr[35] = 'a';
   }
   fechahr[indice_forma++] = ':'; /*Forma los digitos de los minutos*/
   fechahr[indice_forma++] = datos.hora_entrega[indice_dato++];
   fechahr[indice_forma++] = datos.hora_entrega[indice_dato++];
   fechahr[indice_forma] = ':';
   fechahr[36] = '.';
   fechahr[37] = 'm';
   fechahr[38] = '.';
   seek_file(arecibos,0x1D9,0);
   write_file(arecibos,s_leng(fechahr),fechahr);
   /*Construye la linea para el estado de la transaccion*/
   seek_file(arecibos,0x229,0);
   switch(estado)
   {
      case 1: write_file(arecibos,s_leng(compr04),compr04);
              break; /*Transaccion completada*/
      case 2: write_file(arecibos,s_leng(compr05),compr05);
              break; /*Transaccion no completada*/
      case 3: write_file(arecibos,s_leng(compr03),compr03);
              break; /*Entrega extemporanea*/
   }
   /*Construye la linea para el comentario de la transaccion*/
   seek_file(arecibos,0x257,0);
   switch(estado)
   {
      case 1: write_file(arecibos,s_leng(compr07),compr07);
              break; /*Transaccion completada*/
      case 2: write_file(arecibos,s_leng(compr08),compr08);
              break; /*Transaccion no completada*/
      case 3: write_file(arecibos,s_leng(compr06),compr06);
              break; /*Entrega extemporanea*/
   }
   seek_file(arecibos,0,0);
   impre_recibos = open_file(printer_2,1);
   while(read_file(arecibos,1,&caracter))
   {
      write_file(impre_recibos,1,&caracter);
   }
   close_file(impre_recibos);
   close_file(arecibos);
}



/*[]-----------------------------------------[]*
 *  Procedimiento que interpreta los comandos  *
 *  del terminal de control y los ejecuta.     *
 *                                             *
 *  Entrada: Linea de comando desde el MCT     *
 *  Salida:  0 --> Comando ejecutado.          *
 *           1 --> Comando no reconocido.      *
 *           2 --> Parametros erroneos.        *
 *           3 --> Ayuda para EXTRAER.         *
 *           4 --> Ayuda para ELIMINAR.        *
 *           5 --> Ayuda para FECHA.           *
 *           6 --> Ayuda para HORA.            *
 *           7 --> Ayuda para HORARIO.         *
 *[]-----------------------------------------[]*/
int interpreta_ejecuta_comando(char *linea)
{
   register registro_sdc  *indice_secundario;
   long int  espera;
   int  sdcs_leidos,
        casilla[20],
        bz03,
        bz_disponibles,
        datos_mct,
        datos_buzon,
        casilla_origen,
        casilla_destino,
        parpadeo = 0,
        pd,
        indice = 0,
        i = 0,
        intentos,
        datos_intermedio;
   char  caracter_control,
         buffer_sim[74],
         fecha_transferida[7],
         hora_transferida[5],
         nulo[11] =  "\0\0\0\0\0\0\0\0\0\0\0",
         token[15] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";


   /*Busca la primera palabra del texto*/
   while(linea[indice] == 0x20)
   {
      indice++;
   }
   if(linea[indice] == 0x0D)
   {
      return 0;
   }
   else
   {
      /*Forma la primera palabra*/
      while((linea[indice] != 0x20) && (linea[indice] != 0x0D))
      {
         token[i++] = linea[indice++];
      }
      token[i] = '\0';
      i = 0;
      if(son_iguales("EXTRAER\0",token)) /*BUZON>EXTRAER*/
      {
         for(;;)
         {
            while((linea[indice] == 0x20) || (linea[indice] == ','))
            {
               indice++;
            }
            if(linea[indice] == 0x0D)
            {
               if(!i)
               {
                  return 3; /*Envia mensaje de ayuda*/
               }
               else
               {
                  /*Indicacion luminosa de inicio de extraccion.
                    Espera a que la puerta se cierre (si esta abierta)*/
                  while(datos_de_puerta(PUERTO_DE.MECANISMO) & 0x01)
                  {
                     parpadeo =! parpadeo;
                     datos_a_puerta(PUERTO_DE.MECANISMO,0,parpadeo,1,0,0);
                     dead_time(500);
                  }
                  /*Prepara la variable de casilla a utilizar*/
                  casilla_origen = casilla_permanente;
                  for(indice = 0;indice < i;indice++)
                  {
                    /*El movimiento de busqueda debe realizarse
                      tomando en cuenta los bordes de la polea
                      que esta sujeta al motor y la cual da el
                      movimiento al carrusel*/
                     if(casilla[indice] <= 5)
                     {
                        casilla[indice] += 20;
                     }
                     /*Indicacion al usuario para que oprima
                       el boton de arranque*/
                     datos_a_puerta(PUERTO_DE.MECANISMO,0,0,1,0,0);
                     while(!(datos_de_puerta(PUERTO_DE.MECANISMO)&0x02))
                     {
                        ;
                     }
                     /*Realizando la busqueda de la siguiente
                       casilla*/
                     datos_a_puerta(PUERTO_DE.MECANISMO,1,0,1,0,0);
                     /*La diferencia de 5 casillas desde la
                       posicion de los lectores opticos del
                       carrusel hasta la puerta de extraccion
                       obliga a realizar el siguiente calculo*/
                     if(casilla[indice] != (casilla_origen+5))
                     {
                        casilla_destino = casilla[indice] - 5;
                        busca_la_casilla(PUERTO_DE.MOTORES,casilla_destino);
                        casilla_origen = casilla_destino;
                        /*Indicacion para que el usuario extraiga
                          el contenido de la casilla*/
                        datos_a_puerta(PUERTO_DE.MECANISMO,0,1,1,1,1);
                        while(!(datos_de_puerta(PUERTO_DE.MECANISMO)&0x01))
                        {
                           ;
                        }
                        datos_a_puerta(PUERTO_DE.MECANISMO,0,1,1,0,0);
                        dead_time(100);
                        /*Espera a que la puerta este cerrada
                          para iniciar una nueva busqueda*/
                        while(datos_de_puerta(PUERTO_DE.MECANISMO) & 0x01)
                        {
                           parpadeo =! parpadeo;
                           datos_a_puerta(PUERTO_DE.MECANISMO,0,parpadeo,1,0,0);
                           dead_time(500);
                        }
                     }
                  }
                  /*Limpia los bits del mecanismo*/
                  datos_a_puerta(PUERTO_DE.MECANISMO,0,0,0,0,0);
                  /*Regresa a la casilla original*/
                  busca_la_casilla(PUERTO_DE.MOTORES,casilla_permanente);
                  return 0;
               }
            }
            if((linea[indice] < 0x30) || (linea[indice] > 0x39))
            {
               return 2; /*Parametro erroneo*/
            }
            if((linea[indice+1] != 0x20) && (linea[indice+1] != 0x0D) &&
               (linea[indice+1] != 0x2C))
            {
               if((linea[indice+1] < 0x30) && (linea[indice+1] > 0x39))
               {
                  return 2;
               }
               casilla[i] = ((linea[indice]&0x0F)<<3) +
                            ((linea[indice]&0x0F)<<1) +
                            (linea[indice+1]&0x0F);
               indice += 2;
            }
            else
            {
               casilla[i] = linea[indice++] & 0x0F;
            }
            if((casilla[i] > 20) || (casilla[i] == 0))
            {
               return 2;
            }
            i++;
         }
      }
      else
      {
         if(son_iguales("ELIMINAR\0",token))
         { /*BUZON>ELIMINAR*/
            while(linea[indice] == 0x20)
            {
               indice++; /*Busca el numero de SDC*/
            }
            if(linea[indice] == 0x0D)
            {
               return 4; /*Envia mensaje de ayuda*/
            }
            i = 0;
            while((linea[indice] != 0x20) && (linea[indice] != 0x0D))
            {
               token[i++] = linea[indice++]; /*Forma la palabra SDC*/
            }
            token[i] = '\0';
            if((i != 8) || !numero_de_sdcs)
            {
               return 2;
            }
            for(indice_secundario = nodo_sdc;
                (indice_secundario <= numero_de_sdcs) &&
                (no_son_iguales(indice_secundario->sdc,token));
                indice_secundario++)
            {
               ;
            }
            if(indice_secundario > numero_de_sdcs)
            {
               return 2;
            }
            if(numero_de_sdcs == nodo_sdc)
            {
               delete_file(buzon01);
               delete_file(buzon02);
            }
            else
            {
               datos_intermedio = create_file(buzon00);
               for(i_sdc = nodo_sdc;i_sdc <= indice_secundario-1;i_sdc++)
               {
                  write_file(datos_intermedio,sizeof(*i_sdc),i_sdc);
               }
               if(i_sdc < numero_de_sdcs)
               {
                  for(i_sdc++;i_sdc <= numero_de_sdcs;i_sdc++)
                  {
                     write_file(datos_intermedio,sizeof(*i_sdc),i_sdc);
                  }
               }
               seek_file(datos_intermedio,0,0);
               datos_mct = create_file(buzon01);
               for(;;)
               {
                  if(!read_file(datos_intermedio,
                     sizeof(nodo_sdc[NUM_SDCS]),&nodo_sdc[NUM_SDCS]))
                  {
                     break;
                  }
                  write_file(datos_mct,sizeof(nodo_sdc[NUM_SDCS]),
                             &nodo_sdc[NUM_SDCS]);
               }
               close_file(datos_mct);
               delete_file(buzon00);
               /*Para colocar disponible una casilla simplemente se activa
                 con cero (0) el campo del tipo de oferta*/
               for(intentos = 2;!(backup_casillas = open_file(buzon02,0x02)) && intentos;intentos--)
               {
                  ;
               }
               if(backup_casillas != 0)
               {
                  for(indice = 0;indice < 20;indice++)
                  { /*Actualiza el archivo BZ02*/
                     if(son_iguales(casillas[indice].sdc,token))
                     {
                        casillas[indice].tipo = 0;
                     }
                     seek_file(backup_casillas,
                               sizeof(casillas[indice])*indice,0);
                     write_file(backup_casillas,sizeof(casillas[indice]),
                                &casillas[indice]);
                  }
                  close_file(backup_casillas);
               }
               casillas_disponibles++;
            }
            /*Inicializa el sistema de archivos*/
            inicializacion_de_archivos();
            block(PUERTO_DE.MCT,0);
         }
         else
         {
            if(son_iguales("FECHA\0",token))
            { /*BUZON>FECHA*/
               do
               {
                  while((linea[indice] == 0x20) || (linea[indice] == 0x2F))
                  {
                     indice++;
                  }
                  if(linea[indice] == 0x0D)
                  {
                     return 5; /*Mensaje de ayuda*/
                  }
                  if((linea[indice] < 0x30) || (linea[indice] > 0x39))
                  {
                     return 2; /*Parametro erroneo*/
                  }
                  if((linea[indice+1] < 0x30) || (linea[indice+1] > 0x39))
                  {
                     return 2; /*Parametro erroneo*/
                  }
                  token[i] = linea[indice];
                  token[i+1] = linea[indice+1];
                  i += 2;
                  indice += 2;
               }while(i < 6);
               actualizar_fecha(token);
            }
            else
            {
               if(son_iguales("HORA\0",token))
               { /*BUZON>HORA*/
                  do
                  {
                     while((linea[indice] == 0x20) || (linea[indice] == 0x3A))
                     {
                        indice++;
                     }
                     if(linea[indice] == 0x0D)
                     {
                        return 6; /*Mensaje de ayuda*/
                     }
                     if((linea[indice] < 0x30) || (linea[indice] > 0x39))
                     {
                        return 2; /*Parametro erroneo*/
                     }
                     if((linea[indice+1] < 0x30) || (linea[indice+1] > 0x39))
                     {
                        return 2; /*Parametro erroneo*/
                     }
                     token[i] = linea[indice];
                     token[i+1] = linea[indice+1];
                     i += 2;
                     indice += 2;
                  }while(i < 4);
                  actualizar_hora(token);
               }
               else
               {
                  if(son_iguales("HORARIO\0",token))
                  { /* BUZON>HORARIO */
                     do
                     {
                        while((linea[indice] == 0x20) ||
                              (linea[indice] == 0x3A))
                        {
                           indice++;
                        }
                        if(linea[indice] == 0x0D)
                        {
                           return 7; /* Mensaje de ayuda*/
                        }
                        if((linea[indice] < 0x30) || (linea[indice] > 0x39))
                        {
                           return 2; /* Parametro erroneo*/
                        }
                        if((linea[indice+1] < 0x30) ||
                           (linea[indice+1] > 0x39))
                        {
                           return 2; /* Parametro erroneo*/
                        }
                        horario.hora_inicio[i] = linea[indice];
                        horario.hora_inicio[i+1] = linea[indice+1];
                        i += 2;
                        indice += 2;
                     }while(i < 4);
                     i = 0;
                     do
                     {
                        while((linea[indice] == 0x20) ||
                              (linea[indice] == 0x3A))
                        {
                           indice++;
                        }
                        if(linea[indice] == 0x0D)
                        {
                           return 7; /* Mensaje de ayuda*/
                        }
                        if((linea[indice] < 0x30) || (linea[indice] > 0x39))
                        {
                           return 2; /* Parametro erroneo*/
                        }
                        if((linea[indice+1] < 0x30) ||
                           (linea[indice+1] > 0x39))
                        {
                           return 2; /* Parametro erroneo*/
                        }
                        horario.hora_finalizacion[i] = linea[indice];
                        horario.hora_finalizacion[i+1] = linea[indice+1];
                        i += 2;
                        indice += 2;
                     }while(i < 4);
                     if(!(bz03 = open_file(buzon03,0x02)))
                     {
                        bz03 = create_file(buzon03);
                     }
                     seek_file(bz03,0,0);
                     write_file(bz03,sizeof(horario),&horario);
                     close_file(bz03); /* Actualizado el horario de trabajo*/
                  }
                  else
                  {
                     if(son_iguales("DATOS\0",token))
                     { /*BUZON>DATOS*/
                        datos_mct = create_file(buzon00);
                        caracter_control = 6;
                        for(;;)
                        {
                           enviar(PUERTO_DE.MCT,caracter_control);
                           for(espera = 80000;!(caracter_control = recibir(PUERTO_DE.MCT)) && espera;espera--)
                           {
                              ;
                           }
                           if(!espera && !caracter_control)
                           {
                              close_file(datos_mct);
                              delete_file(buzon00);
                              return 0;
                           }
                           if(caracter_control == 0x16)
                           {
                              break;
                           }
                           write_file(datos_mct,1,&caracter_control);
                        }
                        enviar(PUERTO_DE.MCT,caracter_control);
                        for(i_sdc = nodo_sdc;i_sdc < &nodo_sdc[NUM_SDCS];i_sdc++)
                        {
                           for(indice = 0;indice < 9;indice++)
                           {
                              i_sdc->sdc[indice] = '\0';
                           }
                           for(indice = 0;indice < 7;indice++)
                           {
                              i_sdc->fecha_tope[indice] = '\0';
                           }
                           for(i = 0;i < INVITADOSxSDC;i++)
                           {
                              for(indice = 0;indice < 41;indice++)
                              {
                                 i_sdc->invitado[i].nombre_proveedor[indice] = '\0';
                              }
                              for(indice = 0;indice < 11;indice++)
                              {
                                 i_sdc->invitado[i].rif[indice] = '\0';
                              }
                              for(indice = 0;indice < 7;indice++)
                              {
                                 i_sdc->invitado[i].clave_secreta[indice] = '\0';
                              }
                              i_sdc->invitado[i].ofertas_entregadas = 0;
                           }
                        }
                        seek_file(datos_mct,0,0);
                        i_sdc = indice_secundario = nodo_sdc;
                        i_inv = i_sdc->invitado;
                        parpadeo = 0;
                        sdcs_leidos = 0;
                        for(indice = 0;indice < 9;indice++)
                        {
                           i_sdc->sdc[indice] = '\0';
                        }
                        while(read_file(datos_mct,sizeof(buffer_sim),&buffer_sim)
                              && (sdcs_leidos <= NUM_SDCS))
                        { /*Lee cada renglon del archivo, agregando un registro
                            SDC nuevo a la estructura nodo_sdc en caso de encontrarse*/
                           for(indice = 0;indice < 8;indice++)
                           {
                              nodo_sdc[NUM_SDCS].sdc[indice] = buffer_sim[indice];
                           }
                           nodo_sdc[NUM_SDCS].sdc[indice] = '\0';
                           if(no_son_iguales(nodo_sdc[NUM_SDCS].sdc,i_sdc->sdc))
                           {
                              for(indice = 0;indice < 11;indice++)
                              {
                                 i_inv->rif[indice] = '\0';
                              }
                              i_sdc = indice_secundario;
                              indice_secundario++;
                              sdcs_leidos++; /*Otro SDC recibido*/
                              i_inv = i_sdc->invitado;
                              s_copy(nodo_sdc[NUM_SDCS].sdc,i_sdc->sdc);
                              i = 0;
                              indice = 70;
                              i_sdc->fecha_tope[i++] = buffer_sim[indice];
                              i_sdc->fecha_tope[i++] = buffer_sim[indice+1];
                              indice -= 2;
                              i_sdc->fecha_tope[i++] = buffer_sim[indice];
                              i_sdc->fecha_tope[i++] = buffer_sim[indice+1];
                              indice -= 2;
                              i_sdc->fecha_tope[i++] = buffer_sim[indice];
                              i_sdc->fecha_tope[i++] = buffer_sim[indice+1];
                              i_sdc->fecha_tope[i] = '\0';
                              parpadeo++;
                           }
                           for(indice = 8,i = 0;indice < 18;indice++,i++)
                           {
                              i_inv->rif[i] = buffer_sim[indice];
                           }
                           i_inv->rif[i] = '\0';
                           for(indice = 18,i = 0;indice < 58;indice++,i++)
                           {
                              i_inv->nombre_proveedor[i] = buffer_sim[indice];
                           }
                           i_inv->nombre_proveedor[i] = '\0';
                           for(indice = 58,i = 0;indice < 64;indice++,i++)
                           {
                              i_inv->clave_secreta[i] = buffer_sim[indice];
                           }
                           i_inv->clave_secreta[i] = '\0';
                           i_inv->ofertas_entregadas = 0;
                           i_inv++;
                        }
                        delete_file(buzon00);
                        /*Abre el archivo principal de datos para actualizar
                          en los nuevos datos, el campo de ofertas entregadas
                          para cada proveedor en todas las SDCs*/
                        for(intentos = 2;!(datos_buzon = open_file(buzon01,0)) && intentos;intentos--)
                        {
                           ;
                        }
                        if(intentos)
                        { /*Si existe el archivo BZ01*/
                           while(read_file(datos_buzon,sizeof(nodo_sdc[20]),&nodo_sdc[20]))
                           { /*Lee cada registro del archivo BZ01*/
                              i_sdc = nodo_sdc; /*Inicializa el apuntador a la estructura*/
                              while(no_son_iguales(nodo_sdc[20].sdc,i_sdc->sdc) &&
                                    (i_sdc != numero_de_sdcs))
                              { /*Busca un registro SDC ya existente*/
                                 i_sdc++;
                              }
                              if(son_iguales(nodo_sdc[20].sdc,i_sdc->sdc))
                              { /*Si lo encontro*/
                                 struct lista_proveedores *auxiliar = nodo_sdc[20].invitado;
                                 for(i_inv = i_sdc->invitado,i = 0;no_son_iguales(i_inv->rif,nulo) &&
                                                                   (i <= 20);i_inv++,auxiliar++,i++)
                                 { /*Hubica cada sub-registro de invitado al SDC*/
                                    if(son_iguales(i_inv->rif,auxiliar->rif))
                                    { /*Refresca el campo de ofertas entregadas para el nuevo registro*/
                                       i_inv->ofertas_entregadas = auxiliar->ofertas_entregadas;
                                    }
                                 }
                              }
                           }
                           close_file(datos_buzon); /*Cierra el archivo de datos BZ01*/
                        }
                        datos_buzon = create_file(buzon01); /*Crea un nuevo archivo de datos*/
                        for(indice = 0;indice < parpadeo;indice++)
                        { /*Construye el archivo de datos del Buzon*/
                           write_file(datos_buzon,sizeof(nodo_sdc[indice]),&nodo_sdc[indice]);
                        }
                        close_file(datos_buzon);
                        inicializacion_de_archivos();
                        block(PUERTO_DE.MCT,0);
                     }
                     else
                     {
                        if(son_iguales("VERFECHA\0",token)) /*BUZON>VERFECHA*/
                        {
                           leer_fecha(fecha_transferida);
                           envia_al_MCT_campo(fecha_transferida);
                        }
                        else
                        {
                           if(son_iguales("VERHORA\0",token)) /*BUZON>VERHORA*/
                           {
                              leer_hora(hora_transferida);
                              envia_al_MCT_campo(hora_transferida);
                           }
                           else
                           {
                              if(son_iguales("FUERA_DE_SERVICIO\0",token))
                              { /*BUZON>FUERA_DE_SERVICIO*/
                                 fuera_de_servicio = 1; /*Pone fuera de servicio al Buzon*/
                              }
                              else
                              {
                                 if(son_iguales("EN_SERVICIO\0",token))
                                 { /*BUZON>EN_SERVICIO*/
                                    fuera_de_servicio = 0; /*Pone en servicio al Buzon*/
                                 }
                                 else
                                 {
                                    if(son_iguales("INICIALIZAR\0",token))
                                    { /*Elimina los archivos de datos*/
                                       delete_file(buzon01);
                                       delete_file(buzon02);
                                       inicializacion_de_archivos();
                                    }
                                    else
                                    {
                                       return 1;  /*"COMANDO ERRONEO"*/
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
   return 0;
}



/*[]----------------------------------------------------------[]*
 *  Procedimiento que construye todas las estructuras de datos  *
 *  en la memoria del micro computador del Buzon, ademas de     *
 *  activar ciertas variables utilizadas para trabajar.         *
 *                                                              *
 *  Entradas: ninguna                                           *
 *  Salidas:  ninguna                                           *
 *[]----------------------------------------------------------[]*/
void inicializacion_de_archivos()
{
   registro_sdc  *indice_principal;
   sdc_tipos_casilla  *indice_casilla;
   int  i,
        datos_mct,
        trans,
        bz03,
        bz05,
        bz_disponibles,
        intentos;
   char
         *inicio_defecto =       "0600",
         *finalizacion_defecto = "2300";


   for(intentos = 2;!(datos_mct = open_file(buzon01,0)) && intentos;intentos--)
   {
      ;
   }
   if(datos_mct)
   {
      for(indice_principal = nodo_sdc;
          read_file(datos_mct,sizeof(*indice_principal),indice_principal);
          indice_principal++)
      {
         ;
      }
      numero_de_sdcs = indice_principal;
      close_file(datos_mct);
      for(intentos = 2;!(backup_casillas = open_file(buzon02,0)) && intentos;intentos--)
      {
         ;
      }
      if(backup_casillas)
      {
         casillas_disponibles = 0; /*Inicializa el numero de casillas disponibles*/
         for(indice_casilla = casillas;read_file(backup_casillas,
                                                 sizeof(*indice_casilla),
                                                 indice_casilla);
                                                 indice_casilla++)
         {
            if(indice_casilla->tipo == 0) /*Esta disponible esta casilla?*/
            {
               casillas_disponibles++; /*Aumenta el contador de casillas*/
            }
         }
         close_file(backup_casillas);
         for(primero_disponible = 0;casillas[primero_disponible].tipo;
             primero_disponible++)
         {
            ;
         }
         casilla_permanente = punto_medio(NUM_SDCS - casillas_disponibles);
         if(!casilla_permanente)
         { /*Si todas estan disponibles*/
            casilla_permanente = 1; /*Primera casilla*/
         }
         if(casillas_disponibles <= MINIMO_DISPONIBLE)
         { /*No se atiende la peticion de extraccion de sobres*/
            urgencia_atendida = 0;
         }
         else
         {
            urgencia_atendida = 1;
         }
      }
      else
      {
         primero_disponible = 0;
         casilla_permanente = 1;
         casillas_disponibles = 20; /*Todas las casillas estan disponibles*/
         urgencia_atendida = 1;
      }
   }
   else
   {
      numero_de_sdcs = 0;
      casilla_permanente = 1;
      casillas_disponibles = 20; /*Todas las casillas estan disponibles*/
      urgencia_atendida = 1;
   }
   for(intentos = 2;!(bz05 = open_file(buzon05,0)) && intentos;intentos--)
   { /*Intenta abrir el archivo de puertos*/
      ;
   }
   if(!bz05)
   {
      bz05 = create_file(buzon05); /*Nuevo archivo*/
      PUERTO_DE.MCT = 0x03F8; /*Coloca el numero de puerto para MCT*/
      PUERTO_DE.MOTORES = 0x03BC; /*Coloca el numero de puerto para motores*/
      PUERTO_DE.MECANISMO = 0x0278; /*Coloca el numero de puerto para mecanismo*/
      PUERTO_DE.TSENSORES = 0x0378; /*Direccion base para sensores del tobogan*/
      write_file(bz05,sizeof(PUERTO_DE),&PUERTO_DE); /*Guarda la configuracion*/
   }
   seek_file(bz05,0,0); /*Toma la direccion base de puertos*/
   read_file(bz05,sizeof(PUERTO_DE),&PUERTO_DE);
   close_file(bz05);
   for(intentos = 2;!(bz03 = open_file(buzon03,0)) && intentos;intentos--)
   { /*Intenta abrir el archivo de horario del Buzon*/
      ;
   }
   if(!bz03)
   {
      bz03 = create_file(buzon03); /*Nuevo archivo*/
      /*Coloca el horario por defecto para el Buzon*/
      s_copy(inicio_defecto,horario.hora_inicio);
      s_copy(finalizacion_defecto,horario.hora_finalizacion);
      write_file(bz03,sizeof(horario),&horario); /*Guarda el horario*/
   }
   /*Lee el Horario establecido para el Buzon*/
   seek_file(bz03,0,0);
   read_file(bz03,sizeof(horario),&horario);
   close_file(bz03);
   /*Comprueba si hay transacciones por enviar al MCT*/
   archivo_existente = ((trans = open_file(buzon04,0)) != 0) ? 1 : 0;
   close_file(trans);
   //busca_la_casilla(PUERTO_DE.MOTORES,casilla_permanente);
}



/*[]------------------------------------------------[]*
 *  Procedimiento que verifica el horario de trabajo  *
 *  del Buzon contra la hora actual                   *
 *                                                    *
 *  Entrada: ninguna                                  *
 *  Salida:  status 1 -> en horario                   *
 *                  0 -> fuera de horario             *
 *[]------------------------------------------------[]*/
int esta_en_horario()
{
   int  hora_i,
        hora_f,
        hora_leida;
   char  hora[5];


   leer_hora(hora); /*Lee la hora actual*/
   /*Arma los digitos de la hora de inicio*/
   hora_i = ( (horario.hora_inicio[0]&0x0F) << 3 ) +
            ( (horario.hora_inicio[0]&0x0F) << 1 ) +
            (horario.hora_inicio[1]&0x0F);
   /*Arma los digitos de la hora de finalizacion*/
   hora_f = ( (horario.hora_finalizacion[0]&0x0F) << 3 ) +
            ( (horario.hora_finalizacion[0]&0x0F) << 1 ) +
            (horario.hora_finalizacion[1]&0x0F);
   /*Arma los digitos de la hora actual*/
   hora_leida = ( (hora[0]&0x0F) << 3 ) +
                ( (hora[0]&0x0F) << 1 ) +
                (hora[1]&0x0F);
   if((hora_leida > hora_i) && (hora_leida < hora_f))
   {
      return 1; /*Esta en horario*/
   }
   if((hora_leida == hora_i) && (hora_leida != hora_f))
   {
     /*Arma los digitos de los minutos de inicio*/
      hora_i = ( (horario.hora_inicio[2]&0x0F) << 3 ) +
               ( (horario.hora_inicio[2]&0x0F) << 1 ) +
               (horario.hora_inicio[3]&0x0F);
     /*Arma los digitos de los minutos actuales*/
      hora_leida = ( (hora[2]&0x0F) << 3 ) +
                   ( (hora[2]&0x0F) << 1 ) +
                   (hora[3] & 0x0F);
      if(hora_leida >= hora_i)
      {
         return 1; /*Esta en horario*/
      }
      else
      {
         return 0; /*Esta fuera de horario*/
      }
   }
   if((hora_leida == hora_f) && (hora_leida != hora_i))
   {
     /*Arma los digitos de los minutos de finalizacion*/
      hora_f = ( (horario.hora_finalizacion[2]&0x0F) << 3 ) +
               ( (horario.hora_finalizacion[2]&0x0F) << 1 ) +
               (horario.hora_finalizacion[3]&0x0F);
     /*Arma los digitos de los minutos de finalizacion*/
      hora_leida = ( (hora[2]&0x0F) << 3 ) +
                   ( (hora[2]&0x0F) << 1 ) +
                   (hora[3]&0x0F);
      if(hora_leida <= hora_f)
      {
         return 1; /*Esta en horario*/
      }
      else
      {
         return 0; /*Esta fuera de horario*/
      }
   }
   if((hora_leida == hora_f) && (hora_leida == hora_i))
   {
     /*Arma los digitos de los minutos de finalizacion*/
      hora_f = ( (horario.hora_finalizacion[2]&0x0F) << 3 ) +
               ( (horario.hora_finalizacion[2]&0x0F) << 1 ) +
               (horario.hora_finalizacion[3]&0x0F);
     /*Arma los digitos de los minutos de inicio*/
      hora_i = ( (horario.hora_inicio[2]&0x0F) << 3 ) +
               ( (horario.hora_inicio[2]&0x0F) << 1 ) +
               (horario.hora_inicio[3]&0x0F);
     /*Arma los digitos de los minutos de finalizacion*/
      hora_leida = ( (hora[2]&0x0F) << 3 ) +
                   ( (hora[2]&0x0F) << 1 ) +
                   (hora[3]&0x0F);
      if((hora_leida >= hora_i) && (hora_leida <= hora_f))
      {
         return 1; /*Esta en horario*/
      }
   }
   return 0; /*Esta fuera de horario*/
}



void envia_comentarios_MCT(register char *cadena)
{
   for(;*cadena;enviar(PUERTO_DE.MCT,*cadena++),delay(FRENO_BUZON))
   {
      ;
   }
}



int envia_al_MCT_campo(register char *cadena)
{
   long int  espera;
   unsigned char  caracter;


   while(*cadena)
   {
      enviar(PUERTO_DE.MCT,*cadena); /*Envia el siguiente caracter al MCT*/
      for(espera = 80000;!(caracter = recibir(PUERTO_DE.MCT)) && espera;espera--)
      { /*Espera a recibir el caracter enviado*/
         ;
      }
      if(!espera && !caracter)
      { /*No hay respuesta por parte del MCT*/
         return 0; /*Transferencia no completada*/
      }
      cadena++;
   }
   return 1; /*Transferencia completada*/
}



/*[]---------------------------------------------[]*
 *  Significado de los indicadores:                *
 *                                                 *
 *  # Rojo   => el Buzon esta buscando la casilla  *
 *              en la cual seran extraidos sobres  *
 *                                                 *
 *  # Verde  => el Buzon hubico la casilla donde   *
 *              se hara la extraccion, y se deben  *
 *              extraer los sobres                 *
 *                                                 *
 *  # Blanco => encendida por el Buzon durante     *
 *              todo el proceso de extraccion      *
 *[]---------------------------------------------[]*/
void datos_a_puerta(unsigned int puerto,unsigned char LR,unsigned char LV,
                    unsigned char LB,unsigned char C,unsigned char E)
{ /*Envia una combinacion de bits para encender las luces
    de extraccion ademas de controlar el cerrojo electronico
    para la puerta de extraccion de sobres*/
   asm  MOV  AL,LR /*Indicador Rojo*/
   asm  SHL  AL,1
   asm  OR   AL,LV /*Indicador Verde*/
   asm  SHL  AL,1
   asm  OR   AL,LB /*Indicador Blanco*/
   asm  SHL  AL,1
   asm  OR   AL,C  /*Control del Cerrojo*/
   asm  SHL  AL,1
   asm  OR   AL,E  /*Energia para el Cerrojo*/
   asm  MOV  DX,puerto
   asm  OUT  DX,AL
}



/*[]------------------------------[]*
 *  Los dos primeros bits indican:  *
 *                                  *
 *  bit 1 = 1 => puerta abierta     *
 *        = 0 => puerta cerrada     *
 *                                  *
 *  bit 2 = 1 => boton oprimido     *
 *        = 0 => boton no oprimido  *
 *[]------------------------------[]*/
int datos_de_puerta(unsigned int puerto)
{ /*Recoge el status del boton de arranque (para extracciones)
    y del sensor de la puerta (que indica si la puerta esta abierta)*/
   asm  MOV  DX,puerto
   asm  INC  DX
   asm  IN   AL,DX /*recibe del puerto*/
   asm  SHR  AL,1 /*Adapta a numero entero la lectura*/
   asm  SHR  AL,1
   asm  SHR  AL,1
   asm  AND  AL,0x03 /*Enmascara los dos primeros bits*/
   asm  SUB  AH,AH
   return _AX;
}



/*[]------------------------------------------[]*
 *  Procedimiento que abre la puerta de sobres  *
 *  y verifica si el sobre cae en el Buzon      *
 *                                              *
 *  Entrada: ninguna                            *
 *  Salida:  status del paso de sobre           *
 *           1 --> el sobre paso                *
 *           0 --> el sobre no paso             *
 *[]------------------------------------------[]*/
int entrada_de_sobre(int com_carrusel)
{
   #define  kcons  8000
   int  revoluciones;


   lectores = 0; /*Limpia la variable indicadora*/
   for(revoluciones = 0;revoluciones < 35;revoluciones++)
   { /*Abre la puerta de entrada de sobres*/
      mover_la_puerta(com_carrusel,1,kcons);
   }
   if(!lectores)
   { /*Se ha detectado el paso del sobre?*/
      dead_time(800); /*Espera un tiempo*/
   }
   for(revoluciones = 0;revoluciones < 35;revoluciones++)
   { /*Cierra la puerta de entrada de sobres*/
      mover_la_puerta(com_carrusel,0,kcons);
   }
   datos_al_mecanismo(com_carrusel,0); /*Desenergiza la entrada del motor*/
   return !lectores ? 0 : 1; /*Regresa status 0 si no se detecto el sobre*/
}



int busca_el_codigo(int puerto,int sentido)
{
   int  codigo;


   if(!(codigo = datos_del_mecanismo(puerto)))
   { /*hay codigo leido?*/
      datos_al_mecanismo(puerto,sentido); /*Mueve el carrusel*/
      /*espera a leer codigo*/
      while(!(codigo = datos_del_mecanismo(puerto))) { ; }
      delay(300); /*Entra mas en el codigo*/
      codigo = datos_del_mecanismo(puerto); /*Lee el definitivo*/
   }
   return codigo;
}



void busca_la_casilla(int puerto,int casilla_destino)
{
   unsigned char  codigo;
   int  sentido = 5;


   codigo = busca_el_codigo(puerto,sentido);
   while(codigo != casilla_destino)
   { /*Mientras el codigo leido sea diferente a la casilla destino*/
      if(codigo > casilla_destino)
      { /*Busca en el sentido contrario a las agujas del reloj*/
         if(codigo)
         {
            if(sentido == 3)
            {
               datos_al_mecanismo(puerto,0); delay(400); /*Detiene el carrusel*/
            }
            datos_al_mecanismo(puerto,sentido); delay(500); /*Detiene el carrusel*/
         }
         sentido = 5; codigo = busca_el_codigo(puerto,sentido);
      }
      else
      { /*Busca en el sentido de las agujas del reloj*/
         if(codigo)
         {
            if(sentido == 5)
            {
               datos_al_mecanismo(puerto,0); delay(400); /*Detiene el carrusel*/
            }
            sentido = 3; datos_al_mecanismo(puerto,sentido); /*Detiene el carrusel*/
            delay(500);
         }
         codigo = busca_el_codigo(puerto,sentido);
      }
   }
   if(sentido == 5)
   {
      datos_al_mecanismo(puerto,0); delay(400); /*Detiene el carrusel*/
      sentido = 3; datos_al_mecanismo(puerto,sentido); /*Alinea la casilla con el tobogan*/
      delay(3000);
   }
   else
   {
      datos_al_mecanismo(puerto,sentido); delay(2000); /*Alinea la casilla con el tobogan*/
   }
   datos_al_mecanismo(puerto,0); /*Detiene el carrusel*/
}



/*[]---------------------------[]*
 *  Sentido = 1 -->   creciente  *
 *          = 0 --> decreciente  *
 *[]---------------------------[]*/
void mover_la_puerta(int com_carrusel,int sentido,int k)
{
   register int  cronometro,
                 numero;
   unsigned char
                  secuencia[8] = {0xa0,0xb0,0x90,0xd0,0x50,0x70,0x60,0xe0};


   if(!sentido)
   {
      secuencia[0] = 0xe0;
      secuencia[1] = 0x60;
      secuencia[2] = 0x70;
      secuencia[3] = 0x50;
      secuencia[4] = 0xd0;
      secuencia[5] = 0x90;
      secuencia[6] = 0xb0;
      secuencia[7] = 0xa0;
   }
   for(numero = 0;numero <= 7;datos_al_mecanismo(com_carrusel,secuencia[numero++]))
   { /*Una revolucion completa de la polea*/
      for(cronometro = 0;cronometro <= k;cronometro++)
      {
         ;
      }
   }
}



/*[]------------------------[]*
 *  Para el carrusel:         *
 *  Parar    = 0              *
 *  Mover    = 3 izquierda    *
 *           = 5 derecha      *
 *[]------------------------[]*/
void datos_al_mecanismo(unsigned int puerto,unsigned char caracter)
{
   asm  MOV  DX,puerto /*Carga en DX direccion del puerto*/
   asm  MOV  AL,caracter /*Carga el byte a transmitir en AL*/
   asm  OUT  DX,AL /*Envia el byte al puerto*/
}



unsigned char datos_del_mecanismo(unsigned int puerto)
{
   asm  MOV  DX,puerto /*Carga en DX direccion del puerto*/
   asm  INC  DX
   asm  IN   AL,DX /*Lee el contenido del puerto*/
   asm  MOV  CL,3 /*Ajusta el codigo leido*/
   asm  SHR  AL,CL
   asm  XOR  AL,0x10 /*bit D7 negado*/
   return _AL;
}



void instala_vector_para_filtro()
{
   asm  MOV  AX,0x351C /*Toma la direccion segmentada para INT 1Ch*/
   asm  INT  0x21
   asm  MOV  numseg,ES /*Almacena el numero de segmento en "numseg"*/
   asm  MOV  index,BX /*Almacena el numero de offset en "index"*/
   asm  PUSH DS
   asm  MOV  AX,0x251C /*Instala la direccion nueva (segmentada)*/
   asm  MOV  DX,OFFSET CS:filtro /*Coloca el offset del procedimiento "filtro"*/
   asm  PUSH CS
   asm  POP  DS
   asm  INT  0x21
   asm  POP  DS
   lectores = 0; /*Inicializa el mapa de bits para los lectores del tobogan*/
}



void repone_vector_de_filtro()
{
   asm  PUSH DS
   asm  MOV  DX,index /*Numero de offset anterior a la instalacion*/
   asm  MOV  AX,numseg /*Numero de segmento anterior a la instalacion*/
   asm  MOV  DS,AX
   asm  MOV  AX,0x251C /*Numero de interrupcion cuyo vector hay que reponer*/
   asm  INT  0x21
   asm  POP  DS
}



void interrupt far filtro()
{
   asm  MOV  BX,OFFSET PUERTO_DE.TSENSORES
   asm  MOV  DX,WORD PTR [BX] /*Toma la direccion base de puerto*/
   asm  INC  DX
   asm  IN   AL,DX /*Lee los sensores del tobogan*/
   asm  AND  AL,0XF0
   asm  CMP  AL,0x70
   asm  JNE  flt02
   lectores = 1; /*Paso por el segundo sensor (el unico que funciona)*/
flt02:
   ;
}