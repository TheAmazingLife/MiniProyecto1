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
  std::cout << "Creando lista con capacidad máxima de 3 elementos por nodo de datos..." << std::endl;
  ListArr myList(3);
  std::cout << "Size del arreglo: "<< myList.size() << std::endl;


  std::cout << "Insertando valores en la lista..." << std::endl;
  std::cout << "A" << std::endl;
  myList.insert_left(10);
  std::cout << "B" << std::endl;
  myList.insert_right(20);
  std::cout << "C" << std::endl;
  myList.insert(30, 1);
  std::cout << "D" << std::endl;
  myList.insert_left(5);
  std::cout << "E" << std::endl;
  myList.insert_right(25);
  std::cout << "F" << std::endl;
  myList.insert(15, 2);

  std::cout << "Imprimiendo valores de la lista..." << std::endl;
  myList.print();

  std::cout << "Buscando valores en la lista..." << std::endl;
  std::cout << "¿El valor 15 está en la lista? " << (myList.find(15) ? "Sí" : "No") << std::endl;
  std::cout << "¿El valor 25 está en la lista? " << (myList.find(25) ? "Sí" : "No") << std::endl;
  std::cout << "¿El valor 35 está en la lista? " << (myList.find(35) ? "Sí" : "No") << std::endl;

  std::cout << "Número de elementos en la lista: " << myList.size() << std::endl;

  return 0;
}
