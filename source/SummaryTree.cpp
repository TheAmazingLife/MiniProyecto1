#include "..\include\SummaryTree.hpp"
#include "..\include\SummaryNode.hpp"

#include <vector>

// Arma un árbol apartir de un vector de summary nodes ordenados
SummaryNode* SummaryTree::buildTree() {
    int n = this->leaves.size();
    
    // crear un vector de punteros a SummaryNode y llenarlo de NULL
    std::vector<SummaryNode*> tree(n+1, nullptr);

    // crear los nodos finales y asignarlos a los índices correspondientes
    for (int i = 0; i < n; i++) {
        tree[i+1] = this->leaves[i];
    }

    // agregar los hijos de cada nodo
    for (int i = 1; i <= n/2; i++) {
        if (tree[i] != nullptr) {
            tree[i]->SummNodeL = tree[2*i];
            tree[i]->SummNodeR = tree[2*i+1];
        }
    }

    return tree[1]; // devolver la raíz del árbol
}

void SummaryTree::insert(DataNode* data) {
    leaves.push_back(new SummaryNode(data, nullptr));
}
