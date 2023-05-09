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

  std::cout << "Insertando valores en la lista..." << std::endl;
  myList.insert_left(10);
  myList.insert_right(20);
  myList.insert(30, 1);
  myList.insert_left(5);
  myList.insert_right(25);
  myList.insert(15, 2);

  std::cout << "Imprimiendo valores de la lista..." << std::endl;
  myList.print();

  std::cout << "Buscando valores en la lista..." << std::endl;
  std::cout << "¿El valor 15 está en la lista? " << (myList.find(15) ? "Sí" : "No") << std::endl;
  std::cout << "¿El valor 25 está en la lista? " << (myList.find(25) ? "Sí" : "No") << std::endl;
  std::cout << "¿El valor 35 está en la lista? " << (myList.find(35) ? "Sí" : "No") << std::endl;

  std::cout << "Número de elementos en la lista: " << myList.size() << std::endl;

    // Segundo main comprobador

  // Creamos una lista vacía con capacidad de cada DataNode igual a 2
  ListArr list(2);

  // Insertamos algunos elementos en la lista
  list.insert_left(10);
  list.insert_right(20);
  list.insert_left(5);
  list.insert_right(15);
  list.insert_left(0);
  list.insert_right(25);

  // Imprimimos los valores en la lista
  std::cout << "Valores en la lista: ";
  list.print();

  // Buscamos algunos valores en la lista
  int val1 = 5, val2 = 15, val3 = 30;
  std::cout << "Buscar valores " << val1 << ", " << val2 << ", " << val3 << " en la lista" << std::endl;
  std::cout << "Valor " << val1 << (list.find(val1) ? " encontrado" : " no encontrado") << std::endl;
  std::cout << "Valor " << val2 << (list.find(val2) ? " encontrado" : " no encontrado") << std::endl;
  std::cout << "Valor " << val3 << (list.find(val3) ? " encontrado" : " no encontrado") << std::endl;

  // Insertamos un valor en una posición específica
  int index = 2, value = 7;
  std::cout << "Insertar valor " << value << " en la posición " << index << std::endl;
  list.insert(value, index);

  // Imprimimos los valores en la lista de nuevo
  std::cout << "Valores en la lista después de insertar " << value << ": ";
  list.print();

  // Insertamos algunos valores más
  list.insert_left(-5);
  list.insert_right(30);

  // Imprimimos los valores en la lista de nuevo
  std::cout << "Valores en la lista después de insertar -5 y 30: ";
  list.print();

  // Insertamos más valores para hacer que la lista se expanda
  list.insert_right(35);
  list.insert_right(40);
  list.insert_right(45);

  // Imprimimos los valores en la lista de nuevo
  std::cout << "Valores en la lista después de insertar 35, 40 y 45: ";
  list.print();

  return 0;
}
