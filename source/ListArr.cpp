#include "..\include\ListArr.hpp"

#include <iostream>

#include <stack>
#include <vector>
#include <functional>

using std::cout;

// * Constructor de ListArr
ListArr::ListArr(int dataCap) : dataMaxCapacity(dataCap) {
    dataHead = new DataNode(dataMaxCapacity);
    dataTail = new DataNode(dataMaxCapacity);
    dataHead->next = dataTail;
    dataTail->previous = dataHead;
    dataNodes_count = 2;

    summaryRoot = new SummaryNode(dataHead, dataTail); // * no necesita armar un árbol ya que es el primer summary sumaNode
}

// * Destructor de ListArr
ListArr::~ListArr() {
    typedef std::function<void(SummaryNode*)> Fuction; /**< Apodo de variable función recursiva con parámetro SummaryNode* */
    Fuction deleteSummaryNode = [&](SummaryNode* currSumm) { /**< Función lambda recursiva para eliminar todos los nodos summary */
        if (currSumm == nullptr) return;
        deleteSummaryNode(currSumm->summLeft);
        deleteSummaryNode(currSumm->summRight);
        delete currSumm;
    };
    
    // Eliminar SummaryNodes
    deleteSummaryNode(summaryRoot);

    // Eliminar DataNodes
    while (dataHead != nullptr) {
        DataNode* aux = dataHead;
        dataHead = dataHead->next;
        delete aux;
    }
}

// * Función general para insertar en ListArr
void ListArr::insert(int v, int index) {
    // Comprobar si el indice es valido
    if (index < 0 || index > size()) {
        cout << "Error: Index out of bounds" << '\n';
        return;
    }

    // Comprobar si se necesita expandir la capacidad de ListArr
    if (size() == summaryRoot->maxCapacity) {
        this->expandListArr();
    }
    
    //* Algoritmo del enunciado para encontrar datos en cierto index
    // Recorrer árbol de summaryNodes hasta llegar a un nodo hoja
    SummaryNode* currentSumm = summaryRoot;
    while (currentSumm != nullptr) {
        if (index < currentSumm->summLeft->usedCapacity) {
            currentSumm = currentSumm->summLeft;
        } else {
            index -= currentSumm->summLeft->usedCapacity;
            currentSumm = currentSumm->summRight;
        }
    }

    // Comprobar en que dataNode del summaryNode actual se insertara el valor
    DataNode* currentData;
    if (index < currentSumm->dataLeft->usedCapacity) {
        currentData = currentSumm->dataLeft;
    } else {
        index -= currentSumm->dataLeft->usedCapacity;
        currentData = currentSumm->dataRight;
    }

    // Desplazar los datos de ListArr consecuentes a la posición en que se insertara el valor
    this->shiftDataToRight(currentData, index);

    // Insertar el nuevo valor en el dataNode correspondiente
    currentData->array[index] = v;

    // Actualizar la cantidad de datos en árbol de summaryNodes
    updateSummaryNodes(summaryRoot);
}

// * Subfuncion de insert (insert(v, 0)))
void ListArr::insert_left(int v) {
    insert(v, 0);
}

// * Subfuncion de insert (insert(v, size()))
void ListArr::insert_right(int v) {
    insert(v, size());
}

// * Función para desplazar los datos de ListArr consecuentes a la posición en que se insertara el valor
void ListArr::shiftDataToRight(DataNode* refData, int index) {
    DataNode* currentData = dataTail;

    // Recorrer dataNodes desde tail hasta encontrar dataNode no vació
    while (currentData->usedCapacity == 0) {
        currentData = currentData->previous;
    }

    // Actualizar la cantidad de datos en el dataNode correspondiente
    if (currentData->usedCapacity == currentData->maxCapacity) {
        currentData->next->usedCapacity++;
    } else {
        currentData->usedCapacity++;
    }

    // En el caso que sea necesario desplazar los datos de otros dataNodes...
    if (currentData != refData) {
        // Desplazar datos desde el ultimo dato de ListArr hasta dataNodo siguiente a refData (izq<--der)
        while (true) {
            // Su dataNode actual esta lleno, entonces se mueve ultimo valor al siguiente dataNode
            if (currentData->usedCapacity == currentData->maxCapacity) {
                currentData->next->array[0] = currentData->array[dataMaxCapacity-1];
            }

            // Comprobar si se llego al dataNode en el que se insertara el valor
            if (currentData == refData) break;

            for (int i = currentData->usedCapacity - 1; i > 0; i--) {
                currentData->array[i] = currentData->array[i-1];
            }

            currentData = currentData->previous;
        }
    }

    // Actualizar dataNode en el que se insertara el valor
    for (int i = refData->usedCapacity - 1; i > index; i--) {
        refData->array[i] = refData->array[i-1];
    }
}

