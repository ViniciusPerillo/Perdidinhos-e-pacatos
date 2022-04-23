#pragma once


#include "environment_member.h"
#include <string>
using namespace std;

//Classe Target encapsula os dados de um objeto que podera ser interagido para completar Tasks 

class Target : public EnvironmentMember {
public:
    //constructors
    Target(int position = 0, int size = 0, string imageD = "", bool* task = nullptr, int index = 0)
        :EnvironmentMember(position, size, index)
    {
        this->imageDiretory = imageD;
        this->task = task;
    }

    Target(Target& target):EnvironmentMember(target.getPosition(), target.getSize(), target.getIndex()) {
        *this = target;
    }

    //getters
    bool isActive() {
        return *this->task;
    }

    string getImageDirectory() {
        return this->imageDiretory;
    }

    bool* getTask() {
        return this->task;
    }


    //setters

    string setImageDirectory() {
        return this->imageDiretory;
    }

    void setTask(bool* task) {
        this->task = task;
    }

    //Esses operadores sao fundamentais para o funcionamento da arvore binaria

    //operadores Target/Target
    void operator=(Target& target) {
        this->setPosition(target.getPosition());
        this->setSize(target.getSize());
        this->imageDiretory = target.getImageDirectory();
        this->task = target.getTask();
    }

private:
    //atributes
    string imageDiretory;
    bool* task;
};