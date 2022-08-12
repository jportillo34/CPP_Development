#include  <conio.h>
#include  <stdio.h>


#define  entrada   0x379
#define  serialb    0x10  /* bit dato serial ___d____ */
#define  sincron    0x08  /* bit sincronismo ____s___ */


unsigned char recibe_codigo()
{
   asm   PUSH      CX
   asm   PUSH      DX

   asm   MOV       CX,8            /* Recibe los ocho bits del codigo */
   asm   SUB       AH,AH
   asm   MOV       DX,entrada

ciclo:
   asm   IN        AL,DX           /* Lee el puerto */
   asm   TEST      AL,sincron      /* Comprueba el bit de sincronismo */
   asm   JNZ       ciclo

   asm   SHR       AL,4            /* Toma el bit dato serial */
   asm   XOR       AL,1
   asm   AND       AL,1            /* Enmascara el bit 1 */
   asm   OR        AH,AL
   asm   DEC       CX              /* Acumula los ocho bits */
   asm   JZ        fin             /* Recibidos los ocho bits */
   asm   SHL       AH,1

espera:
   asm   IN        AL,DX           /* Espera el nivel bajo del bit de sinc. */
   asm   TEST      AL,sincron
   asm   JNZ       ciclo
   asm   JMP       espera          /* Data valida en la linea */

fin:
   asm   IN        AL,DX           /* Espera el nivel bajo del bit de sinc. */
   asm   TEST      AL,sincron
   asm   JZ        fin

   asm   MOV       AL,AH
   asm   POP       DX
   asm   POP       CX
   return _AL;                     /* Regresa el codigo leido */
}


void  main() { while(!kbhit())  printf("CODIGO>  %2x\n",recibe_codigo()); }