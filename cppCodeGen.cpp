/* ------------------------------------------------------------------------------------------------------------------- */
/* Ejemplo del codigo de maquina generado por el compilador C++ de manejo de arreglos a traves de apuntadores basicos. */
/*                                                                                                                     */
/* NOTA: El codigo generado es para un procesador Intel Core(TM) i5-3210M CPU 2.50GHz                                  */
/*       y la invocacion al compilador fue la siguiente:                                                               */
/*                                                       c++ -S -std=c++14 apuntadores.cpp                             */ 
/* ------------------------------------------------------------------------------------------------------------------- */

//
// funcion ejemplo: se maneja un arreglo 4-dimensional a traves de apuntadores basicos del C++.
//
void cargar_arreglo_2(char array[dimension1][dimension2][dimension3][dimension4])
{
	char *base = &array[0][0][0][0];

	for(int j = 0;j < dimension1;j++)
		for(int z = 0;z < dimension2;z++)
			for(int y = 0;y < dimension3;y++)
				for(int x = 0;x < dimension4;x++)
					*((char *) base + (j*dimension2*dimension3*dimension4) + (z*dimension3*dimension4) + (y*dimension4) + x) = 3;
}

//
// Codigo assembler generado por el compilador usando la opcion "c++ -S ..." (solo se incluye la funcion, no el main):
//
_Z16CARGAR_ARREGLO_2PA2_A2_A4_C:
.LFB0:
	PUSHQ	%RBP
	MOVQ	%RSP, %RBP
	SUBQ	$32, %RSP
	MOVQ	%RCX, 16(%RBP)   <-- desde el main viene la direccion del arreglo dentro del registro CX del Intel x62.
	MOVQ	16(%RBP), %RAX
	MOVQ	%RAX, -24(%RBP)  <-- ahora la posicion -24 del buffer BP contiene la direccion del arreglo.
	MOVL	$0, -4(%RBP)     <-- int j = 0  (del for mas externo).
	JMP		.L2

.L9:
	MOVL	$0, -8(%RBP)     <-- int z = 0 
	JMP		.L3

.L8:
	MOVL	$0, -12(%RBP)    <-- int y = 0
	JMP		.L4

.L7:
	MOVL	$0, -16(%RBP)    <-- int x = 0
	JMP		.L5

.L6:

#define dimension1   2
#define dimension2   2
#define dimension3   2
#define dimension4   4
-24(%BP) -----> base   (apuntador al array que viene como parametro).
-4(%BP)  -----> j
-8(%BP)  -----> z
-12(%BP) -----> y
-16(%BP) -----> x

// El siguiente es el codigo que ejecuta la sentencia que asigna el valor 3 a cada elemento del arreglo 4-dimensional: 
// *(base + (j*dimension2*dimension3*dimension4) + (z*dimension3*dimension4) + (y*dimension4) + x) = 3;
//
// NOTA: Observar que el generador de codigo no utiliza la operacion MULT del Intel x64 (Intel Core(TM) i5-3210M CPU 2.50GHz)
//       En su lugar usa la operacion SALL (Shift Arithmetic Left) que respeta el bit del signo (complemento-2).

	MOVL	-4(%RBP), %EAX    <-- j
	SALL	$4, %EAX          <-- (j*dimension2*dimension3*dimension4)
	MOVSLQ	%EAX, %RDX
	MOVL	-8(%RBP), %EAX    <-- z
	SALL	$3, %EAX          <-- (z*dimension3*dimension4)
	CLTQ                      <-- convierte el contenido del registro AX de double-word a quad-word
	ADDQ	%RAX, %RDX        <-- (j*dimension2*dimension3*dimension4) + (z*dimension3*dimension4)
	MOVL	-12(%RBP), %EAX   <-- y
	SALL	$2, %EAX          <-- (y*dimension4)
	CLTQ                      <-- convierte el contenido del registro AX de double-word a quad-word
	ADDQ	%RAX, %RDX        <-- (j*dimension2*dimension3*dimension4) + (z*dimension3*dimension4) + (y*dimension4)
	MOVL	-16(%RBP), %EAX   <-- x
	CLTQ                      <-- convierte el contenido del registro AX de double-word a quad-word
	ADDQ	%RAX, %RDX        <-- (j*dimension2*dimension3*dimension4) + (z*dimension3*dimension4) + (y*dimension4) + x
	MOVQ	-24(%RBP), %RAX   <-- base
	ADDQ	%RDX, %RAX        <-- base + (j*dimension2*dimension3*dimension4) + (z*dimension3*dimension4) + (y*dimension4) + x
	MOVB	$3, (%RAX)        <-- *(...) = 3 , es decir: asigna el valor 3 a lo apuntado.
	ADDL	$1, -16(%RBP)     <-- x++

//
// NOTA: Asumiendo un modelo de programacion de 64 bits, veamos lo que hace la operacion SALL:
//
// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001  <-- valor inicial (asumiendo valor 1)
// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0100  <-- SALL $2, %EAX (multiplica por 4 el valor)
// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1000  <-- SALL $3, %EAX (multiplica por 8 el valor)
// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001 0000  <-- SALL $4, %EAX (multiplica por 16 el valor)
//

