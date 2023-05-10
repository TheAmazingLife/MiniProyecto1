#include "include\ListArr.hpp"

#include <iostream>

using std::cout;

//? Para compilar y ejecutar el programa: "g++ main.cpp source/*.cpp -o main && ./main"

/* //* Ideas
 * - Cada vez que aumentamos la capacidad de ListArr (agregar DataNodes), 
 *   doblaremos la cantidad actual de DataNodes.
 * - Usar una lista doble ligada para los DataNodes, para asi poder desplazar 
 *   los datos de los arreglos de manera mas eficiente.
 * - Iniciar la cantidad de nodos
 */

int main() {
    int maxCapacity = 1;

    cout << "Creando lista con capacidad maxima de " << maxCapacity << " elementos por nodo de datos..." << '\n';
    ListArr myList(maxCapacity);

    cout << "* Insertando valores en la lista..." << '\n';

    // for (int i = 0; i < (maxCapacity*32)+1; i++) {
    for (int i = 0; i < 1000; i++) {
        // myList.insert(i+1, i);

        myList.insert_left(i+1);
        // myList.insert_right(i+1);

        myList.print();
    }

    return 0;
}
