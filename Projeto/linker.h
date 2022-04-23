#pragma once

/*
 * Header da classe Linker
*/

#include "environment_member.h"

//Classe Linker conecta um ambiente a outro, eles sao uma regiao do ambiente que serve para ir para outro ambiente 

class Linker : public EnvironmentMember {
public:
    //constructor
    Linker(int position = 0, int size = 0, int PlayerPosition = 0, int index = 0) :
        EnvironmentMember(position, size, index) {
        this->newPlayerPosition = PlayerPosition;
    }

    Linker(Linker& linker) :EnvironmentMember(linker.getPosition(), linker.getSize(), linker.getIndex()) {
        *this = linker;
    }

    //getters
    /*int getAmbientPointerIndex() {
        return this->ambientPointerIndex;
    }*/

    int getNewPlayerPosition() {
        return this->newPlayerPosition;
    }

    //methods

    //Esses operadores sao fundamentais para o funcionamento da arvore binaria

    //operators Linker/Linker
    void operator=(Linker& linker) {
        this->setPosition(linker.getPosition());
        this->setSize(linker.getSize());
        this->setIndex(linker.getIndex());
        this->newPlayerPosition = linker.newPlayerPosition;
    }

    

private:
    //atributes
    int newPlayerPosition;
};
