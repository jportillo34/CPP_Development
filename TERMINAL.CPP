#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

class teletipo
   {
      public:
         unsigned char caracter;
         void activa_el_caracter_con(unsigned char valor)
            { caracter = valor; }
         unsigned char entrega_el_valor_del_caracter()
            { return caracter; }
         void comprueba_tu_teclado()
            { caracter = (kbhit() != 0) ? getch() : 0; }
         void muestra_en_tu_pantalla()
            { if(caracter) putchar(caracter); }
   };

class terminal : public teletipo
   {
      public:
         unsigned int direccion_del_puerto;
         void utiliza_el_puerto_numero(unsigned int puerto)
            { direccion_del_puerto = puerto; }
         unsigned int entrega_la_direccion_de_puerto()
            { return direccion_del_puerto; }
         void envia_al_puerto();
         void recibe_del_puerto();
   };

void terminal::envia_al_puerto()
   {
      _DX = direccion_del_puerto;
      _AL = caracter;
      asm     CMP       AL,0
      asm     JE        nout
      asm     OUT       DX,AL
nout:
   }

void terminal::recibe_del_puerto()
   {
      _DX = direccion_del_puerto;
      asm     ADD       DX,5
      asm     IN        AL,DX
      asm     AND       AL,0x01
      asm     JZ        noc
      asm     SUB       DX,5
      asm     IN        AL,DX
      asm     JMP       sl01

noc:
      asm     SUB       AL,AL

sl01:
      caracter = _AL;
   }

void main()
   {
      #define puerto  0x03F8
      #define Esc     0x1B
      int  rows; teletipo  *tele; terminal  *terminal_local;

      printf("terminales activos hoy:"); scanf("%d",rows);
      if(!(terminal_local = new terminal[rows]))
         {  printf("No es posible hubicar los %d terminales\n",rows);
            exit(0);
         }
      for(terminal_local[rows-1].utiliza_el_puerto_numero(puerto);;)
         {  terminal_local[rows-1].recibe_del_puerto();
            terminal_local[rows-1].muestra_en_tu_pantalla();
            terminal_local[rows-1].comprueba_tu_teclado();
            if(terminal_local[rows-1].entrega_el_valor_del_caracter() == Esc)
               { break; }
            terminal_local[rows-1].envia_al_puerto();
         }
      delete[] terminal_local;
      for(tele = new teletipo;;)
         {  tele->comprueba_tu_teclado();
            if(tele->entrega_el_valor_del_caracter() == Esc)
               { break; }
            tele->muestra_en_tu_pantalla();
         }
      delete tele;
   }