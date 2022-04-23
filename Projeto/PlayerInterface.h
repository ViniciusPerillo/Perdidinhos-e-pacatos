
#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H

#include "Header.h"
#include "Animation.h"
#include "player.h"

/*
 * PlayerInterface: faz a interface do player;
 herda player
*/
class PlayerInterface : public Player {

public:
	//construtor
	PlayerInterface(string image, Vector2f position, Environment* ambiente, float screenSize) :Player(image, position, ambiente) {
		//define o tamanho da tela
		this->screenSize = screenSize;

		//inicia a interface do player
		iniTexture();
		iniSprite();
	}

	//destrutor
	~PlayerInterface() {

	}

	//renderiza o player
	void render(RenderTarget& target) {
		target.draw(this->PlayerSprite);
	}

	//move o player, dado o botao aperdado (dir = +1 x, esq = -1 x)
	void move(const float X) {

		//direcao e movimento
		this->setFacing(X > 0 ? true : false);
		this->PlayerSprite.move(this->getMoveSpeed() * X, 0.0);

		//colisao com os limites da tela
		if (this->PlayerSprite.getPosition().x < - this->playerOrigin || (this->PlayerSprite.getPosition().x > this->screenSize - this->playerOrigin)) {
			this->PlayerSprite.move(-1 * this->getMoveSpeed() * X, 0);
			this->attAmbiente();
			this->PlayerSprite.setPosition(this->getPosition() - Vector2f(this->playerOrigin, 0.0));
		}



		//update da animacao
		this->animation->update(X > 0 ? 0 : 1, this->getDelta());
		this->PlayerSprite.setTextureRect(animation->retangulo);

		//update posicao para classe Player
		this->setPosition(this->PlayerSprite.getPosition() + Vector2f(this->playerOrigin, 0.0));

	}

	void stop(const float X) {
		this->PlayerSprite.move(-1 * this->getMoveSpeed() * X, 0);
		this->PlayerSprite.setPosition(this->getPosition() - Vector2f(this->playerOrigin, 0.0));
	}

	void attSprite() {
		this->PlayerSprite.setPosition(this->getPosition() - Vector2f(this->playerOrigin, 0.0));
	}



private:
	//inicializadores
	void iniTexture() {

		//se diretorio invalido
		if (!this->texture.loadFromFile(this->getImage()))
			cout << " ERROR::PLAYER::INITEXTURE:: invalid directory" << endl;

		//se valido
		else
			this->texture.loadFromFile(this->getImage());
	}

	void iniSprite() {

		//inicia o shape
		this->PlayerSprite = RectangleShape(Vector2f(280, 420));
		this->playerOrigin = this->PlayerSprite.getSize().x / 2;

		//inicia a posicao
		this->PlayerSprite.setOrigin(0, -110);
		this->PlayerSprite.setPosition(this->getPosition() - Vector2f(this->playerOrigin, 0.0));

		//inicia a animacao
		this->animation = new Animation(&texture, Vector2u(4, 2), 0.1f);

		//inicia a textura
		this->PlayerSprite.setTexture(&this->texture);
		this->PlayerSprite.setTextureRect(animation->retangulo);

	}

	//imagem do player
	RectangleShape PlayerSprite;
	Texture texture;

	//animacao do player
	Animation* animation;

	//tamanho total da tela
	float screenSize;

	float playerOrigin;
};

#endif