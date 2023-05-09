#include "..\include\ListArr.hpp"

#include <iostream>

#include <stack> // borrar si es que se usa deque
#include <vector>
#include <deque>
#include <functional>

#include <iostream>

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
    std::cout << "Inserting " << v << " at index " << index << ".\n";

    // Comprobar si el indice es valido
    if (index < 0 || index > size()) {
        cout << "Error: Index out of bounds" << ".\n";
        return;
    }

    // Comprobar si se necesita expandir la capacidad de ListArr
    if (size() == summaryRoot->maxCapacity) {
        this->resize();
        // ! EXPERIMENTAL
        /* this->resize();
        this->resize();
        this->resize(); // de aca en adelante se empieza a usar el while de padre de padres
        this->resize();
        this->resize(); */
        // ! EXPERIMENTAL
    }

    //* Algoritmo del enunciado para encontrar datos en cierto index
    // Recorrer árbol de summaryNodes hasta llegar a un nodo hoja
    SummaryNode* currentSumm = summaryRoot;
    while (currentSumm->summLeft != nullptr) {
        if (index < currentSumm->summLeft->usedCapacity) {
            currentSumm = currentSumm->summLeft;
        } else {
            index -= currentSumm->summLeft->usedCapacity;
            currentSumm = currentSumm->summRight;
        }
    }

    // Comprobar en que dataNode del summaryNode actual se insertara el valor
    DataNode* currentData;
    if (index <= currentSumm->dataLeft->usedCapacity) {
        currentData = currentSumm->dataLeft;
    } else {
        index -= currentSumm->dataLeft->usedCapacity;
        currentData = currentSumm->dataRight;
    }

    // std::cout << "* usedCapacity1: " << currentData->usedCapacity << "\n";
    // std::cout << "* size1: " << size() << "\n";

    // Desplazar los datos de ListArr consecuentes a la posición en que se insertara el valor
    if (currentData->usedCapacity != 0) shiftDataToRight(currentData, index);

    // Insertar el nuevo valor en el dataNode correspondiente
    currentData->array[index] = v;
    currentData->usedCapacity++;

    // Actualizar la cantidad de datos en árbol de summaryNodes
    if (summaryRoot->summLeft == nullptr) {
        summaryRoot->usedCapacity++;
    } else {
        updateSummaryNodes(summaryRoot);
    }

    // std::cout << "* usedCapacity2: " << currentData->usedCapacity << "\n";
    // std::cout << "* size2: " << size() << "\n";
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

