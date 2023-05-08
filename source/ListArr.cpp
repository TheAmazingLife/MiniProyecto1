#include "..\include\ListArr.hpp"

#include <iostream>
#include <stack>

//* Métodos públicos
ListArr::ListArr(int dataCap) : dataMaxCapacity(dataCap) {
    head = new DataNode(dataMaxCapacity);
    tail = new DataNode(dataMaxCapacity);
    head->next = tail;
    tail->previous = head;
    dataNodes_count = 2;

    summaryRoot = new SummaryNode(head, tail); // * no necesita armar un arbol ya que es el primer summary node
    
    vectorSummaryNodes.push_back(summaryRoot);
}

ListArr::~ListArr() {
    // TODO: Eliminar todos los nodos
}

void ListArr::insert(int v, int index) {
    // Comprobar si el indice es valido
    if (index < 0 || index > summaryRoot->usedCapacity) {
        std::cout << "Index out of bounds" << std::endl;
        return;
    }

    // Comprobar si se necesita expandir la capacidad de ListArr
    if (summaryRoot->usedCapacity == summaryRoot->MaxCapacity) {
        
    }
}

void ListArr::insert_left(int v) {
    // inserta en la posicion 0 de head y desplaza a los demas
}

void ListArr::insert_right(int v) {
    // inserta en la posicion dataMaxCapacity de tail y desplaza a los demas
}

void ListArr::print() {
    std::cout << "ListArr: " << std::endl;

    DataNode* current = head;
    while (current != nullptr) {
        std::cout << "[";
        for (int i = 0; i < current->usedCapacity; i++) {
            std::cout << current->array[i];
            if (i < current->usedCapacity - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        current = current->next;
    }
    std::cout << std::endl;
}

int ListArr::size() {
    return summaryRoot->usedCapacity;
}

bool ListArr::find(int v) {
    DataNode* current = head;
    while (current != nullptr) {
        for (int i = 0; i < current->usedCapacity; i++) {
            if (current->array[i] == v) {
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

//* Métodos privados
void ListArr::expandListArr() {
    // Agregar los nuevos nodos de datos
    for (int i = 0; i < dataNodes_count; i++) {
        DataNode* newDataNode = new DataNode(dataMaxCapacity);
        newDataNode->previous = tail;
        tail->next = newDataNode;
        tail = newDataNode;

        // Crear summaryNodes para cada par (Primera linea de summaryNodes)
        if (i+1 % 2 == 0) {
            SummaryNode* newSummaryNode = new SummaryNode(newDataNode->previous, newDataNode);
            vectorSummaryNodes.push_back(newSummaryNode);
        }
        // TODO: Crear summaryNodes padres de los summaryNodes de la primera linea
    }
    
    dataNodes_count *= 2; // Actualizar la cantidad de DataNodes (se duplica)

    // ? generar los nuevos nodos summ, luego recorrer para que se linkeen en base a for i = 1, left 2i y right 2i+1  

    // * Generar arbol de summaryNodes y asignar raiz a summaryRoot
    summaryRoot = buildTree();
}

// * metodo creador de nodo raiz en base a nodos base
// ? se puede optimizar para que no se tenga que repetir por cada duplicado
// * Agrega la raiz para asi sacar sus nodos vecinos de nivel
// * YA LA OPTIMICE UWU
// ! poner ojo en el enlazado entre izquierda y derecha
SummaryNode* ListArr::buildTree() {
    std::stack<SummaryNode*> tree;
    // generamos los nodos padre de los ultimos nodos generados
    for (int i = vectorSummaryNodes.size() - 1; i >= 0; i-=2) { // agrega los nodos de manera inversa, de derecha a izquierda
        SummaryNode* auxSummNode = gen_summ(vectorSummaryNodes[i-1], vectorSummaryNodes[i]);
        pila.push(auxSummNode);
    }    

    // de la primera generacion de padres generamos padres hasta que lleguemos al mismo nivel que la raiz
    while (tree.size != 1) {
        SummaryNode* auxSummL, auxSummR;
        auxSummR = tree.pop();
        auxSummL = tree.pop();
        SummaryNode* auxSummNode = gen_summ(auxSummL, auxSummR);
        pila.push(auxSummNode);
    }
    tree.push(summaryRoot); // agrega la raiz para asi no calcular nuevamente los nodos summary

    // generamos el nuevo ultima raiz

}

/* SummaryNode* ListArr::buildTree() {
    int n = this->vectorSummaryNodes.size();
    
    // crear un vector de punteros a SummaryNode y llenarlo de NULL
    std::vector<SummaryNode*> tree(n+1, nullptr);

    // crear los nodos finales y asignarlos a los índices correspondientes
    for (int i = 0; i < n; i++) {
        tree[i+1] = this->vectorSummaryNodes[i];
    }

    // agregar los hijos de cada nodo
    for (int i = 1; i <= n/2; i++) {
        if (tree[i] != nullptr) {
            tree[i]->SummNodeL = tree[2*i];
            tree[i]->SummNodeR = tree[2*i+1];
        }
    }
    return tree[1]; // devolver la raíz del árbol
} */

/* // Insertar un nodo de datos en el arbol como una hoja
void ListArr::insertSumm(SummaryNode* data) {
    this->vectorSummaryNodes.push_back(data);
} */