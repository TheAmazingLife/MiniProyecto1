#include <iostream>

#include "include\ListArr.hpp" // ! Incluir bien los datos

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
  std::cout << "Creando lista con capacidad maxima de 3 elementos por nodo de datos..." << std::endl;
  ListArr myList(3);

  std::cout << "* Insertando valores en la lista..." << std::endl;

  myList.insert_left(10);
  myList.insert_right(20);
  myList.insert(30, 1);
  myList.insert_left(5);
  myList.insert_right(25);
  myList.insert(15, 2);
  std::cout << "Imprimiendo valores de la lista..." << std::endl;
  myList.print();
  std::cout << '\n';

  // std::cout << "El valor 35 esta en la lista? " << (myList.find(35) ? "Si" : "No") << std::endl;
  // std::cout << "Numero de elementos en la lista: " << myList.size() << std::endl;
  myList.printSummaries();
  
  std::cout << "*Testeando expand() de ListArr: \n";
  myList.insert_left(10);
  std::cout << "Imprimiendo valores de la lista..." << std::endl;
  myList.print();
  std::cout << '\n';

  return 0;
}
