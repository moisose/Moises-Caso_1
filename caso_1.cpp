/* Caso_1 
Moises Solano Espinoza
2021144322 */

// Importacion de librerias
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include <vector>
#include <algorithm>

using namespace std;

//---------------------------------------------------------------------------------------------------------------
// EJERCICIO 1: COMPARE THE TRIPLETS
//---------------------------------------------------------------------------------------------------------------

/* Este es el algoritmo menos eficiente de los dos
porque para poder llegar a la solución debe de 
recorrer con un ciclo for todos los elementos de
los arrays para compararlos; es decir en cada iteración
se compara el elemento en la posicion i del primer array
con el segundo. */

int compareTheTriplets(int Alice[3], int Bob[3]){
    int result[] = {0,0};

    for (int i = 0; i < 3; i++){ // comparaciones de cada posicion
        if (Alice[i] > Bob[i]){
            result[0]++;
        } 
        if(Alice[i] < Bob[i]){
            result[1]++;
        }  
    }

    cout << "Menos eficiente -> " << result[0] << ", " << result[1] << endl;
    return *result;
}

/* Este es el algoritmo más eficiente para resolver el problema.
En este caso al contrario del anterior, se le asigna directamente
el valor a el resultado realizando comparaciones sin utiizar ciclos
ni if. Solamente con operaciones aritméticas se llega a la solución. */

int compareTheTriplets2 (int Alice[3], int Bob[3]){
    int result[] = {0,0};

    result[0] = (Alice[0] > Bob[0]) + (Alice[1] > Bob[1]) + (Alice[2] > Bob[2]); // asignación directa 
    result[1] = (Bob[0] > Alice[0]) + (Bob[1] > Alice[1]) + (Bob[2] > Alice[2]); // del resultado sin utilizar
                                                                                 // condicionales
    cout << "Mas eficiente -> " << result[0] << ", " << result[1] << endl;
    
    return *result;
}


//---------------------------------------------------------------------------------------------------------------
// EJERCICIO 2: TIME CONVERSION
//---------------------------------------------------------------------------------------------------------------

/* Este algoritmo para el problema de conversión de tiempo es
el menos eficiente de los dos. Se recibe un string del tiempo en
formato 12 horas y lo convierte a 24 utilizando muchos condicionales
if y else para realizar las validaciones. Verifica si tiene un P
de pm para saber si debe sumar 12 (si las horas no son 12 que también
se valida con otro if).
En caso de que sea A de am se solo se debe cambiar las horas si es
un 12. 
Luego de hacer estas validaciones rearma el string resultado utilizando
dos condicionales más. Al final se retorna el resultado. */

string timeConversion (string time){
    string resultado;

    int hours = stoi(time.substr(0, 2)); // substrings
    string hrsMins = time.substr(2, 6);

    if(time[8] == 'P'){ // caso PM
        if (hours != 12){
            hours = hours + 12;
        }
    }
    else{ // caso AM
        if (hours == 12){
            hours = 0;
        }
    }
    // Retorno del resultado
    if (hours < 10){
        resultado += '0';
        resultado += to_string(hours);
    }
    else{
        resultado += to_string(hours);
    }

    resultado += hrsMins;

    return resultado;
}

/* Este es el algoritmo mas eficiente de conversión de tiempo.
En este igual se divide el string ingresado en substrings para
realizar la conversión. Para disminuir las comparaciones se 
utiliza un factor que tendrá el valor de las horas módulo 12
dividido entre las horas. Esto significa que el factor es 0
si las horas son 12, en otro caso será siempre 1. Luego solo utiliza
un if para saber si se tienen que sumar 12 horas o no.

Resumiendo, se evitan hacer tantas comparaciones utilizando el factor. */

string timeConversion2 (string time){
    string format24h = time.substr(2, 6);

    int hours = stoi(time.substr(0, 2));
    int factor = ((hours % 12) / hours); // el factor es 0 solo cuando
                                         // las horas son 12.

    if (time[8] == 'A'){ // se decrementa el factor si es AM
        factor--;
    }

    hours += (12 * factor); // se suman 12 dependiendo del factor

    format24h = (hours < 10) ? "0" + to_string(hours) + format24h : to_string(hours) + format24h;

    return format24h;
}


//---------------------------------------------------------------------------------------------------------------
// EJERCICIO 3: SUBARRAY DIVISION
//---------------------------------------------------------------------------------------------------------------

/* El primer algoritmo para resolver este problema es probablemente
el primero en el que se piensa para recorrer un array varias veces.
Es muy ineficiente porque utiliza un ciclo for para recorrer todos
los elementos, y luego otro ciclo for adentro de él para recorrer
los elementos desde la posición actual la cantidad de veces que diga
el mes. Después de cada segundo ciclo for se valida el resultado parcial
para saber si se tiene que incrementar el resultado. */