// * Función para imprimir ListArr
void ListArr::print() {
    cout << "ListArr: ";

    DataNode* currentData = dataHead;
    while (currentData != nullptr) {
        cout << "[";
        for (int i = 0; i < currentData->maxCapacity; i++) {
            cout << currentData->array[i];
            if (i < currentData->maxCapacity-1) {
                cout << ", ";
            }
        }
        cout << "]";
        currentData = currentData->next;
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
void ListArr::resize() {
    std::vector<SummaryNode*> vecSummaryNodes; /**< Un vector que contiene todos los SummaryNode en la estructura */

    // Agregar los nuevos nodos de datos
    for (int i = 0; i < dataNodes_count; i++) {
        DataNode* newDataNode = new DataNode(dataMaxCapacity);
        newDataNode->previous = dataTail;
        dataTail->next = newDataNode;
        dataTail = newDataNode;

        // Crear summaryNodes para cada par de dataNodes (primera linea de summaryNodes)
        if ((i + 1) % 2 == 0) {
            SummaryNode* newSummaryNode = new SummaryNode(newDataNode->previous, newDataNode);
            vecSummaryNodes.push_back(newSummaryNode);
        }
    }
    dataNodes_count *= 2; // Actualizar la cantidad de DataNodes (se duplica)

    // ! EXPERIMENTAL // imprime el vector de nodos summary que le vamos a pasar a build
    for (auto i : vecSummaryNodes) std::cout << i << " " ;
    std::cout << "\n";
    // ! EXPERIMENTAL
    
    summaryRoot = buildTree(vecSummaryNodes);

    vecSummaryNodes.clear(); // Vaciar el vector de summaryNodes

    // ! EXPERIMENTAL
    printSummaries(); 
    print();
    // ! EXPERIMENTAL
}

// ! TA MALOOOOOOOOOOOOOOOOOOOOOOOOOO // comentario de joaquin: creo que ya no :3
// * Función que genera una nueva SummaryNode raiz a partir de SummaryNodes base
SummaryNode* ListArr::buildTree(std::vector<SummaryNode*> &vecSummaryNodes) {
    // std::stack<SummaryNode*> treeStack;
    std::deque<SummaryNode*> treeDeque;

    // En caso de que sea el primer duplicado solo se genera la nueva raiz a partir de la `summaryRoot` y el unico nuevo nodo vecino
    if (vecSummaryNodes.size() == 1)  {
        SummaryNode* newRoot = new SummaryNode(summaryRoot, vecSummaryNodes[0]);
        return newRoot;
    }
    
    // generamos los nodos padre de los últimos nodos generados
    for (int i = 0; i < vecSummaryNodes.size() - 1; i += 2) { 
        SummaryNode* auxSummNode = new SummaryNode(vecSummaryNodes[i], vecSummaryNodes[i+1]);
        treeDeque.push_back(auxSummNode);
        // treeStack.push(auxSummNode); // Ingrear por posterior
    }

        // ! EXPERIMENTAL
        std::cout << "treeDeque:" << " ";
        for (int i = 0; i < treeDeque.size(); i++) {
        std::cout << treeDeque.at(i) << " ";
        }
        cout << "\n";
        // ! EXPERIMENTAL

    // de la primera generación de padres generamos padres hasta que lleguemos al mismo nivel que la raíz
    // while (treeStack.size() != 1) {
    while (treeDeque.size() != 1) {
        // SummaryNode* auxSummL = treeStack.top(); treeStack.pop(); // sacar por frontal y borrar
        SummaryNode* auxSummL = treeDeque.front(); treeDeque.pop_front(); // sacar por frontal y borrar
        // SummaryNode* auxSummR = treeStack.top(); treeStack.pop(); 
        SummaryNode* auxSummR = treeDeque.front(); treeDeque.pop_front(); // sacar por frontal y borrar
        SummaryNode* newParent = new SummaryNode(auxSummL, auxSummR); 
        // treeStack.push(newParent); // Ingresar por posterior
        treeDeque.push_back(newParent);
        
        // ! EXPERIMENTAL
        std::cout << "Hola owo\n";
        for (int i = 0; i < treeDeque.size(); i++) {
        std::cout << treeDeque.at(i) << " ";
        }
        // ! EXPERIMENTAL
    }
    // treeStack.push(summaryRoot); // agrega la raíz para asi no calcular nuevamente los nodos summary

    // generamos el nuevo ultima raíz
    // SummaryNode* newRoot = new SummaryNode(summaryRoot, treeStack.top());
    SummaryNode* newRoot = new SummaryNode(summaryRoot, treeDeque.front());
    // treeStack.pop();
    treeDeque.pop_front();
    
    return newRoot;
}

void ListArr::updateSummaryNodes(SummaryNode* currentSumm) {
    if (currentSumm->summLeft == nullptr || currentSumm->summRight == nullptr) {
        currentSumm->usedCapacity = currentSumm->summLeft->usedCapacity + currentSumm->summRight->usedCapacity;
        return;
    }
    
    updateSummaryNodes(currentSumm->summLeft);
    updateSummaryNodes(currentSumm->summRight);

    currentSumm->usedCapacity = currentSumm->summLeft->usedCapacity + currentSumm->summRight->usedCapacity;
}

// ! EXPERIMENTAL
void ListArr::printSummaries() {
    typedef std::function<void(SummaryNode*, std::vector<SummaryNode*>&)> Function;
    Function preOrder = [&](SummaryNode* currSumm, std::vector<SummaryNode*>& vecSummNodes) {
        if (currSumm == nullptr) return;

        vecSummNodes.push_back(currSumm); // agrega el padre luego los hijos        

        preOrder(currSumm->summLeft, vecSummNodes);
        preOrder(currSumm->summRight, vecSummNodes);
    };
    
    std::vector<SummaryNode *> vecSumms;
    preOrder(summaryRoot, vecSumms);

    std::cout << "Summaries en preorder: ";
    for (auto summ : vecSumms)  {
        cout << "[" << summ->usedCapacity << ", " << summ->maxCapacity << "]";
    }
    std::cout << "\n";
}
// ! EXPERIMENTAL
