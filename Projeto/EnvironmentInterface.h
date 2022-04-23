
#pragma once

#include "header.h"
#include "ObjectInterface.h"
#include "array.h"
#include "environment.h"
#include <iostream>


class EnvironmentInterface {
public:
	//construtor / destrutor
	EnvironmentInterface(Environment *ambientePtr, float width, float height) {


		this->background = new ObjectInterface(ambientePtr->getImageDirectory(), width, height);
		
		Target* target;

		while (!(ambientePtr->getTargets().getAll(&target))) {
			int index = elementos.append(new ObjectInterface(target->getImageDirectory(), (float)target->getSize() + 1, height, (float)target->getPosition(), 0.0f, 2, 1));
 			target->setIndex(index - 1);
			if (target->isActive())
				this->elementos[index - 1]->update((int)target->isActive());
		}
			

	};

	~EnvironmentInterface() {
		delete this->background;
		for (int i = 0; i < this->elementos.getSize(); i++)
			delete elementos[i];
		elementos.clean();
	};


	void render(RenderTarget& target) {
		background->render(target);

		for (int i = 0; i < this->elementos.getSize(); i++)
			elementos[i]->render(target);

	}

private:
	
	ObjectInterface* background;
	Array<ObjectInterface*> elementos;
	

};