.L5:
	CMPL	$3, -16(%RBP)            <-- como la dimension4 es 4 el for compara x < 4 (es decir 3).
	JLE		.L6
	ADDL	$1, -12(%RBP)     <-- y++

.L4:
	CMPL	$1, -12(%RBP)
	JLE		.L7
	ADDL	$1, -8(%RBP)      <-- z++

.L3:
	CMPL	$1, -8(%RBP)
	JLE		.L8
	ADDL	$1, -4(%RBP)      <-- j++

.L2:
	CMPL	$1, -4(%RBP)      <-- como la dimension1 es 2 el primer for compara j < 2 (es decir 1).
	JLE		.L9
	ADDQ	$32, %RSP
	POPQ	%RBP
	RET

/* --------------------------------------------------------------- */
/* Ejemplo de generacion de codigo de una sentencia switch...case: */
/* --------------------------------------------------------------- */
void prueba_case()
{
	int valor = 10;
	int salida = 0;

	switch(valor)
	{
		case 2:
				salida *= valor;
				break;
		case 4:
				salida = (valor * 500) / 100;
				break;
		case 7:
				salida += valor;
				break;
		case 10:
				salida = valor / 2;
				break;
		default:
				salida = 1;
	}
}

_Z11prueba_casev:

.LFB1:
	PUSHQ	%RBP
	MOVQ	%RSP, %RBP
	SUBQ	$16, %RSP
	MOVL	$10, -4(%RBP)
	MOVL	$0, -8(%RBP)
	MOVL	-4(%RBP), %EAX
	CMPL	$4, %EAX
	JE		.L12
	CMPL	$4, %EAX
	JG		.L13
	CMPL	$2, %EAX
	JE		.L14
	JMP		.L11

.L13:
	CMPL	$7, %EAX
	JE		.L15
	CMPL	$10, %EAX
	JE		.L16
	JMP		.L11

.L14:
		case 2:
				salida *= valor;
				break;

	MOVL	-8(%RBP), %EAX
	IMULL	-4(%RBP), %EAX
	MOVL	%EAX, -8(%RBP)
	JMP		.L10

.L12:
		case 4:
				salida = (valor * 500) / 100;
				break;

	MOVL	-4(%RBP), %EAX
	IMULL	$500, %EAX, %ECX
	MOVL	$1374389535, %EDX   <-- el algoritmo usado por el compilador c++ no utiliza la operacion DIV del Intel x64.
	MOVL	%ECX, %EAX              En su lugar utiliza un algoritmo basado en desplazamientos y escalamiento.
	IMULL	%EDX
	SARL	$5, %EDX
	MOVL	%ECX, %EAX
	SARL	$31, %EAX
	SUBL	%EAX, %EDX
	MOVL	%EDX, %EAX
	MOVL	%EAX, -8(%RBP)
	JMP		.L10

.L15:
		case 7:
				salida += valor;
				break;

	MOVL	-4(%RBP), %EAX
	ADDL	%EAX, -8(%RBP)
	JMP		.L10

.L16:
		case 10:
				salida = valor / 2;
				break;

	MOVL	-4(%RBP), %EAX
	MOVL	%EAX, %EDX
	SHRL	$31, %EDX
	ADDL	%EDX, %EAX
	SARL	%EAX
	MOVL	%EAX, -8(%RBP)
	JMP		.L10

.L11:
		default:
				salida = 1;

	MOVL	$1, -8(%RBP)

.L10:
	ADDQ	$16, %RSP
	POPQ	%RBP
	RET

#
# Ejemplo de codigo assembler generado para la siguiente funcion Fibonnaci:
int fib(int n) { if(n == 0 || n == 1) return(n); return(fib(n - 1) + fib(n - 2)); }

_Z3FIBI:
	PUSHQ	%RBP
	PUSHQ	%RBX
	SUBQ	$40, %RSP
	LEAQ	128(%RSP), %RBP
	MOVL	%ECX, -64(%RBP)
	MOVL	-64(%RBP), %EAX
	TESTL	%EAX, %EAX
	JE		.L2
	MOVL	-64(%RBP), %EAX
	CMPL	$1, %EAX
	JNE		.L3

.L2:
	MOVL	-64(%RBP), %EAX
	JMP		.L4

.L3:
	MOVL	-64(%RBP), %EAX
	SUBL	$1, %EAX
	MOVL	%EAX, %ECX
	CALL	_Z3FIBI
	MOVL	%EAX, %EBX
	MOVL	-64(%RBP), %EAX
	SUBL	$2, %EAX
	MOVL	%EAX, %ECX
	CALL	_Z3FIBI
	ADDL	%EBX, %EAX

.L4:
	ADDQ	$40, %RSP
	POPQ	%RBX
	POPQ	%RBP
	RET
