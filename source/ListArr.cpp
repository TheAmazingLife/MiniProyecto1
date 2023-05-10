#include "..\include\ListArr.hpp"

#include <iostream>
#include <vector>
#include <deque>
#include <functional>

using std::cout;

// * Constructor de ListArr
ListArr::ListArr(int dataCap) : dataMaxCapacity(dataCap) {
    dataHead = new DataNode(dataMaxCapacity);
    dataTail = new DataNode(dataMaxCapacity, dataHead, nullptr);
    dataHead->next = dataTail;

    dataNodes_count = 2;
    summaryRoot = new SummaryNode(dataHead, dataTail);
}

// * Destructor de ListArr
ListArr::~ListArr() {
    typedef std::function<void(SummaryNode*)> Fuction; /**< Apodo de variable función recursiva con parámetro SummaryNode* */
    Fuction deleteSummaryNodes = [&](SummaryNode* currSumm) { /**< Función lambda recursiva para eliminar todos los nodos summary */
        if (currSumm == nullptr) return;
        deleteSummaryNodes(currSumm->summL);
        deleteSummaryNodes(currSumm->summR);
        delete currSumm;
    };
    
    // Eliminar SummaryNodes
    deleteSummaryNodes(summaryRoot);

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
        cout << "Error: Index out of bounds" << ".\n";
        return;
    }

    // Comprobar si se necesita expandir la capacidad de ListArr
    if (size() == summaryRoot->maxCapacity) {
        this->resize();
    }

    //* Algoritmo del enunciado para encontrar datos en cierto index
    // Recorrer árbol de summaryNodes hasta llegar a un nodo hoja
    SummaryNode* currentSumm = summaryRoot;
    while (currentSumm->summL != nullptr) {
        SummaryNode* left = currentSumm->summL;
        if ((index <= left->usedCapacity && index != left->maxCapacity) || index < dataMaxCapacity) {
            currentSumm = left;
        } else {
            index -= left->usedCapacity;
            currentSumm = currentSumm->summR;
        }
    }
    // Comprobar en que dataNode del summaryNode actual se insertara el valor
    DataNode* currentData;
    if (index <= currentSumm->dataL->usedCapacity && index != dataMaxCapacity) {
        currentData = currentSumm->dataL;
    } else {
        index -= currentSumm->dataL->usedCapacity;
        currentData = currentSumm->dataR;
    }
    //* Fin del algoritmo del enunciado

    // Desplazar los datos de ListArr consecuentes a la posición en que se insertara el valor
    if (index < currentData->usedCapacity && currentData->usedCapacity != 0) {
        // std::cout << "Desplazando datos...\n"; //!
        shiftDataToRight(currentData, index);
    }

    // Insertar el nuevo valor en el dataNode correspondiente
    currentData->array[index] = v;
    currentData->usedCapacity++;

    // Actualizar la cantidad de datos en árbol de summaryNodes
    if (summaryRoot->summL == nullptr) {
        summaryRoot->usedCapacity++;
    } else {
        updateSummaryNodes();
    }
}

// * Sub-función de insert (insert(v, 0)))
void ListArr::insert_left(int v) {
    insert(v, 0);
}

// * Sub-función de insert (insert(v, size()))
void ListArr::insert_right(int v) {
    insert(v, size());
}

// * Función para imprimir ListArr
void ListArr::print() {
    cout << "ListArr: ";
    DataNode* currentData = dataHead;
    while (currentData != nullptr) {
        cout << "[";
        for (int i = 0; i < dataMaxCapacity; i++) {
            if (i < currentData->usedCapacity) {
                cout << currentData->array[i];
            } else {
                cout << " ";
            }
            if (i < dataMaxCapacity-1) cout << ",";
        }
        cout << "]";
        currentData = currentData->next;
    }
    cout << '\n';
    printSummariesNodes();
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
            if (currentData->array[i] == v) return true;
        }
        currentData = currentData->next;
    }
    return false;
}

// * Función que expande la capacidad de ListArr
void ListArr::resize() {
    std::vector<SummaryNode*> vecSummaryNodes; /**< Un vector que contiene todos los SummaryNode en la estructura */

    // Agregar los nuevos nodos de datos
    for (int i = 0; i < dataNodes_count; i++) {
        DataNode* newDataNode = new DataNode(dataMaxCapacity, dataTail, nullptr);
        dataTail->next = newDataNode;
        dataTail = newDataNode;
        // Crear summaryNodes para cada par de dataNodes (primera linea de summaryNodes)
        if ((i + 1) % 2 == 0) {
            SummaryNode* newSummaryNode = new SummaryNode(newDataNode->previous, newDataNode);
            vecSummaryNodes.push_back(newSummaryNode);
        }
    }
    dataNodes_count *= 2; // Actualizar la cantidad de DataNodes (se duplica)

    summaryRoot = buildSummaryTree(vecSummaryNodes);
    vecSummaryNodes.clear(); // Vaciar el vector de summaryNodes
}