int subarrayDivision (int lenght, int numbers[], int date[2]){
    int result = 0;
    int sum = 0;

    for (int i = 0; i < lenght; i++){
        for(int x = 0; x < date[1]; x++){
            sum += numbers[i+x];
        }
        if(sum == date[0]){
            result++;
        }
        sum = 0;
    }
    return result;

}

/* Este es el algoritmo más eficiente para resolver el problema de
Subarray Division. A diferencia del primero solo se utiliza un ciclo
for lo que disminuye la cantidad de iteraciones y comparaciones.
Se lleva una suma parcial para saber si se debe incrementar el resultado.
Se lleva el control para saber si los pedazos son del tamano del mes
y la sum para saber si es igual a los días. En el caso de que se 
encuentre un bloque correcto se suma al resultado y se resta
de la suma el valor que este en la posicion init e init se incrementa.

De esta forma se logra resolver el problema evitando utilizar
varios ciclos for anidados y convirtiendo al algoritmo mas eficiente. */

int subarrayDivision2 (int lenght, int numbers[], int date[2]){
    int init = 0; // posicion de atras
    int result = 0; 
    int sum = 0; // suma parcial
    int control = 1; // tamano del bloque

    for (int i = 0; i < lenght; i++){
        sum += numbers[i];

        if (control == date[1] && sum == date[0]){ // caso en el que el mes y los dias
            result++;                              // concuerdan
            sum -= numbers[init];
            init++;
        }
        else if (control == date[1]){ // caso en el que solo el mes concuerda
            sum -= numbers[init];
            init++;
        }
        else { // caso en el que ninguno de los dos concuerda
            control++;
        }
    }

    return result;
}

//---------------------------------------------------------------------------------------------------------------
// EJERCICIO 4: THE MINION GAME
//---------------------------------------------------------------------------------------------------------------

/* En este algoritmo se utiliza un ciclo for con el largo del string.
Se compara si la letra es una vocal, en este caso se suma al contador
de Kevin el largo de la palabra menos la posición actual, es decir:
el tamaño de la posición actual en adelante.
En caso de que sea consonante se hace lo mismo pero con Stuart. */

string theMinionGame (string stringGame){
    int resStuart = 0;
    int resKevin = 0;
    string resultado = "Draw"; // será retornado
    int largo = stringGame.length();

    for (int i = 0; i < largo; i++){
        char letra = stringGame[i];
        if (letra == 'A' || letra == 'E' || letra == 'I' || letra == 'O' || letra == 'U'){ // caso Kevin
            resKevin += largo - i;
        }
        else{ // caso Stuart
            resStuart += largo - i;             
            }
    }

    if(resStuart > resKevin){
        resultado = "Stuart " + to_string(resStuart);
    }
    else{
        resultado = "Kevin " + to_string(resKevin);
    }

    return resultado;
}


//---------------------------------------------------------------------------------------------------------------
// EJERCICIO 5: CIPHER
//---------------------------------------------------------------------------------------------------------------

/* Este algoritmo se encarga de decodificar el codigo ingresado utilizando xor. */

string cipher (int nums[2], string s){

    int n = nums[0];
    int k = nums[1];
    char result[n];
    
    result[0] = s[0];

    for (int i = 1; i < k; i++){
        result[i] = s[i]==s[i-1]?'0':'1';
    }

    char aux;
    for(int i = k; i < n; i++){
        aux = '0';
        for(int j = i-(k-1); j < i; j++){
            aux = aux==result[j]?'0':'1';
        }
        result[i] = aux==s[i]?'0':'1';
    }

    string final_result = "";
    for (int i = 0; i < nums[0]; i++) {
        final_result += result[i];
    }
    return final_result;
}

//---------------------------------------------------------------------------------------------------------------
// EJERCICIO 6: PAIRS
//---------------------------------------------------------------------------------------------------------------

/* Se utilizan punteros para ir avanzando en los elementos del array
e ir haciendo comparaciones. Se compara el numero mayor con el menor 
porque se ordena el array. */

int pairs (int k, vector<int> arr) {
    
    // Ordenar el array(ascendente)
    sort(arr.begin(), arr.end());
    
    // {Pointer 2, NULL, Pointer1}
    int pointers[] = {1, 0, 0};
    int result = 0;
    int valueDif = 0;
    
    // en este ciclo se van haciendo los recorridos para comparar
    while (pointers[0] < arr.size()) {
        
        // diferencia entre los dos valores comparados
        valueDif = arr[pointers[0]] - arr[pointers[2]];
        
        // Si es lo que busco, aumento pointer2
        if (valueDif == k) {
            result++;
            pointers[0]++;
            continue;
        }
        
        // Mueve el puntero necesario dependiendo si es mayor o menor
        pointers[ ((valueDif - k)/abs(valueDif - k)) + 1 ]++;
    }
    
    return result;
}

