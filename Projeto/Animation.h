
#pragma once
#include "Header.h"

//faz animacao de uma imagem sheet de frames

class Animation {
public:
	//construtor recebe imagem, vetor com a quantia de sprites da imagem, e o tempo de mudança da sprite
	Animation(Texture* texture, Vector2u counter, float tSwitch) {

		this->counter = counter;
		this->tSwitch = tSwitch;
		this->tTotal = 0.0f;
		this->atual.x = 0;

		this->retangulo.width = texture->getSize().x / counter.x;
		this->retangulo.height = texture->getSize().y / counter.y;


		//recalcula os retangulos
		retangulo.left = 0 * retangulo.width;
		retangulo.top = 0 * retangulo.height;
	}
	//destrutor
	~Animation() {
	}

	//update especial do player, muda a direcao de acordo com a camada
	//delta tem funcao de aumentar a fluidez
	void update(int camada, float delta) {

		//muda a camada 
		atual.y = camada;
		//ajuda a animacao a ficar mais smooth
		tTotal += delta;

		if (tTotal >= tSwitch) {

			tTotal -= tSwitch;
			//muda a imagem atual
			atual.x++;

			//reinicia a animacao
			if (atual.x >= counter.x) {
				atual.x = 0;
			}

		}

		//recalcula os retangulos
		retangulo.left = atual.x * retangulo.width;
		retangulo.top = atual.y * retangulo.height;
	}

	//updater especial para objetos de task, 
	//recebe a situacao e alterna entre objeto sujo ou limpo
	void staticUpdate(int situacao) {

		//muda a camada 
		atual.y = 0;

		switch (situacao) {

			//frame desarrumado
		case 1:
			atual.x = 1;
			break;
			//frame de hover

		case 2:
			atual.x = 2;
			break;

			//frame default (arrumado)
		default:
			atual.x = 0;
			break;
		}

		//recalcula os retangulos
		retangulo.left = atual.x * retangulo.width;
		retangulo.top = atual.y * retangulo.height;
	}

	//updater especial para tasks
	//recebe o tempo e muda a frame de acordo com tal
	void timerUpdate(int time) {

		int i = 0;

		//o y continua o mesmo
		atual.y = 0;

		//muda o tempo
		atual.x = time;

		//recalcula os retangulos
		retangulo.left = atual.x * retangulo.width;
		retangulo.top = atual.y * retangulo.height;
	}

public:
	//retangulos divididores
	IntRect retangulo;

private:
	//variaveis de imagem
	Vector2u counter;
	Vector2u atual;

	//variaveis de velocidade
	float tTotal;
	float tSwitch;

};