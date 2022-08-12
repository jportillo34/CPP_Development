#include<stdio.h>
#include<stdlib.h>
#include<metrolog.h>
#include<estandar.h>



void extrae_un_codigo(FILE *texto,unsigned char cadena[])
{
   unsigned char caracter;
   int indice_codigos;


   /*Limpia la cadena antes de usarla*/
   for(indice_codigos = 0;indice_codigos < TOPE;indice_codigos++)
   {
      cadena[indice_codigos] = 0;
   }
   for(indice_codigos = 0;;)
   {
      caracter = getc(texto);
      if(caracter == 0x0A) /*Filtra el final de una fila*/
      {
         caracter = getc(texto);
      }
      if(caracter == 'F')
      { /*Es el final de los codigos => "FINAL DE LECTURAS"*/
         cadena[0] = 0; /*Indicativo de final de codigos*/
         break; /*Termina el procedimiento*/
      }
      if((caracter != ',') && (caracter != '_'))
      { /*Escribe en la cadena todo el codigo sin relleno*/
         cadena[indice_codigos++] = caracter;
      }
      else
      {
         /*Encuentra el inicio del siguiente codigo*/
         while(getc(texto) != ' ');
         break; /*Termina el procedimiento*/
      }
   }
}



void main()
{
   struct conteo ocurrencia[MAX];
   unsigned char caracter,
                 tecla,
                 status_tecla,
                 C_oprimida,
                 *cadena_origen,
                 *cadena_destino,
                 patron[TOPE],
                 errado[TOPE];
   int   gap,
         var,
         indice_util,
         indice_columna;
   unsigned long int lecturas_realizadas,
                     lecturas_erroneas,
                     caracteres_escritos;
   FILE *metro;


   printf("[]-------Programa para lectura de Codigo de Barras-------[]\n");
   printf("Desarrollado por el Departamento de Investigacion de XXXXXXX c.a.\n");
   printf("Acciones:  tecla 'c'   --> iniciar comparaciones\n");
   printf("           tecla 'Esc' --> finalizar\n\n");
   for(indice_util = 0;indice_util < TOPE;indice_util++)
   {
      patron[indice_util] = 0;
      errado[indice_util] = 0;
   }
   metro = fopen("METROLOG.TXT","w");
   for(lecturas_realizadas = lecturas_erroneas = caracteres_escritos = 0,indice_util = 0,indice_columna = 1,gap = 14,C_oprimida = 0;;)
   {
      if((caracter = recibir(COM2)) != 0) /*Hay caracter recibido?*/
      {
         putchar(caracter); /*Imprime en la pantalla el digito*/
         if(!C_oprimida) /*No se ha oprimido la tecla F1?*/
         {
            if((caracter != LF) && (caracter != CR)) /*Es un digito?*/
            {
               patron[indice_util++] = caracter;
            }
            else
            {
               if(caracter == LF)
               {
                  lecturas_realizadas++; /*Numero de lecturas realizadas*/
                  /*Espera una accion o tecla Esc*/
                  while(((status_tecla = keypressed()) != COMP) && (status_tecla != Esc) && ((caracter = recibir(COM2)) == 0));
                  if(status_tecla == Esc)
                  {
                     break;
                  }
                  if((caracter != 0) && (status_tecla != COMP))
                  {
                     putchar(caracter); /*Imprime en la pantalla el digito*/
                     for(indice_util = 0;indice_util < TOPE;indice_util++)
                     {
                        patron[indice_util] = 0;
                     }
                     indice_util = 0;
                     patron[indice_util++] = caracter;
                  }
                  else
                  {
                     fputs("\r\n\t\t\t*************************\n",metro);
                     fputs(    "\t\t\t* REPORTE  DE  LECTURAS *\n",metro);
                     fputs(    "\t\t\t*************************\n\n",metro);
                     fputs("\n\nCodigo Patron de Comparaciones -> ",metro);
                     caracteres_escritos++;
                     for(indice_util = 0;patron[indice_util] != 0;indice_util++)
                     {
                        putc(patron[indice_util],metro);
                     }
                     fputs("\n----------------------------------------------------------------------------",metro);
                     putc('\n',metro);
                     putc('\n',metro);
                     C_oprimida = 1; /*Se oprimio la tecla F1*/
                     indice_util = 0; /*Prepara para indizar a errado[]*/
                  }
               }
            }
         }
         else
         {
            if((caracter != LF) && (caracter != CR)) /*Es un digito?*/
            {
               errado[indice_util++] = caracter;
            }
            else
            {
               if(caracter == LF)
               {
                  lecturas_realizadas++; /*Numero de lecturas realizadas*/
                  if(!s_comp(patron,errado)) /*Compara ambas lecturas*/
                  {
                     for(indice_util = 0;errado[indice_util] != 0;indice_util++)
                     {
                        putc(errado[indice_util],metro);
                        errado[indice_util] = 0;
                        indice_columna++;
                     }
                     while(indice_columna < gap) /*rellena con # hasta 13 caracteres*/
                     {
                        putc('_',metro);
                        indice_columna++;
                     }
                     /*Separadores de codigos leidos*/
                     putc(',',metro);
                     putc(' ',metro);
                     indice_columna += 2; /*Salta los separadores*/
                     gap += 15;           /*Siguiente separador*/
                     if(indice_columna == 76) /*Columna final?*/
                     {
                        putc('\n',metro); /*Siguiente fila*/
                        indice_columna = 1; /*retorno de indice*/
                        gap = 14; /*Primer separador*/
                     }
                     caracteres_escritos++;
                     lecturas_erroneas++; /*Cuenta de lecturas erradas*/
                  }
                  indice_util = 0;
               }
            }
         }
      }
      if((tecla = keypressed()) != 0) /*Hay tecla oprimida?*/
      {
         if(tecla == Esc) /*Tecla oprimida Esc?*/
         {
            break; /*Finalizar lecturas*/
         }
         if(tecla == COMP)
         {
            status_tecla = tecla; /*Guardar el valor de la tecla*/
         }
      }
   } /*Finalizadas las lecturas*/
   /*Comienza la creacion del reporte*/
   if(C_oprimida)
   {
      printf("\n\n****  Patron de Comparacion => ");
      /*Coloca la marca de fin de lecturas en el archivo*/
      for(indice_util = 0;patron[indice_util] != 0;indice_util++)
      {
         putchar(patron[indice_util]);
      }
      fputs("FIN DE LECTURAS.\n",metro);
      fputs("\n----------------------------------------------------------------------------\n",metro);
   }
   printf("\n****  Codigos Leidos  => %d",lecturas_realizadas);
   fputs("\n****  Codigos Leidos  => ",metro);
   ltoa(lecturas_realizadas,patron,10);
   for(indice_util = 0;patron[indice_util] != 0;indice_util++)
   {
      putc(patron[indice_util],metro);
   }
   if(C_oprimida)
   {
      printf("\n****  Codigos Errados => %d",lecturas_erroneas);
      fputs("\n****  Codigos Errados => ",metro);
      ltoa(lecturas_erroneas,errado,10);
      for(indice_util = 0;errado[indice_util] != 0;indice_util++)
      {
         putc(errado[indice_util],metro);
      }
      fputs(" repartidos de la siguiente forma:\n",metro);
   }
   if(caracteres_escritos) /*Finalizado el programa*/
   {
      fclose(metro);
      metro = fopen("METROLOG.TXT","r");
      /*Busca en el texto del archivo, el primer codigo leido*/
      indice_util = 0;
      /*Primer codigo hubicado en la linea 11*/
      while(indice_util < 10)
      {
         if(getc(metro) == 0x0A)
         {
            indice_util++;
         }
      }
      /*Coloca en cero todos los nodos de la tabla*/
      for(indice_util = 0;indice_util < MAX;indice_util++)
      {
         ocurrencia[indice_util].numero = 0;
         for(gap = 0;gap < TOPE;gap++)
         {
            ocurrencia[indice_util].codigo[gap] = 0;
         }
      }
      /*Inicia el conteo de ocurrencias*/
      for(indice_columna = 0;;)
      {
         /*Captura el siguiente codigo del archivo*/
         extrae_un_codigo(metro,patron);
         if(!patron[0]) /*Es el final de codigos?*/
         {
            break; /*Finaliza el conteo de ocurrencias*/
         }
         for(indice_util = 0;(indice_util < indice_columna) &&
                             (!s_comp(patron,ocurrencia[indice_util].codigo));
                             indice_util++);
         if(indice_util == indice_columna) /*El codigo no esta registrado*/
         {
            /*Registra el codigo*/
            cadena_origen = patron;
            cadena_destino = ocurrencia[indice_util].codigo;
            while((*cadena_destino++ = *cadena_origen++) != 0);
            cadena_destino = cadena_origen; /*Copia el caracter nulo*/
            ocurrencia[indice_util].numero++; /*Nueva ocurrencia*/
            indice_columna++; /*Siguiente nodo disponible*/
         }
         else
         {
            ocurrencia[indice_util].numero++; /*Nueva ocurrencia del codigo*/
         }
      } /*Contadas las ocurrencias (tabla ocurrencias)*/
      fclose(metro);
      /*Reporta en el archivo, el porcentaje de ocurrencias de cada codigo*/
      metro = fopen("METROLOG.TXT","a+");
      /*Ordena los codigos  en orden Decreciente por ocurrencias*/
      qsort((void *)ocurrencia,indice_columna,sizeof(ocurrencia[0]),comparacion);
      for(indice_util = 0;indice_util < indice_columna;indice_util++)
      {
         putc('\n',metro);
         fputs("      Codigo ",metro);
         for(gap = 0;ocurrencia[indice_util].codigo[gap] != 0;gap++)
         {
            putc(ocurrencia[indice_util].codigo[gap],metro);
         }
         fputs(", ",metro);
         for(var = 0;var < 15-gap;var++)
         {
            putc(' ',metro);
         }
         ocurrencia[indice_util].numero = (ocurrencia[indice_util].numero * 100) / lecturas_erroneas;
         itoa(ocurrencia[indice_util].numero,errado,10);
         for(gap = 0;errado[gap] != 0;gap++)
         {
            putc(errado[gap],metro);
         }
         putc(0x25,metro); /*Caracter '%'*/
      }
      fclose(metro);
   }
   else
   { /*No hay reporte en esta ocurrencia del programa*/
      remove("METROLOG.TXT");
   }
}
   asm   db    'Autor del Programa: Jose R. Portillo L. 1993'
