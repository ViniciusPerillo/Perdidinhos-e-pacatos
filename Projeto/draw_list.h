#pragma once

#include "array.h"
#include "card.h"
#include <cstdlib>
#include <ctime>
using namespace std;



template <typename T>
class DrawList{
    public:
        explicit DrawList(bool removeDrawn){
            this->modifying = true;
            this->removeDrawn = removeDrawn;
            this->virtualSize = 0;
            srand(time(nullptr));
        }

        
        /*  append: Adiciona um elemento ao fim do vetor
            entrada: Elemento a ser adicionado
            saida: retorna o novo tamanho do vetor
        */
        int append(T new_info){
            Card<T> new_card(new_info, this->data.getSize());
            prepareToModify();

            this->virtualSize = this->data.append(new_card);
            return this->virtualSize;
        }

        /*  pop: Remove um elemento ao fim do vetor
            entrada: nada
            saida: retorna o novo tamanho do vetor
        */
        int pop(){
            prepareToModify();
            
            this->virtualSize = this->data.pop();
            return this->virtualSize;
        }


        /*  remove: Remove o elemento na posição do index
        entrada: inteiro que contem o index
        saida: retorna o novo tamanho do vetor
        */
        int remove(int index){
            prepareToModify();
            
            this->virtualSize = this->data.remove(index);
            return this->virtualSize;
        }

        //Volta a pilha para a organização original
        void reset(){
            if (this->removeDrawn) {
                //declaração das variáveis locais
                Card<T> aux;
                int passadas = this->data.getSize();
                bool isSorted;

                //sort
                do {
                    isSorted = false;
                    for (int i = 1; i < passadas; i++) {
                        if (this->data[i - 1] >this->data[i]) {
                            isSorted = true;
                            troca(this->data[i - 1], this->data[i]);
                        }

                    }
                    passadas--;
                } while (isSorted);
            }

        }

        //Compra um item da pilha
        bool draw(T* drawn){
            //Caso vazio
            if(!(bool)this->data.getSize())
                return false;
            //Caso todas compradas 
            if (!(bool)this->virtualSize)
                this->reset();
            
            this->modifying = false;

            //sorteio
            int index = rand() % this->virtualSize;

            *drawn = this->data[index].getInfo();

            if(this->removeDrawn){
                troca(this->data[index], this->data[--this->virtualSize]);
            }

            return true;
        }

    private:
        Array<Card<T>> data;
        bool modifying;
        bool removeDrawn;
        int virtualSize;

        void prepareToModify(){
            if(!modifying){
                this->modifying = true;
                this->reset();
            }
        }

        void troca(Card<T>& a, Card<T>& b) {
            Card<T> aux;
            aux = a;
            a = b;
            b = aux;
        }
};