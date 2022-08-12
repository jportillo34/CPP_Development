#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


fstream   finSIX;   // Archivo conteniendo los contratos registrados en SIX.
fstream   finIBS;   // Archivo conteniendo los contratos registrados en IBS.
fstream   foutFalt;   // Archivo que contendra el faltante.
fstream   foutSobr;   // Archivo que contendra el sobrante.

char sepdr = ' ';   // Separador de campos en los archivos leidos.
char sepdrS = ',';  // Separador de campos en los archivos de salida.


/* ----------------------------------------------------------------------- *
 * Objeto que representa un contrato con su monto de transaccion asociado. *
 * ----------------------------------------------------------------------- */
class contrato
{
   private:
      long long int numCon;    // Numero de Contrato.
      long double monto;       // Monto de la transaccion.
      int indCnc;              // Indicador de coincidencia (contrato SIX vs lista de contratos IBS). Leer notas abajo.
   public:
      long long int getNumCon() const { return(numCon); }     // Funcion que devuelve el numero de contrato.
      double getMonto() { return(monto); }                    // Funcion que devuelve el monto asociado al contrato.
      int getInd() { return(indCnc); }                        // Funcion que devuelve el indicador de coincidencia de la primera pasada.
      void setNumCon(long long int contrato) { numCon = contrato; }
      void setMonto(long double imonto) { monto = imonto; }
      void setInd(int indicador) { indCnc = indicador; }
};


typedef vector<contrato> vectorContratos;   // Tipo de dato "Vector de contratos".



// string patron   = "";   // Patron de busqueda.
/*
void imprimeOcurrencias(string txt, string pat)
{
   int found = txt.find(pat);

   while (found != string::npos) {
      cout << "Patron encontrado en la posicion: " << found << endl;

      found = txt.find(pat, found + 1);
   }
}
*/


bool mifuncion(const contrato & contra1, const contrato & contra2)
{
   return contra1.getNumCon() < contra2.getNumCon();
}

/* ----------------------------------------------------------------- */
/* Funcion que ordena un vector de contratos por numero de contrato. */
/* ----------------------------------------------------------------- */
void ordenaContr(vectorContratos & vector)
{
   sort(vector.begin(), vector.end(), mifuncion);

   /* Esta forma de realizar el sort (usando una Lambda function) no es soportada por algunos compiladores.
   std::sort(vector.begin(), vector.end(), [](contrato & contra1, contrato & contra2)
   {
      return contra1.getNumCon() < contra2.getNumCon();
   });
   */
}


/* --------------------------------------------------------------------------------------------------- *
 * Funcion que convierte un string de campos con separador y llena un elemento del vector de contratos *
 * --------------------------------------------------------------------------------------------------- */
void llenaContr(const string & str, char separador, vectorContratos & vector)
{
   size_t   posi1 = 0;
   size_t   posi2 = 0;
   contrato   elemento;
   string   montoTemp = "";


   // Busca el caracter separador para obtener el numero de contrato.
   posi2 = str.find(separador, posi1);

   if(posi2 != str.npos) {
      if (posi2 > posi1) {
         // Toma el numero de contrato y lo convierte a numerico.
         elemento.setNumCon(stoll(str.substr(posi1, posi2-posi1)));

         posi1 = posi2 + 1;

         montoTemp = str.substr(posi1, str.find_first_of("\n"));
         montoTemp.erase(remove( montoTemp.begin(), montoTemp.end(), '\"' ), montoTemp.end());   // Elimina cualquier comilla doble.


         replace(montoTemp.begin(), montoTemp.end(), ',', '.');   // Reemplaza la coma por un punto decimal.


         elemento.setMonto(stold(montoTemp));   // Convierte el monto en numero decimal.

         elemento.setInd(0);   // Inicia el indicador de coincidencia de primera pasada con cero (0).

         vector.push_back(elemento);   // Almacena el elemento en el vector de contratos.

         montoTemp = "";
      }
   }
}


/* ------------------------------------------------------------- *
 * Funcion que convierte un contrato en un string con separador. *
 * ------------------------------------------------------------- */
string convSep(contrato & contIn)
{
   string soutput = "";
   string strMont = to_string(contIn.getMonto());

   replace(strMont.begin(), strMont.end(), '.', ',');          // Reemplaza el punto decimal por la coma decimal.
   soutput = to_string(contIn.getNumCon()) + sepdr + strMont;

   return(soutput);
}


/* ------------------------------------------------------ *
 * Funcion que graba un contrato en un archivo de salida. *
 * ------------------------------------------------------ */
void grabaContrato(contrato contSalida, fstream & archivo)
{
   string   outptr = "";   // Almacenara cada string (fila) que se escribira al archivo de salida.

   outptr = convSep(contSalida);   // Convierte el contrato en un string con separador.

   archivo << outptr << endl;   // Graba el string en el archivo de salida.
}



