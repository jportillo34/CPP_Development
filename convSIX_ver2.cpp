#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


// Objetos archivos de entrada, salida y archivo de parametros.
fstream   finputSIX;
fstream   finputIBS;
fstream   foutputSIX;
fstream   foutputIBS;
fstream   fparam;


// Registros de entrada y salida.
string inputr   = "";
string outptr   = "";


/* ------------------------------------------ */
/* Elimina los espacios blancos de un string. */
/* ------------------------------------------ */
void elimEsp(string & cadena)
{
   cadena.erase(std::remove_if(cadena.begin(), cadena.end(), ::isspace), cadena.end());
}



/* ---------------------------------------------------------------------------------------------------- */
/* Descripticion: Convierte un archivo en formato texto hacia un archivo con caracter separador blanco. */
/* ---------------------------------------------------------------------------------------------------- */
int main()
{
   string contrato = "";
   string monto = "";


   // Archivo conteniendo los contratos en la base de datos de SIX.
   finputSIX.open("sixdata.csv", ios::in);

   // Archivo conteniendo los contratos y sus montos asociados con separador.
   foutputSIX.open("datosSIX.txt", ios::out);

   // Archivo conteniendo los contratos en la base de datos de SIX.
   finputIBS.open("ibsdata.csv", ios::in);

   // Archivo conteniendo los contratos y sus montos asociados con separador.
   foutputIBS.open("datosIBS.txt", ios::out);



   // Valida que el archivo de base de datos SIX contenga registros.
   if (!finputSIX || !finputIBS) {
       cout << "No hay registros contratos desde SIX o desde IBS!" << endl;
       return 0;
   }else {
      // Descarta la primera linea de titulos de las columnas del archivo de datos SIX.
      // getline(finputSIX, inputr);
   }


   // Ciclo de lectura de contratos SIX.
   while(getline(finputSIX, inputr))
   {
      if(inputr.substr(0, 2) == "0 ") inputr = "         " + inputr;

      outptr = inputr;

      foutputSIX << outptr << endl;   // Escribe en el archivo de salida.

      // Limpiamos los registros de entrada y salida para una nueva lectura.
      inputr = ""; outptr = ""; contrato = ""; monto = "";
   }


   // Limpiamos los registros de entrada y salida para una nueva lectura.
   inputr = ""; outptr = "";


   string strMonto = "";

   // Ciclo de lectura de contratos IBS.
   while(getline(finputIBS, inputr))
   {
      std::replace(std::begin(inputr),std::end(inputr),'\t',' ');        // Elimina cualquier caracter Tab.

      if(inputr.substr(0, 1) == "0") {
         contrato = "         0";

         strMonto = inputr.substr(2, inputr.find_first_of("\n"));   // Toma el string del monto.
      }
      else{
         contrato = inputr.substr(0, 10);                                   // Toma el string del contrato.
         elimEsp(contrato);                                                 // Elimina cualquier espacio blanco.

         strMonto = inputr.substr(11, inputr.find_first_of("\n"));   // Toma el string del monto.
      }

      outptr = contrato + " " + strMonto;                                // Arma la fila conteniendo el contrato y el monto con separador.

      foutputIBS << outptr << endl;                                      // Escribe en el archivo de salida.

      // Limpiamos los registros de entrada y salida para una nueva lectura.
      inputr = ""; outptr = ""; contrato = ""; monto = "";
   }


/*
   // Ciclo de lectura de contratos.
   while(getline(finput, inputr))
   {
      if(inputr.length() < 120) {
         outptr = string("   ;") + string("   ;") + string("   ;") + inputr;
      }else {
         // Llenamos los datos del registro leido.
         outptr = inputr.substr(11, 6) + " " + inputr.substr(31, 4) + ";" + inputr.substr(18, 12) + ";" + inputr.substr(42, 10) + ";" + inputr.substr(120, inputr.find_first_of("\n"));
      }

      foutput << outptr << endl;   // Escribe una linea en el archivo de salida.

      // Limpiamos los registros de entrada y salida para una nueva lectura de registro desde el log.
      inputr = ""; outptr = "";
   }
*/

   // Cierra los archivos.
   finputSIX.close();
   foutputSIX.close();
   finputIBS.close();
   foutputIBS.close();

   return 0;
}
