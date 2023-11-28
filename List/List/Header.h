#ifndef _HEADER_H
#define _HEADER_H

class Node
{
public:
    int key;        // поле данных
    Node* pNext;// указатель на следующий узел:
};

//0123
//Node* pFirst = new Node;
//pFirst->key = 1;
//pFirst->pNext = new Node;
//pFirst->pNext->key = 2;
//pFirst->pNext->pNext = new Node;
//pFirst->pNext->pNext->key = 3;
//pFirst->pNext->pNext->pNext = nullptr;

Node* newNode(int key, Node* next)
{
    // выделяем новый узел в куче и устанавливаем его данные
    Node* node = new Node;
    node->key = key;

    // устанавливаем указатель `.next` нового узла так, чтобы он указывал на текущий
    // первый узел списка.
    node->pNext = next;

    return node;
}

Node* Search(Node* pFirst, int Key) {
    Node* tmp = pFirst;
    while ((tmp != nullptr) && (tmp->key != Key)) {
        tmp = tmp->pNext;//сдвигаемся пока не найдем нужный элемент
    }
    return tmp;
}

Node* Push(Node* pFirst, int Key) {
    Node* pNode = new Node;
    pNode->key = Key;
    pNode->pNext = pFirst;
    pFirst = pNode;//вставляем в начало
}

void InsertEnd(Node* pFirst, int Key) {
    Node* tmp = pFirst;
    if (pFirst == 0) {
        Push(pFirst, Key);
    }
    while (tmp->pNext != nullptr) {
        tmp = tmp->pNext;
    }
    tmp->pNext = new Node;
    tmp->pNext->key = Key;
    tmp->pNext->pNext = nullptr;
}

void InsertAfter(Node* pFirst,int prewKey, int Key) {
    if (pFirst == 0) {
        throw("exp");
    }
    Node* pPrew = Search(pFirst, prewKey);
    if(pPrew==0) throw("exp");
    Node* pNode = new Node;
    pNode->key = Key;
    pNode->pNext =pPrew->pNext;
    pPrew->pNext = pNode;
}

void InsertBefore(Node* pFirst, int nextKey, int Key) {
    if (pFirst == 0) {
        throw("exp");
    }
    Node* pPrew = nullptr;
    Node* node = pFirst;
    while (node->pNext != nullptr && node->key != nextKey) {
        pPrew = node;
        node = node->pNext;
    }
    if (node->pNext != nullptr && node->key != nextKey)
    {
        throw("exp");
    }
    Node* pNode = new Node;
    pNode->key = Key;
    pNode->pNext = node;

    if (pPrew == 0) {
        pFirst = pNode;
        return;
    }
    pPrew->pNext = pNode;
}

void Delete(Node*& pFirst, int Key)
{
    if (pFirst == 0) {
        throw("exp");
    }
    Node* pPrew = nullptr;
    Node* pNode = pFirst;
    while (pNode->pNext != nullptr && pNode->key != Key) {
        pPrew = pNode;
        pNode = pNode->pNext;
    }
    if (pNode->pNext != nullptr && pNode->key != Key) throw("exp");
    if (pPrew == nullptr) {
        pFirst = pNode->pNext;
        delete pNode;
        return;
    }
    pPrew->pNext = pNode->pNext;
    delete pNode;
    }

int count(Node* pFirst) {
    Node* pNode = pFirst;
    int k = 0;
    while (pNode != nullptr) {
        pNode = pNode->pNext;
        k++;
    }
    return k;
}

Node* min(Node* pFirst) {
    Node* pNode = pFirst;
    Node* pmin = pFirst;
    while (pNode != nullptr) {
        if (pmin->key > pNode->key)
        {
            pmin = pNode;
        }
        pNode = pNode->pNext;

    }

    return pmin;
}

void swapFL(Node*& pFirst) {
    if (pFirst == 0 || pFirst->pNext==0) {
        return;
    }

    if (pFirst->pNext->pNext == 0)
    {
        Node* plast = pFirst->pNext;
        pFirst->pNext->pNext == pFirst;
        pFirst = plast;
        return;

    }
    Node* pPrew = nullptr;
    Node* plast = pFirst;
    while (plast->pNext != nullptr) {
        pPrew = plast;
        plast = plast->pNext;
    }
    plast->pNext = pFirst->pNext;
    pPrew->pNext = pFirst;
    pFirst->pNext = nullptr;
    pFirst = plast;
}

void Remove(Node*& pFirst) {

    Node* pNode = pFirst;
    while (pNode != nullptr) {
        pNode = pNode->pNext;
        delete pFirst;
        pFirst = pNode;
    }

}


#endif