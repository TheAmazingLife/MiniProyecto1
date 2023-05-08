#include <iostream>

#include "include\ListArr.hpp" // ! Incluir bien los datos

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
    std::cout << "Hello World!" << std::endl;
    int b = 4;
    ListArr* listArr1 = new ListArr(b);
    listArr1->insert(1, 0);
    listArr1->insert(2, 0);
    listArr1->insert(3, 0);
    listArr1->insert(4, 0);
    listArr1->insert_left(5);
    listArr1->insert_right(6);

    listArr1->print();    

    return 0;
}
