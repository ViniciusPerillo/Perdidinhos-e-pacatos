#pragma once

//Classe Node representa o no de uma estrutura de dados encadeada

template <typename T>
class Node {
public:
    Node(T info, Node* next = nullptr) {
        this->setInfo(info);
        this->setNext(next);
    }

    //metodos
    T& getInfo(){
        return this->info;
    }

    Node<T>* getNext() const {
        return this->next;
    }

    void setInfo(T info) {
        this->info = info;
    }

    void setNext(Node<T>* next) {
        this->next = next;
    }

private:
    //atributos
    T info;
    Node<T>* next;
};