//---------------------------------------------------------------------------------------------------------------
// MAIN
//---------------------------------------------------------------------------------------------------------------

int main(){

    // Pruebas ejercicio 1

    cout << "---------------------------------" << endl;
    cout << "PRUEBAS" << endl;
    cout << "---------------------------------" << endl;
    cout << "\n EJERCICIO 1" << endl;
    cout << "---------------------------------" << endl;

    int lista1[3] = {5,6,7};
    int lista2[3] = {3,6,10};
    int lista3[3] = {17,28,30};
    int lista4[3] = {99,16,8};

    cout << "Lista1: " << "{5,6,7}" << ", Lista2: " << "{3,6,10}" << endl;
    compareTheTriplets(lista1,lista2);
    compareTheTriplets2(lista1,lista2);

    cout << "\nLista1: " << "{17,28,30}" << ", Lista2: " << "{99,16,8}" << endl;
    compareTheTriplets(lista3,lista4);
    compareTheTriplets2(lista3,lista4);

    cout << "\n EJERCICIO 2" << endl;
    cout << "---------------------------------" << endl;

    string hora1 = "12:05:45AM";
    string hora2 = "04:55:45PM";

    cout << "Hora: " << hora1 << endl;
    cout << "Menos eficiente -> " << timeConversion(hora1) <<endl;
    cout << "Mas eficiente -> " << timeConversion2(hora1) <<endl;

    cout << "\nHora: " << hora2 << endl;
    cout << "Menos eficiente -> " << timeConversion(hora2) <<endl;
    cout << "Mas eficiente -> " << timeConversion2(hora2) <<endl;

    cout << "\n EJERCICIO 3" << endl;
    cout << "---------------------------------" << endl;
    
    int nums[] = {1,2,1,2,3,1,1,4,1};
    int dates[2] = {6,3};

    int nums2[] = {1,2,1,3,2};
    int dates2[2] = {3,2};

    cout << "Dia: " << dates[0] << " , Mes: " << dates[1] << " , Array: {1,2,1,2,3,1,1,4,1}" << endl;
    cout << "Menos eficiente -> " << subarrayDivision (9, nums, dates) << endl;
    cout << "Mas eficiente -> " << subarrayDivision2 (9, nums, dates) << endl;

    cout << "\nDia: " << dates2[0] << " , Mes: " << dates2[1] << " , Array: {1,2,1,3,2}" << endl;
    cout << "Menos eficiente -> " << subarrayDivision (5, nums2, dates2) << endl;
    cout << "Mas eficiente -> " << subarrayDivision2 (5, nums2, dates2) << endl;

    cout << "\n EJERCICIO 4" << endl;
    cout << "---------------------------------" << endl;

    string palabra = theMinionGame("BANANA");
    string palabra2 = theMinionGame("ARROZ");

    cout << "Palabra: " << "BANANA" << endl;
    cout << palabra << endl;
    cout << "\nPalabra: " << "ARROZ" << endl;
    cout << palabra2 << endl;

    cout << "\n EJERCICIO 5" << endl;
    cout << "---------------------------------" << endl;

    int nk[] = {7,4};
    string s = "1110100110";

    int nk2[] = {6,2};
    string s2 = "1110001";

    cout << "N: " << nk[0] << " , K: " << nk[1] << " , String: " << s << endl;
    cout << "Res: "<< cipher(nk, s) << endl;

    cout << "\nN: " << nk2[0] << " , K: " << nk2[1] << " , String: " << s2 << endl;
    cout << "Res: "<< cipher(nk2, s2) << endl;

    int nk3[] = {5,2};
    int arr[] = {1,5,3,4,2};
    //cout << "Res: "<< pairs(nk3, arr) << endl;

    cout << "\n EJERCICIO 6" << endl;
    cout << "---------------------------------" << endl;

    vector<int> arr1 = {1, 5, 3, 4, 2};

    cout << "N: 5" << " , K: 2" << " , Array: {1, 5, 3, 4, 2}" << endl;
    cout << "Resultado: " << pairs(2, arr1) << endl;

    vector<int> arr2 = {1,2,3,4};
    cout << "\nN: 4" << " , K: 1" << " , Array: {1,2,3,4}" << endl;
    cout << "Resultado: " << pairs(1, arr2) << endl;

    return 0;
}