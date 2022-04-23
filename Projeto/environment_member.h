#pragma once
//AmbientMember é uma superclasse para os objetos Linker e Target, contem posicao e tamanho.

class EnvironmentMember {
public:
    EnvironmentMember(int position, int size, int index) {
        this->setPosition(position);
        this->setSize(size);
        this->setIndex(index);
    }

    //getters
    int getPosition() {
        return this->position;
    }

    int getSize() {
        return this->size;
    }

    int getIndex() {
        return this->indexVector;
    }

    //setters
    void setPosition(int position) {
        this->position = position >= -100 ? position : -100;
    }

    void setSize(int size) {
        this->size = size > 0 ? size : 0;
    }

    void setIndex(int index) {
        this->indexVector = index > 0 ? index : 0;
    }

    bool operator<(EnvironmentMember& member) {
        return this->getPosition() + this->getSize() < member.getPosition();
    }
    bool operator>(EnvironmentMember& member) {
        return this->getPosition() > member.getPosition() + member.getSize();
    }

    bool operator!=(EnvironmentMember& member) {
        return (*this < member || *this > member);
    }
    bool operator==(EnvironmentMember& member) {
        return !(*this < member || *this > member);
    }
    bool operator<=(EnvironmentMember& member) {
        return !(*this > member);
    }
    bool operator>=(EnvironmentMember& member) {
        return !(*this < member);
    }


    //operadores Linker/int
    bool operator<(int position) {
        return this->getPosition() + this->getSize() < position;
    }
    bool operator>(int position) {
        return this->getPosition() > position;
    }

    bool operator!=(int position) {
        return (*this > position || *this < position);
    }
    bool operator==(int position) {
        return !(*this > position || *this < position);
    }
    bool operator<=(int position) {
        return !(*this == position);
    }
    bool operator>=(int position) {
        return !(*this < position);
    }

private:
    //atributes
    int position;
    int size;
    int indexVector;    //para relacionar o AmbientMember de uma Árvore com um Vetor      
};