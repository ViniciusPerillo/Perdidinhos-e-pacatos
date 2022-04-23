#pragma once

#include "Header.h"
#include "ObjectInterface.h"

//produz um menu, um tipo especial de objeto de interface
class Menu : public ObjectInterface {
public:
	//construtor
	Menu(string image, float width, float heigth, int sheetX = 1, int sheetY = 1) :ObjectInterface(image, width, heigth, 0.0f, 0.0f, sheetX, sheetY) {
		this->ativo = true;
	}
	//destrutor
	void setAtivo(bool ativo) {
		this->ativo = ativo;
	}
	//getters
	bool getAtivo() {
		return this->ativo;
	}

private:
	bool ativo;
};