// * Función para imprimir ListArr
void ListArr::print() {
    cout << "ListArr: " << '\n';

    DataNode* currentSumm = dataHead;
    while (currentSumm != nullptr) {
        cout << "[";
        for (int i = 0; i < currentSumm->usedCapacity; i++) {
            cout << currentSumm->array[i];
            if (i < currentSumm->usedCapacity - 1) {
                cout << ", ";
            }
        }
        cout << "]";
        currentSumm = currentSumm->next;
    }
    cout << '\n';
}

// * Función que devuelve la cantidad de datos en ListArr
int ListArr::size() {
    return summaryRoot->usedCapacity;
}

// * Función que busca un valor en ListArr
bool ListArr::find(int v) {
    DataNode* currentData = dataHead;
    while (currentData != nullptr) {
        for (int i = 0; i < currentData->usedCapacity; i++) {
            if (currentData->array[i] == v) {
                return true;
            }
        }
        currentData = currentData->next;
    }
    return false;
}

// * Función que expande la capacidad de ListArr
void ListArr::expandListArr() {
    std::vector<SummaryNode*> vecSummaryNodes; /**< Un vector que contiene todos los SummaryNode en la estructura */

    // Agregar los nuevos nodos de datos
    for (int i = 0; i < dataNodes_count; i++) {
        DataNode* newDataNode = new DataNode(dataMaxCapacity);
        newDataNode->previous = dataTail;
        dataTail->next = newDataNode;
        dataTail = newDataNode;

        // Crear summaryNodes para cada par de dataNodes (Primera linea de summaryNodes)
        if ((i + 1) % 2 == 0) {
            SummaryNode* newSummaryNode = new SummaryNode(newDataNode->previous, newDataNode);
            vecSummaryNodes.push_back(newSummaryNode);
        }
    }
    dataNodes_count *= 2; // Actualizar la cantidad de DataNodes (se duplica)

    summaryRoot = buildTree(vecSummaryNodes);

    vecSummaryNodes.clear(); // Vaciar el vector de summaryNodes
}

SummaryNode* ListArr::buildTree(std::vector<SummaryNode*> vecSummaryNodes) {
    std::stack<SummaryNode*> treeStack;

    // generamos los nodos padre de los últimos nodos generados
    for (int i = vecSummaryNodes.size() - 1; i > 0; i -= 2) { // agrega los nodos de manera inversa, de derecha a izquierda
        SummaryNode* auxSummNode = newSummaryParent(vecSummaryNodes[i-1], vecSummaryNodes[i]);
        treeStack.push(auxSummNode);
    }    

    // de la primera generación de padres generamos padres hasta que lleguemos al mismo nivel que la raíz
    while (treeStack.size() != 1) {
        SummaryNode *auxSummL, *auxSummR;
        auxSummL = treeStack.top();
        treeStack.pop();
        auxSummR = treeStack.top();
        treeStack.pop();
        SummaryNode* auxSummNode = newSummaryParent(auxSummL, auxSummR);
        treeStack.push(auxSummNode);
    }
    treeStack.push(summaryRoot); // agrega la raíz para asi no calcular nuevamente los nodos summary

    // generamos el nuevo ultima raíz
    SummaryNode* newRoot = treeStack.top();
    treeStack.pop();
    return newRoot;
}

SummaryNode* ListArr::newSummaryParent(SummaryNode* left, SummaryNode* right) {
    return new SummaryNode(left, right);
}

// TODO: actualizar summaryNodes
// Post Order recorrido

/* void ListArr::postOrder(Nodo *nodo, vector<Nodo*> &resultado) {
    if (nodo == NULL)
    {
      return;
    }
    for (auto hijo : nodo->hijos)
    {
      postOrder(hijo, resultado);
    }
    resultado.push_back(nodo); // va al ultimo hijo y lo agrega
} */

void ListArr::updateSummaryNodes(SummaryNode* currentNodo) {
    if (currentNodo->summLeft == nullptr || currentNodo->summRight == nullptr) {
        return;
    }
    
    updateSummaryNodes(currentNodo->summLeft);
    updateSummaryNodes(currentNodo->summRight);
    
    std::vector<SummaryNode*> hijosCurrent = {currentNodo->summLeft, currentNodo->summRight};
    for (auto hijo : hijosCurrent) {
        updateSummaryNodes(hijo);
    }
    
    currentNodo->usedCapacity = currentNodo->summLeft->usedCapacity + currentNodo->summRight->usedCapacity;
}