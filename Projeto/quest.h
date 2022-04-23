#pragma once

#include "node.h"
#include "card.h"
#include <string>
using namespace std;


//Classe Quest agrupa uma sequencia de tarefa que representam uma missão no jogo, ela completa tarefa e avança pela missao
class Quest{
    public:
        Quest(bool* firstTask, string title, string* estados){
            Card<bool*> new_card(firstTask, 1);
            Node<Card<bool*>>* new_node = new Node<Card<bool*>>(new_card);
            
            this->starter = new_node;
            this->current = nullptr;
            this->title = title;
            this->estados = estados;
        }

        ~Quest() {
            while (this->starter != nullptr) {
                //variavel auxiliar
                Node<Card<bool*>>* aux = this->starter;

                if (aux->getNext() == nullptr) {

                    this->starter = nullptr;
                    delete(aux);
                }
                else {
                    while (aux->getNext()->getNext() != nullptr)
                        aux = aux->getNext();

                    aux->setNext(aux->getNext()->getNext());
                    delete(aux->getNext());
                }

                
            }
        }

        /*  append: adiciona uma tarefa ao fim da sequencia
            entradas: ponteiro de Task
            saida: nada
        */
        void append(bool* nextTask){
            //Variavel auxiliar
            Node<Card<bool*>>* aux = this->starter;
            

            //varrendo
            while(aux->getNext()!=nullptr)
                aux = aux->getNext();
            
            //Adicionando ao final
            Card<bool*> new_card(nextTask, aux->getInfo().getIndex() + 1);
            Node<Card<bool*>>* new_node = new Node<Card<bool*>>(new_card);
            aux->setNext(new_node);
        }


        /*  resetQuest: faz com que a sequencia de tarefas volte para o estado inicial
            entradas: nada
            saida: nada
        */
        void resetQuest(){
            if (this->current != nullptr)
                *this->current->getInfo().getInfo() = false;
            this->current = this->starter;
            *this->current->getInfo().getInfo() = true;
        }

        /*  nextStep: completa a tarefa atual e avança a missao
            entradas: nada
            saida: nada
        */
        void advance(){
            //Completa a tarefa atual
            *this->current->getInfo().getInfo() = false;

            //Atualiza tarefa atual
            this->current = this->current->getNext();

            if (this->current != nullptr)
                *this->current->getInfo().getInfo() = true;
        }

        bool* getCurrentTask(){
                return this->current == nullptr ? nullptr : this->current->getInfo().getInfo();
        }

        string getTitle() {
            return title;
        }

        string getState() {
            if (this->current == nullptr)
                return estados[0];
            return estados[this->current->getInfo().getIndex()];
        }

        bool isFinished() {
            return this->current == nullptr;
        }

    private:
        Node<Card<bool*>>* starter;
        Node<Card<bool*>>* current;
        string title;
        string* estados;
};