#pragma once

#include "node.h"
#include <iostream>

template <typename T>
class Array {
public:
    Array() {
        this->begin = nullptr;
        this->size = 0;
    }

    Array(Array& array){
        array = *this;
    }

    ~Array() {
        this->clean();
    }

    //methods

    /*  append: Adiciona um elemento ao fim do vetor
        entrada: Elemento a ser adicionado
        saida: retorna o novo tamanho do vetor
    */
    int append(T new_info) {
        //caso vazio
        if (this->begin == nullptr) {
            Node<T>* new_node = new Node<T>(new_info, nullptr);
            this->begin = new_node;
        }
        else {
            //variavel auxiliar
            Node<T>* aux = this->begin;

            while (aux->getNext() != nullptr)
                aux = aux->getNext();

            //novo no
            Node<T>* new_node = new Node<T>(new_info, nullptr);
            aux->setNext(new_node);
        }

        return ++this->size;
    }

    /*  pop: Remove um elemento ao fim do vetor
        entrada: nada
        saida: retorna o novo tamanho do vetor
    */
    int pop() {
        //caso vazio
        if (this->begin == nullptr)
            return this->size;

        //variavel auxiliar
        Node<T>* aux = this->begin;

        if (aux->getNext() == nullptr) {

            this->begin = nullptr;
            delete(aux);
            return --this->size;
        }

        while (aux->getNext()->getNext() != nullptr)
            aux = aux->getNext();

        aux->setNext(aux->getNext()->getNext());
        delete(aux->getNext());
        return --this->size;
    }

    /*  remove: Remove o elemento na posição do index
        entrada: inteiro que contem o index
        saida: retorna o novo tamanho do vetor
    */
    int remove(int index){
        //verifica se o index existe
        if (index < 0 || index >= this->size)
            return this->size;

        //variavel auxiliar
        Node<T>* aux = this->begin;

        if(index == 0){
            this->begin = aux->getNext();
        }else{
            for (int i = 0; i < index-1; i++) 
                aux = aux->getNext();

            Node<T>* old_node = aux->getNext();
            aux->setNext(aux->getNext()->getNext());
            aux = old_node;
        }

        delete(aux);
        return --this->size;
    }

    /*  clean: Tira todos os elementos do vetor(desaloca memoria)
        entrada: nada
        saida: nada
    */
    void clean() {
        while (this->pop() > 0);
    }

    int getSize() {
        return this->size;
    }

    T& operator[](int index) {
        try{
            if (index < 0 || index >= this->size)
                throw(index);

            //variavel auxiliar
            Node<T>* aux = this->begin;

            for (int i = 0; i < index; i++) {
                aux = aux->getNext();
            }

            return aux->getInfo();
        }catch(...){
            std::cout << "Index out of range";
        }
    }
    
    void operator=(Array& array){
        //limpando
        this->clean();

        //variavel auxiliar
        Node<T>* aux = array.begin;

        //copiando os valores
        for(int i = 0; i < array.size; i++, aux = aux->getNext())
            this->append(aux->getInfo());
    }

private:
    Node<T>* begin;
    int size;

};