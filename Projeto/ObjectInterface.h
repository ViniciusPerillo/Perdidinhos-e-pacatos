/* Autores: Vinicius Perillo, Ana Ellen Deodato e Lucas Balieiro
 * Data: 04/2022
 * Segundo Periodo do Bacharelado de Ciencia da Computa��o
 * Header da classe Sprite
*/
#pragma once

#include "Header.h"
#include "Animation.h"
#include <iostream>

//Objeto interface
//cria um objeto a ser exibido na interface
class ObjectInterface {
public:
	//construtor recebe a string da imagem, largura, altura, posicoes x, y, quantia de sprites da imagem para x e y
	ObjectInterface(sf::String directory, float width, float height, float x = 0.0f, float y = 0.0f, int sheetX = 1, int sheetY = 1) {

		//iniciando a animacao
		this->sheetX = sheetX;
		this->sheetY = sheetY;

		//setando posicao e tamanho do objeto
		this->setImageDirectory(directory);
		this->StaticObject.setPosition(x, y);
		this->StaticObject.setSize(sf::Vector2f(width, height));

	}
	//destrutor
	~ObjectInterface() {
		delete(this->animation);
	}

	//getters
	sf::Image& getImage() {
		return this->image;
	}


	sf::RectangleShape getSprite() {
		return this->StaticObject;
	}

	sf::Vector2u getPosition() {
		return this->position;
	}

	//setters
		//coloca uma imagem no objeto
	void setImageDirectory(sf::String directory) {

		//se diretorio invalido
		if (!this->image.loadFromFile(directory))
			cout << " ERROR::SETIMAGEDIRECTORY:: invalid directory" << endl;

		//se valido
		else
			this->image.loadFromFile(directory);

		this->texture.loadFromImage(this->image);

		//inicia a textura
		this->StaticObject.setTexture(&this->texture);

		//inicia a animacao no estado default
		this->animation = new Animation(&texture, sf::Vector2u(this->sheetX, this->sheetY), 0.0f);
		this->animation->staticUpdate(0);
		this->StaticObject.setTextureRect(this->animation->retangulo);
	}

	void setPosition(float x = -1.0f, float y = -1.0f) {

		//mudando a posicao do objeto
		if (x >= 0)
			this->position.x = (int)x;
		if (y >= 0)
			this->position.y = (int)y;
		this->StaticObject.setPosition((float)this->position.x, (float)this->position.y);
	}

	//update da animacao, recebe o estado (ativo, desativado) que o objeto se encontra
	void update(int estado) {

		this->animation->staticUpdate(estado);
		this->StaticObject.setTextureRect(this->animation->retangulo);
	}

	//faz update da animacao de acordo com o tempo restante
	void taskUpdater(int tempo) {

		this->animation->timerUpdate(tempo);
		this->StaticObject.setTextureRect(this->animation->retangulo);
	}

	//renderiza
	void render(sf::RenderTarget& target) {

		target.draw(this->StaticObject);
	}

private:

	//definem a imagem do objeto
	sf::Image image;
	sf::Texture texture;
	sf::RectangleShape StaticObject;

	//define a posicao do objeto
	sf::Vector2u position;

	//faz a animacao
	Animation* animation;
	int sheetX, sheetY;
};