// * Función para desplazar los datos de ListArr consecuentes a la posición en que se insertara el valor
void ListArr::shiftDataToRight(DataNode* refData, int index) {
    // Recorrer dataNodes desde tail hasta encontrar dataNode no vació
    DataNode* currentData;
    if (refData->usedCapacity != dataMaxCapacity) {
        currentData = refData;
    } else {
        // * Utilizamos el algoritmo del enunciado para recorrer árbol de summaryNodes y encontrar el ultimo dataNode no vació
        int index = summaryRoot->usedCapacity;
        SummaryNode* currentSumm = summaryRoot;
        while (currentSumm->summL != nullptr) {
            SummaryNode* left = currentSumm->summL;
            if ((index <= left->usedCapacity && index != left->maxCapacity) || index < dataMaxCapacity) {
                currentSumm = left;
            } else {
                index -= left->usedCapacity;
                currentSumm = currentSumm->summR;
            }
        }
        currentData = (index <= currentSumm->dataL->usedCapacity && index != dataMaxCapacity) ? currentSumm->dataL : currentSumm->dataR;
    }

    // Desplazar datos desde el ultimo dato de ListArr hasta dataNodo siguiente a refData (izq<--der)
    while (true) {
        // Su dataNode actual esta lleno, entonces se mueve ultimo valor al siguiente dataNode
        if (currentData->usedCapacity == currentData->maxCapacity) {
            currentData->next->array[0] = currentData->array[dataMaxCapacity-1];
            currentData->next->usedCapacity++;
            currentData->usedCapacity--;
        }
        // Comprobar si se llego al dataNode en el que se insertara el valor
        if (currentData == refData) break;
        // Desplazar datos de dataNode actual
        for (int i = currentData->usedCapacity; i > 0; i--) {
            currentData->array[i] = currentData->array[i-1];
        }
        currentData = currentData->previous;
    }
    // Actualizar dataNode en el que se insertara el valor
    for (int i = refData->usedCapacity; i > index; i--) {
        refData->array[i] = refData->array[i-1];
    }
}

// * Función que genera una nueva SummaryNode raíz a partir de SummaryNodes base
SummaryNode* ListArr::buildSummaryTree(std::vector<SummaryNode*>& vecSummaryNodes) {
    // En caso de que sea el primer duplicado solo se genera la nueva raíz a partir de la `summaryRoot` y el único nuevo nodo vecino
    if (vecSummaryNodes.size() == 1)  {
        SummaryNode* newRoot = new SummaryNode(summaryRoot, vecSummaryNodes[0]);
        return newRoot;
    }
    
    std::deque<SummaryNode*> treeDeque;
    // generamos los nodos padre de los últimos nodos generados
    for (int i = 0; i < vecSummaryNodes.size() - 1; i += 2) { 
        SummaryNode* auxSummNode = new SummaryNode(vecSummaryNodes[i], vecSummaryNodes[i+1]);
        treeDeque.push_back(auxSummNode);
    }

    // de la primera generación de padres generamos padres hasta que lleguemos al mismo nivel que la raíz
    while (treeDeque.size() != 1) {
        SummaryNode* auxSummL = treeDeque.front(); treeDeque.pop_front(); // sacar por frontal y borrar
        SummaryNode* auxSummR = treeDeque.front(); treeDeque.pop_front(); // sacar por frontal y borrar
        SummaryNode* newParent = new SummaryNode(auxSummL, auxSummR); 
        treeDeque.push_back(newParent);
    }

    // generamos el nuevo ultima raíz;
    SummaryNode* newRoot = new SummaryNode(summaryRoot, treeDeque.front());
    treeDeque.pop_front();
    
    return newRoot;
}

void ListArr::updateSummaryNodes() {
    // if (currentSumm->summL == nullptr || currentSumm->summR == nullptr) {
    //     currentSumm->usedCapacity = currentSumm->dataL->usedCapacity + currentSumm->dataR->usedCapacity;
    //     return;
    // }
    // updateSummaryNodes(currentSumm->summL);    
    // updateSummaryNodes(currentSumm->summR);
    // currentSumm->usedCapacity = currentSumm->summL->usedCapacity + currentSumm->summR->usedCapacity;

    // * Utilizamos el algoritmo del enunciado para actualizar la cantidad de datos en árbol de summaryNodes
    int index = summaryRoot->usedCapacity;
    SummaryNode* currentSumm = summaryRoot;
    while (currentSumm->summL != nullptr) {
        currentSumm->usedCapacity++; // Actualizar cantidad de datos en summaryNode actual

        SummaryNode* left = currentSumm->summL;
        if ((index <= left->usedCapacity && index != left->maxCapacity) || index < dataMaxCapacity) {
            currentSumm = left;
        } else {
            index -= left->usedCapacity;
            currentSumm = currentSumm->summR;
        }
    }
    currentSumm->usedCapacity++; // Actualizar cantidad de datos en summaryNode hoja
}

void ListArr::printSummariesNodes() {
    typedef std::function<void(SummaryNode*, std::vector<SummaryNode*>&)> Function;
    Function preOrder = [&](SummaryNode* currSumm, std::vector<SummaryNode*>& vecSummNodes) {
        if (currSumm == nullptr) return;
        vecSummNodes.push_back(currSumm); // agrega el padre luego los hijos        
        preOrder(currSumm->summL, vecSummNodes);
        preOrder(currSumm->summR, vecSummNodes);
    };
    
    std::vector<SummaryNode *> vecSumms;
    preOrder(summaryRoot, vecSumms);

    cout << "Summaries: ";
    for (auto summ : vecSumms)  {
        cout << "[" << summ->usedCapacity << "," << summ->maxCapacity << "]";
    }
    cout << "\n";
}
