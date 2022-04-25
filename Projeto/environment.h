#pragma once

//Ambient encapsula os dados e metodos que compoem um ambiente no jogo 

#include "card.h" 
#include "target.h"
#include "linker.h"
#include "bi_tree.h"
#include "array.h"


class Environment {
public:
    //construtores
    Environment(string imageD) {
        this->imageDirectory = imageD;
        this->nOfLinkers = 0;
    }

    ~Environment() {

    }

    //getters
    string getImageDirectory() {
        return this->imageDirectory;
    }

    BinaryTree<Linker>& getLinkers() {
        return this->borders;
    }

    BinaryTree<Target>& getTargets() {
        return this->targets;
    }

    //setters

    /*  addBorder: adiciona uma borda para mudança de ambiente, Linker
        entradas: Um objeto Linker e o ponteiro do ambiente que aquele linker levará
        saida: true se adicionado com sucesso, falso, caso contrario
    */
    bool addBorder(Linker border, Environment* ambientPtr) {
        
        //caso ja esteja
        if (this->borders.isInTree(border))
            return false;

        Card<Environment*> newPointer(ambientPtr, this->nOfLinkers);

        //adiciona o ponteiro ao fim do array
        this->pointers.insere(newPointer);

        //adiciona o linker na arvore
        border.setIndex(this->nOfLinkers++);
        this->borders.insere(border);

        return true;
    }

    /*  addTarget: adiciona um objeto de interação no ambiente(Target)
        entradas: Um objeto Target
        saida: true se adicionado com sucesso, falso, caso contrario
    */
    bool addTarget(Target target) {
        return this->targets.insere(target);
    }



    //methods

    /*  attPlayerAmbient: Atualiza o ambiente do player e sua posicao caso a posicao do player esteja sobre algum linker
        entradas: ponteiro de inteiro que guarda a posiçao do player, ponteiro de ponteiro de Ambient que guarda endereco que aponta para o ambiente do player
        saida: true se atualizado com sucesso, falso, caso contrario
    */
    bool attPlayerAmbient(int* playerPosition, Environment** playerAmbient) {
        //pega o Linker em que o player esta em cima
        Linker* linkerHovered = this->borders.getByIndex(*playerPosition);

        if (linkerHovered != nullptr) {
            //atualiza ponteiros
            *playerAmbient = this->pointers.getByIndex(linkerHovered->getIndex())->getInfo();
            *playerPosition = linkerHovered->getNewPlayerPosition();
            
            return true;
        }

        return false;
    }

    /*  verifyPlayerOverTarget: Verifica se a posicao do player esta sobre algum target, caso sim faz com que targetHovered aponte para ele
        entradas: inteiro com a posicao do player, ponteiro de ponteiro de Target que recebera o endereço do ponteiro de Target
        saida: true se atualizado com sucesso, falso, caso contrario
    */
    bool verifyPlayerOverTarget(int playerPosition, Target** targetHovered) {
        //pega o Target em que o player esta em cima
        *targetHovered = this->targets.getByIndex(playerPosition);
        return (*targetHovered != nullptr);
    }


private:
    //atributes
    string imageDirectory;          //string com o diretorio da imagem do ambiente
    BinaryTree<Linker> borders;     //Arvore binaria que ira guardar os Linkers do ambiente
    BinaryTree<Target> targets;     //Arvore binaria que ira guardar os Targets do ambiente
    BinaryTree<Card<Environment*>> pointers;      //Array de ponteiros de ambiente relacionado aos Linkers
    int nOfLinkers;
};
