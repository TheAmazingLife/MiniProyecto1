#include <iostream>

#include "include\ListArr.hpp"

using std::cout;

// Para compilar el programa: g++ -o programa main.cpp source/*.cpp -I include
/** //* Ideas
 * - Cada vez que aumentamos la capacidad de ListArr (agregar DataNodes), 
 *   doblaremos la cantidad actual de DataNodes.
 * 
 * - Usar una lista doble ligada para los DataNodes, para asi poder desplazar 
 *   los datos de los arreglos de manera mas eficiente.
 * 
 * - Iniciar la cantidad de nodos
 */

int main() {
    int maxCapacity = 3;

    cout << "Creando lista con capacidad maxima de " << maxCapacity << " elementos por nodo de datos..." << '\n';
    ListArr myList(maxCapacity);

    cout << "* Insertando valores en la lista..." << '\n';

    for (int i = 0; i < (maxCapacity*16)+1; i++) {
        // myList.insert(i+1, i);
        myList.insert_left(i+1);

        // if (i < 10) myList.insert(i+1, 0);
        // else myList.insert(i + 1, 10);

        myList.print();
    }

    return 0;
}
