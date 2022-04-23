#pragma once

#include "environment.h"
#include <SFML/System/Vector2.hpp>
using namespace sf;

//Classe que emcapsula os dados do player para sua manipulacao no jogo

class Player {
public:

	//construtor
	Player() {

		//inicia variaveis associadas ao player
		this->facing = true;
		this->position = Vector2f(0, 0);
		this->imageDirectory = " ";

		//logica movimento e animacao
		this->moveSpeed = 10.f;
		this->delta = 0.0f;
	}

	Player(string image, Vector2f position, Environment* ambiente) {

		//inicia variaveis associadas ao player
		this->facing = true;
		this->position = position;
		this->imageDirectory = image;
		this->ambiente = ambiente;

		//logica movimento e animacao
		this->moveSpeed = 10.f;
		this->delta = 0.f;

	}

	//destrutor
	~Player() {

	}

	//getters
	bool getFacing() {
		return this->facing;
	}

	string getImage() {
		return this->imageDirectory;
	}

	Vector2f getPosition() {
		return this->position;
	}

	float getDelta() {
		return this->delta;
	}

	float getMoveSpeed() {
		return this->moveSpeed;
	}

	Environment* getAmbiente() {
		return this->ambiente;
	}

	//setters
	void setFacing(bool facing) {
		this->facing = facing;
	}

	void setDelta(float delta) {
		this->delta = delta;
	}

	void setPosition(Vector2f position) {
		this->position = position;
	}


	//metodos
	/*  attAmbiente: atualiza o ambiente do player caso ele esteja sobre um linker
		entradas: nada
		saida: nada
	*/
	bool attAmbiente() {
		bool atualizou;

		//Troca posicao do player entre os ambientes
		int pos = (int)this->position.x;
		atualizou = ambiente->attPlayerAmbient(&pos, &this->ambiente);
		this->setPosition(sf::Vector2f((float)pos, this->getPosition().y));

		return atualizou;
	}

	/*  attAmbiente: interage o o otarget que o player esta em cima
		entradas: nada
		saida: Ponteiro do Target que o player interagiu
	*/
	Target* testTarget() {
		Target* targetHovered;

		if (this->ambiente->verifyPlayerOverTarget((int)this->position.x, &targetHovered) && targetHovered->isActive()) {
			return targetHovered;
		}

		return nullptr;
	}

private:

	//atributos de imagem e objeto
	string imageDirectory;
	Vector2f position;
	bool facing;
	Environment* ambiente;

	//movement / general logic
	float delta;
	float moveSpeed;

};