/* ------------------------------------------------------------------------------------------------------ */
/* Para compilar este fuente se utilizó el compilador de C++ del producto MinGW para Windows.             */
/* También puede ser compilado en el sistema operativo Linux y en varios sabores de Unix que soporten     */
/* el estándar ISO C++11:                                                                                 */
/*                                                                                                        */
/* c++ -std=c++11 difSIX_ver5.cpp -o difSIX                                                               */
/*                                                                                                        */
/*                                                                                                        */
/* Descripticion: Lee los archivos de contratos (tanto del IBS como del SIX) e identifica las diferencias */
/*                como sobrantes (SIP/IBS) y faltantes (SIX).                                             */
/*                                                                                                        */
/* NOTAS:                                                                                                 */
/*    - Cada archivo de entrada contiene los contratos y sus montos asociados separados por un caracter   */
/*      blanco.                                                                                           */
/*    - Compara cada contrato SIX (y su monto asociado) contra toda la lista de contratos (y montos) del  */
/*      IBS. Una coincidencia se da cuando los contratos son iguales y la diferencia entre sus montos es  */
/*      cero. Los números de contrato (y su monto) pudieran aparecer repetidos N veces en cada grupo.     */
/*      En casos como este, la primera coincidencia será tomada como no diferencia (no es faltante ni es  */
/*      sobrante). Las siguientes coincidencias serán tomadas, automáticamente, como faltantes (para el   */
/*      caso de SIX) o como sobrantes (para el caso de IBS). El programa utiliza un indicador de          */
/*      coincidencia asociado al contrato, con los siguientes valores posibles:                           */
/*                                                                                                        */
/*                                                        -1 ----> Primera coincidencia                   */
/*                                                         0 ----> No es primera coincidencia             */
/*                                                                                                        */
/*      - En la primera parte, el algoritmo compara cada contrato SIX contra la lista de contratos IBS,   */
/*        detectando todas las primeras coincidencias (coloca los indicadores con valor -1).              */
/*      - Al final, envía al archivo de faltantes todo contrato SIX cuyo indicador tenga valor cero. Y    */
/*        lo mismo hace con los contratos IBS: todo contrato IBS cuyo indicador esté en cero lo envía al  */
/*        archivo de sobrantes.                                                                           */
/*                                                                                                        */
/*      Ejemplo:                                                                                          */
/*                                                                                                        */
/*             SIX                                                            IBS                         */
/*  Ind Contrato       Monto                                      Contrato         Monto     Ind          */
/*  ----------------------------                                  --------------------------------        */
/*  -1  04165736122    5000.00 --- Primera coincidencia   ------->04165736122      5000.00   -1           */
/*                               (no es una diferencia)  |                                                */
/*   0  04165736122    5000.00 --- Segunda coinc. -------|        02887711124   2423848.10                */
/*                               (es un faltante)        |                                                */
/*   0  04165736122    5000.00 --- Tercera coinc. -------     ----02126815363    250727.42   -1           */
/*                               (es un faltante)            |----02126815363    250727.42    0           */
/*                                                           |                                            */
/*  -1  02126815363  250727.42<---- Primera coinc. ----------|    02353418840    910529.66                */
/*                                (no es una diferencia)     |                                            */
/*   0  02126815363  250727.42<---- Segunda coinc. ----------                                             */
/*                                (es un sobrante)                                                        */
/*                                                                                                        */
/*    - Esta aplicación ordena ambas listas de contratos. Este paso pudiera no ser necesario.             */
/*    - Los montos asociados a cada contrato deben tener el siguiente formato (en los archivos entrantes: */
/*                                                                                                        */
/*      xxxxxxxxxxx,xx  o  xxxxxxxxxx.xx                                                                  */
/*                                                                                                        */
/*    - Graba dos archivos: uno con el sobrante (SIP/IBS) y otro con el faltante (SIX).                   */
/*                                                                                                        */
/*                                                                                                        */
/* Analista: José Portillo, Newtechsistemas                                                               */
/* Fecha...: Enero 2022                                                                                   */
/* ------------------------------------------------------------------------------------------------------ */
int main()
{
   string   inputr = "";   // Variable que almacenara cada string (fila) leido desde el archivo de entrada.

   contrato   contSix;   // Representa un contrato registrado en SIX.
   contrato   contIBS;   // Representa un contrato registrado en IBS.

   vectorContratos   vecSIX;       // Vector que contendra los contratos registrados en SIX.
   vectorContratos   vecIBS;       // Vector que contendra los contratos registrados en IBS.


   finSIX.open("datosSIX.txt", ios::in);   // Abre el archivo de contratos SIX.
   foutFalt.open("faltante.csv", ios::out);   // Abre el archivo que contendra el faltante.

   finIBS.open("datosIBS.txt", ios::in);   // Abre el archivo de contratos IBS.
   foutSobr.open("sobrante.csv", ios::out);   // Abre el archivo que contendra el sobrante.


   // Valida que el archivo de contratos SIX contenga registros.
   if (!finSIX) {
       cout << "No hay registros contratos desde SIX!" << endl;
       return 0;
   }

   // Valida que el archivo de contratos IBS contenga registros.
   if (!finIBS) {
       cout << "No hay registros contratos desde IBS!" << endl;
       return 0;
   }


   // Ciclo de lectura de contratos SIX.
   while(getline(finSIX, inputr))
   {
      llenaContr(inputr, sepdr, vecSIX);       // Adiciona el contrato leido al vector SIX.

      // Limpia el string de entrada para una nueva lectura.
      inputr = "";
   }

   // Limpia el string de entrada para una nueva lectura.
   inputr = "";

   // Ciclo de lectura de contratos IBS.
   while(getline(finIBS, inputr))
   {
      llenaContr(inputr, sepdr, vecIBS);   // Adiciona el contrato leido al vector IBS.

      // Limpia el string de entrada para una nueva lectura.
      inputr = "";
   }

   ordenaContr(vecSIX);       // Ordena la lista de contratos SIX.
   ordenaContr(vecIBS);       // Ordena la lista de contratos IBS.


   /* ----------------------------------------------------------------------------------------- */
   /* PROCEDE A COMPARAR CADA CONTRATO SIX CONTRA LA LISTA DE CONTRATOS IBS. Leer notas arriba. */
   /* ----------------------------------------------------------------------------------------- */
   // Compara cada contrato SIX contra los contratos en el vector IBS. Leer las notas arriba.
   for(vector<contrato>::iterator i = vecSIX.begin(); i != vecSIX.end(); i++)
   {
      long double montoDif = 0.0;

      // Itera a traves de la lista de contratos IBS en busca de coincidencias con el contrato SIX en curso.
      for(vector<contrato>::iterator j = vecIBS.begin(); j != vecIBS.end(); j++)
      {    
         montoDif = 0.0;
         montoDif = i->getMonto() - j->getMonto();   // Calcula la diferencia entre ambos montos.

         // Verifica si los números de contrato coinciden y si sus montos asociados son iguales.
         if((i->getNumCon() == j->getNumCon()) && !montoDif) { 
            /* -----------------------------------------------------------------------------------------------*/
            /* Si se trata de la primera coincidencia del contrato SIX en curso, entonces activa el indicador */
            /* de primera coincidencia en ambos contratos.                                                    */
            /* -----------------------------------------------------------------------------------------------*/
            if(!i->getInd() && !j->getInd()) { i->setInd(-1); j->setInd(-1); continue; }   // Entonces ambos contratos son primera coincidencia.
         }
      }
   }

   // Itera a traves de la lista de contratos SIX. Todo contrato cuyo indicador tenga valor cero sera declarado como faltante.
   for(vector<contrato>::iterator i = vecSIX.begin(); i != vecSIX.end(); i++) if(!i->getInd()) i->setInd(1);

   // Itera a traves de la lista de contratos IBS. Todo contrato cuyo indicador tenga valor cero sera declarado como sobrante.
   for(vector<contrato>::iterator j = vecIBS.begin(); j != vecIBS.end(); j++) if(!j->getInd()) j->setInd(2);


/*
   cout << "CONTRATOS SIX: " << endl;
   for(vector<contrato>::iterator i = vecSIX.begin(); i != vecSIX.end(); i++)
   {
      cout << i->getNumCon() << "   Monto SIX: " << i->getMonto() << "   Indicador: "  << i->getInd() << endl;
   }
   cout << "CONTRATOS IBS: " << endl;
   for(vector<contrato>::iterator j = vecIBS.begin(); j != vecIBS.end(); j++)
   {
      cout << j->getNumCon() << "   Monto SIX: " << j->getMonto() << "   Indicador: "  << j->getInd()  << endl;
   }
*/



   /* ---------------------------------------------------------- */
   /* PROCEDE A GRABAR EN LOS ARCHIVOS DE FALTANTES Y SOBRANTES. */
   /* ---------------------------------------------------------- */
   for(vector<contrato>::iterator i = vecSIX.begin(); i != vecSIX.end(); i++)
   {
      // Graba el contrato con indicador "1" en el archivo de faltantes.
      if(i->getInd() == 1) grabaContrato(*i, foutFalt);
   }


   for(vector<contrato>::iterator j = vecIBS.begin(); j != vecIBS.end(); j++)
   {
      // Graba el contrato con indicador "2" en el archivo de sobrantes.
      if(j->getInd() == 2) grabaContrato(*j, foutSobr);
   }


   // Cierra los archivos.
   finSIX.close();
   foutFalt.close();
   finIBS.close();
   foutSobr.close();

   return 0;
}
