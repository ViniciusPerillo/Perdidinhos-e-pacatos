#pragma once

//Ambient encapsula os dados e metodos que compoem um ambiente no jogo 


#include "target.h"
#include "linker.h"
#include "bi_tree.h"
#include "array.h"

class Environment {
public:
    //construtores
    Environment(string imageD) {
        this->imageDirectory = imageD;
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
        Linker new_linker = border;
        
        //caso ja esteja
        if (this->borders.isInTree(new_linker))
            return false;

        //adiciona o ponteiro ao fim do array
        int index = this->pointers.append(ambientPtr) - 1;

        //adiciona o linker na arvore
        new_linker.setIndex(index);
        this->borders.insere(new_linker);

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
            *playerAmbient = this->pointers[linkerHovered->getIndex()];
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
    Array<Environment*> pointers;       //Array de ponteiros de ambiente relacionado aos Linkers
};
