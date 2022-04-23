#pragma once

#include "Header.h"
#include "ObjectInterface.h"
#include "array.h"


//TaskInterface cria toda a interface relacionada a uma task
/*TaskInterface deve ser herdada por Taks*/
class TaskInterface {
public:

	//construtor 3 tasks
	TaskInterface(string image, Vector2u screenSize, Quest* q1, Quest* q2, Quest* q3, Font& fonte) {
		this->fundo = new ObjectInterface(image, screenSize.x/* width */, screenSize.y / 5 /* heigth */);
		this->screenSize = screenSize;
		
		this->quests.append(q1);
		this->quests.append(q2);
		this->quests.append(q3);

		setTexts(fonte);

		update();
	}
	//construtor 1 tasks
	TaskInterface(string image, Vector2u screenSize, Quest* q, Font& fonte) {
		this->fundo = new ObjectInterface(image, screenSize.x/* width */, screenSize.y / 5 /* heigth */);
		this->screenSize = screenSize;

		this->quests.append(q);
		
		setTexts(fonte);

		update();
	}

	~TaskInterface() {
		delete this->fundo;
	}

	void update() {
		float largura = screenSize.x / this->quests.getSize();
		float altura = screenSize.y / 6;
		int wrapI;

		for (int i = 0; i < this->quests.getSize(); i++) {
			//testa se tem quebra de linha
			wrapI = this->quests[i]->getTitle().length();

			//responsividade
			int titY = altura / 4 - ((int)localizeWrapLine(wrapI, this->quests[i]->getTitle()) + 1) * 15 + 15;
			int titX = largura / 2 - 15.0f * wrapI + i * largura;

			//testa se tem quebra de linha
			wrapI = this->quests[i]->getState().length();
			//responsividade
			int texY = 3 * altura / 4 - ((int)localizeWrapLine(wrapI, this->quests[i]->getState()) + 1) * 12 + 12;
			int texX = largura / 2 - 12.0f * wrapI + i * largura;

			//atualiza dos textos e posicoes
			this->textos[i].setString(this->quests[i]->getState());
			this->titulos[i].setPosition(sf::Vector2f(titX, titY));
			this->textos[i].setPosition(sf::Vector2f(texX, texY));
		}
			
	}

	void render(sf::RenderTarget& target){
		//rendeniza os elemntentos
		this->fundo->render(target);
		for (int i = 0; i < quests.getSize(); i++) {
			target.draw(this->titulos[i]);
			target.draw(this->textos[i]);
		}
	}
	

private:
	//verifica se tem quebra de linha na string
	bool localizeWrapLine(int& pos, string string) {
		bool found = false;

		for (int i = 0; i < string.length(); i++) {
			if (string[i] == '\n') {
				found = true;
				pos = i;
				return found;
			}
		}

		return found;
	}

	//configurações padrão os textos
	void setTexts(Font& fonte) {
		for (int i = 0; i < this->quests.getSize(); i++) {
			this->titulos.append(sf::Text(this->quests[i]->getTitle(), fonte, 30));
			this->textos.append(sf::Text(this->quests[i]->getTitle(), fonte, 24));
			this->titulos[i].setFillColor(sf::Color::Black);
			this->textos[i].setFillColor(sf::Color::Black);
		}
	}

	//logica de posicao e tempo
	Vector2u screenSize;
	Array<Quest*> quests;
	Array<Text> textos;
	Array<Text> titulos;
	ObjectInterface* fundo;

};