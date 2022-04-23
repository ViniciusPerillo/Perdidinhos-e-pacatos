
#ifndef GAME_H
#define GAME_H
#include "Header.h"

#include "quest.h"
#include "EnvironmentInterface.h"
#include "PlayerInterface.h"
#include "TaskInterface.h"
#include "ObjectInterface.h"
#include "Menu.h"
#include "draw_list.h"

#include <fstream>
#include <ctime>

//classe game, possui tudo do jogo

class Game {
public:
	//constructor destructor
	inline Game(Environment* starter, DrawList<Quest*>* large, DrawList<Quest*>* medium, DrawList<Quest*>* small, DrawList<string>* words, Quest* end) {

		this->starter = starter;
		this->large = large;
		this->medium = medium;
		this->small = small;
		this->words = words;
		this->end = end;

		this->iniVariables();
		this->iniMusic();
		this->iniWindow();
	}

	inline ~Game() {
		delete this->window;
		delete this->player;
		delete this->task;
	}

	//roda o jogo
	inline void run() {
		Clock clockDelta;

		//Abre o menu de inicio de jogo 
		iniStartMenu();

		while (this->window->isOpen()) {
			//Prepara variaveis para o jogo comecar
			this->preGame();

			//Laco do jogo
			while (this->running) {

				//variaveis auxiliares de tempo
				this->player->setDelta(clockDelta.restart().asSeconds());

				//render
				this->render();

				//update
				this->update();

			}

			//Desaloca memoria e reinicia variaveis 
			this->posGame();

			//Abre o menu de fim de jogo
			this->iniEndMenu();
		}

	}

private:
	//-----Jogo--------------------------------------------------

		//faz mudancas para cada caso de evento
	void update() {
		int side = 0;

		//movimento
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
			this->movePlayer(1);
			side = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
			this->movePlayer(-1);
			side = -1;
		}

		while (this->window->pollEvent(this->eve)) {
			//switch case
			switch (this->eve.type) {

				//fecha the window
			case Event::Closed:
				exit(1);
				break;
			case Event::KeyPressed:
				if (eve.key.code == Keyboard::Escape)
					exit(1);

				//interação
				if (eve.key.code == sf::Keyboard::Space) {
					Target* over = this->player->testTarget();
					if (over != nullptr) {

						this->wordOpen.setPlayingOffset(sf::Time::Zero);
						this->wordOpen.play();

						if (challangeTask(side)) {
							this->advanceQuests(over->getTask());
							delete(this->environment);
							this->iniAmbient();
						}
					}
					
					
				}

				if (eve.key.code == sf::Keyboard::W) {
					if (this->player->attAmbiente()) {
						delete this->environment;
						this->environment = new EnvironmentInterface(this->player->getAmbiente(), (float)this->videoMode.width, (float)this->videoMode.height);
						this->player->attSprite();
					}
				}
				break;
			}
		}
	}

	//Faz toda a renderizacao do jogo
	void render() {

		//limpa a janela
		this->window->clear(Color::Black);

		//desenha o ambiente atual
		this->environment->render(*this->window);

		//desenha as tasks iniciadas
		this->task->render(*this->window);

		//desenha o player
		this->player->render(*this->window);

		//faz o display final
		this->window->display();
	}

	//-----Inicializadores---------------------------------------

	void iniVariables() {

		this->window = nullptr;
		this->player = nullptr;
		this->fonte1.loadFromFile("Fontes/ponderosa.ttf");
		this->fonte2.loadFromFile("Fontes/kongtext.ttf");
		this->playerDirectory = "Textures/Players/";
		
		this->waves = 0;
		this->lastWave = 2;
		this->melhorTempo = INFINITY;

		//especifica o tamanho da janela
		this->videoMode.width = 1440;
		this->videoMode.height = 900;
		
	}

	void iniMusic() {
		this->menuMusic.openFromFile("Sons/menu.ogg");
		this->menuMusic.setVolume(30.0f);
		this->menuMusic.setLoop(true);
		this->menuMusic.setPlayingOffset(sf::seconds(2.0f));
		this->gameMusic.openFromFile("Sons/jogo.ogg");
		this->gameMusic.setVolume(30.0f);
		this->gameMusic.setLoop(true);
		this->endMusic.openFromFile("Sons/end.ogg");
		this->endMusic.setVolume(30.0f);
		this->endMusic.setLoop(true);
		this->startGame.openFromFile("Sons/game_start.ogg");
		this->startGame.setVolume(50.0f);
		this->success.openFromFile("Sons/success.ogg");
		this->success.setVolume(20.0f);
		this->fail.openFromFile("Sons/fail.ogg");
		this->fail.setVolume(20.0f);
		this->wordOpen.openFromFile("Sons/abrirDesafio.ogg");
		this->wordOpen.setVolume(50.0f);
		this->questComplete.openFromFile("Sons/completed.ogg");
		this->questComplete.setVolume(50.0f);
	}

	void drawQuests() {
		this->large->draw(&this->currentLarge);
		this->currentLarge->resetQuest();
		this->medium->draw(&this->currentMedium);
		this->currentMedium->resetQuest();
		this->small->draw(&this->currentSmall);
		this->currentSmall->resetQuest();
	}

	void iniTasks() {
		if (this->waves >= this->lastWave)
			this->task = new TaskInterface("Textures/Menus/quests_menu.png", sf::Vector2u(this->videoMode.width, this->videoMode.height), this->end, this->fonte2);
		else
			this->task = new TaskInterface("Textures/Menus/quests_menu.png", sf::Vector2u(this->videoMode.width, this->videoMode.height), this->currentLarge, this->currentMedium, this->currentSmall, this->fonte2);

	}

	void iniPlayer() {
		//inicia o player
		this->player = new PlayerInterface(this->playerDirectory, Vector2f(450.f, 360.f), this->starter, (float)this->videoMode.width);
	}

	void iniAmbient() {
		//variaveis locais de organizacao
		int y = (this->videoMode.height / 10);
		int height = this->videoMode.height - y;

		//inicia o ambiente
		this->environment = new EnvironmentInterface(this->player->getAmbiente(), (float)this->videoMode.width, (float)this->videoMode.height);
	}

	void iniWindow() {
		//renderiza a janela
		this->window = new RenderWindow(this->videoMode, "Perdidinhos e Pacatos", Style::Titlebar | Style::Close);
		this->window->setFramerateLimit(60);
		this->windowIcon.loadFromFile("Textures/Icon.png");
		this->window->setIcon(this->windowIcon.getSize().x, this->windowIcon.getSize().y, this->windowIcon.getPixelsPtr());
	}

	void preGame() {
		delete this->player;
		delete this->environment;
		delete this->task;

		this->large->reset();
		this->medium->reset();
		this->small->reset();

		this->waves = 0;

		this->drawQuests();
		this->iniTasks();
		this->iniPlayer();
		this->iniAmbient();

		this->running = true;
		this->score.restart();

		this->startGame.setPlayingOffset(sf::Time::Zero);
		this->startGame.play();
		this->gameMusic.setPlayingOffset(sf::Time::Zero);
		this->gameMusic.play();
	}

	void posGame() {
		this->gameMusic.stop();
		this->attScoreData();
	}

	//-----Menus-------------------------------------------------

	void iniStartMenu() {
		//logica
		Clock clock;
		bool escolha = false;

		//interface
		Text titulo("PERDIDINHOS \n   E PACATOS", fonte2, 96); // 12
		Text subtitulo("The Adventure", fonte2, 48); // 13
		Text tShadow("PERDIDINHOS \n   E PACATOS", fonte2, 96);
		Text stShadow("The Adventure", fonte2, 48);
		Text label("Escolha seu personagem\n\n    Pressione Enter   ", fonte2, 24); // 22

		//posicoes
		titulo.setPosition(sf::Vector2f(this->videoMode.width / 2 - 48.0f * 12, this->videoMode.height / 32.0f));
		subtitulo.setPosition(sf::Vector2f(this->videoMode.width / 2 - 24.0f * 13, this->videoMode.height / 32.0f + 225));
		tShadow.setPosition(sf::Vector2f(this->videoMode.width / 2 - 48.0f * 12 + 8, this->videoMode.height / 32.0f + 8));
		stShadow.setPosition(sf::Vector2f(this->videoMode.width / 2 - 24.0f * 13 + 8, this->videoMode.height / 32.0f + 225 + 8));
		label.setPosition(sf::Vector2f(this->videoMode.width / 2 - 12.0f * 22, this->videoMode.height - 150));

		//cores
		titulo.setFillColor(sf::Color(255, 81, 70));
		subtitulo.setFillColor(sf::Color(255, 81, 70));
		tShadow.setFillColor(sf::Color(0, 0, 0, 72));
		stShadow.setFillColor(sf::Color(0, 0, 0, 72));
		label.setFillColor(sf::Color(255, 81, 70));

		//inicia o menu
		this->menu = new Menu("Textures/Menus/start_menu.png", (float)this->videoMode.width, (float)this->videoMode.height, 2);

		//Comeca a musica
		this->menuMusic.play();

		//menu loop
		while (this->menu->getAtivo()) {
			//limpa a janela
			this->window->clear(Color::Black);

			//renderiza o menu
			this->menu->render(*this->window);
			this->window->draw(tShadow);
			this->window->draw(stShadow);
			this->window->draw(titulo);
			this->window->draw(subtitulo);
			this->window->draw(label);

			//faz o display final
			this->window->display();

			//faz update do menu
			while (this->window->pollEvent(this->eve)) {
				switch (this->eve.type) {
					//fecha the window
				case Event::Closed:
					exit(1);
					break;
				case Event::KeyPressed:
					if (eve.key.code == Keyboard::Escape)
						exit(1);
					else if (eve.key.code == Keyboard::Enter)
						this->menu->setAtivo(false);
					else if (eve.key.code == Keyboard::A) {
						escolha = false;
						this->menu->update((int)escolha);
					}
					else if (eve.key.code == Keyboard::D) {
						escolha = true;
						this->menu->update((int)escolha);
					}
					break;
				}
			}

			//animacao do titulo
			switch (clock.getElapsedTime().asMilliseconds() / 400) {
			case 0:
				titulo.setPosition(titulo.getPosition() - sf::Vector2f(0.05f, 0.15f));
				subtitulo.setPosition(subtitulo.getPosition() - sf::Vector2f(0.05f, 0.15f));
				tShadow.setPosition(tShadow.getPosition() - sf::Vector2f(0.05f, 0.15f));
				stShadow.setPosition(stShadow.getPosition() - sf::Vector2f(0.05f, 0.15f));
				break;
			case 2:
				titulo.setPosition(titulo.getPosition() + sf::Vector2f(0.05f, 0.15f));
				subtitulo.setPosition(subtitulo.getPosition() + sf::Vector2f(0.05f, 0.15f));
				tShadow.setPosition(tShadow.getPosition() + sf::Vector2f(0.05f, 0.15f));
				stShadow.setPosition(stShadow.getPosition() + sf::Vector2f(0.05f, 0.15f));
				break;
			case 4:
				clock.restart();
				break;
			default:
				break;
			}
		}

		//escolhe o player
		this->playerDirectory += to_string(escolha) + ".png";

		//Termina a musica
		this->menuMusic.stop();

		delete this->menu;

	}

	void iniEndMenu() {
		//logica
		string scoreStr = to_string((int)round(this->melhorTempo)) + "," + to_string((int)round(this->melhorTempo * 100) % 100) + " segundos";

		//interface
		Text label1("  MAIS UM DIA  \nCHEGOU AO FIM!!", fonte2, 78);
		Text label2("Melhor tempo:", fonte2, 48);
		Text score(scoreStr, fonte2, 48);

		//posicoes
		label1.setPosition(sf::Vector2f(this->videoMode.width / 2 - 39.0f * 15, this->videoMode.height / 4 - 75 * 1.5f));
		label2.setPosition(sf::Vector2f(this->videoMode.width / 2 - 24.0f * 13, 3 * this->videoMode.height / 4  - 75 * .5f));
		score.setPosition(sf::Vector2f(this->videoMode.width / 2 - 24.0f * scoreStr.length(), 3 * this->videoMode.height / 4 + 75 * .5f));

		//cores
		label1.setFillColor(sf::Color::Black);
		label2.setFillColor(sf::Color::Black);
		score.setFillColor(sf::Color::Black);

		//inicia o menu
		this->menu = new Menu("Textures/Menus/end_menu.png", (float)this->videoMode.width, (float)this->videoMode.height);

		//Comeca a musica
		this->endMusic.setPlayingOffset(sf::Time::Zero);
		this->endMusic.play();

		//menu loop
		while (this->menu->getAtivo()) {

			//limpa a janela
			this->window->clear(Color::Black);

			//renderiza o menu
			this->menu->render(*this->window);
			this->window->draw(label1);
			this->window->draw(label2);
			this->window->draw(score);

			//faz o display final
			this->window->display();

			//faz update do menu
			while (this->window->pollEvent(this->eve)) {
				switch (this->eve.type) {
					//fecha the window
				case Event::Closed:
					this->running = false;
					exit(1);
					break;
				case Event::KeyPressed:
					if (eve.key.code == Keyboard::Escape)
						exit(1);

					if (eve.key.code == Keyboard::Enter)
						this->menu->setAtivo(false);
					break;
				}
			}
		}

		//Termina a musica
		this->endMusic.stop();

		delete this->menu;
	}

	bool challangeTask(int dir) {
		//Tratamento do player
		this->stopPlayer(dir);
		this->render();
		
		//logico 
		bool fimDesafio = false;
		string input = "";
		string desafio;


		//declaracoes
		Clock clock;
		
		Text outputDesafio("", fonte1, 36);
		Text outputUser("", fonte1, 36);
		RectangleShape slash(sf::Vector2f(5, 30));
		ObjectInterface fundo("Textures/Menus/word_menu.png", this->videoMode.width / 3, this->videoMode.height / 6, this->videoMode.width / 3, this->videoMode.height / 6 + 12);
		

		//configuracoes iniciais
		outputDesafio.setPosition(sf::Vector2f(this->videoMode.width / 2 - 15 * 7, this->videoMode.height / 5 + 7 - 18));

		//cores
		outputDesafio.setFillColor(sf::Color(160, 0, 0));
		outputUser.setFillColor(sf::Color(160, 0, 0));

		//pegando palavra de desafio
		this->words->draw(&desafio);
		outputDesafio.setString(desafio);

		//menu loop
		while (true) {
			while (this->window->pollEvent(this->eve)) {
				switch (this->eve.type) {
				case Event::Closed:
					this->running = false;
					exit(1);
					break;
				case Event::KeyPressed:
					if (eve.key.code == sf::Keyboard::BackSpace) {
						if (input.length() > 0) {
							input.pop_back();
						}
					}
					else if (eve.key.code == sf::Keyboard::Enter) {
						if (input == desafio) {
							this->success.setPlayingOffset(sf::Time::Zero);
							this->success.play();
						}
						else {
							this->fail.setPlayingOffset(sf::Time::Zero);
							this->fail.play();
						}
						return input == desafio;
					}
					break;
				case Event::TextEntered:
					if (verifyChar(eve.text.unicode) && input.length() < 7) {
						input += eve.text.unicode;
					}
					break;

				}
			}

			//atualiza palavra sendo digitada
			outputUser.setString(input);
			outputUser.setPosition(sf::Vector2f(this->videoMode.width / 2 - 15 * input.length(), this->videoMode.height / 5 + 57 - 18));
			
			//atualiza localizacao da proxima letra
			slash.setPosition(outputUser.getPosition() + sf::Vector2f(30.0f * input.length() + 5, 9.0f));

			//anumacao localizacao da proxima letra
			switch (clock.getElapsedTime().asMilliseconds() / 400) {
			case 0:
				slash.setFillColor(sf::Color(160, 0, 0));
				break;
			case 2:
				slash.setFillColor(sf::Color(160, 0, 0, 0));
				break;
			case 4:
				clock.restart();
				break;
			default:
				break;
			}

			//rendeniza o menu
			fundo.render(*this->window);
			this->window->draw(outputDesafio);
			this->window->draw(outputUser);
			this->window->draw(slash);

			this->window->display();
		}
	}

//-----Metodos para funcionamento do jogo--------------------	

		//Movimentacao do player pelo ambiente
	void movePlayer(int dir) {

		Environment* ambienteAnterior = this->player->getAmbiente();

		this->player->move((float)dir);

		if (ambienteAnterior != this->player->getAmbiente()) {

			delete this->environment;
			this->environment = new EnvironmentInterface(this->player->getAmbiente(), (float)this->videoMode.width, (float)this->videoMode.height);
		}

	}

	void stopPlayer(int dir) {
		this->player->stop((float)dir);
		this->render();
	}

	//Avanca um Quest
	void advanceQuests(bool* task) {
		//verifica se esta no fim de jogo
		if (this->waves < this->lastWave) {
			if (task == this->currentLarge->getCurrentTask()) {
				
				this->currentLarge->advance();

				//Se quests acaba, toca musica
				if (this->currentLarge->getCurrentTask() == nullptr) {
					//Musica
					this->questComplete.setPlayingOffset(sf::Time::Zero);
					this->questComplete.play();
				}

			}
			else if (task == this->currentMedium->getCurrentTask()) {
				
				this->currentMedium->advance();

				//Se quests acaba, toca musica
				if (this->currentMedium->getCurrentTask() == nullptr) {
					//Musica
					this->questComplete.setPlayingOffset(sf::Time::Zero);
					this->questComplete.play();
				}
			}
			else if (task == this->currentSmall->getCurrentTask()) {
				
				this->currentSmall->advance();

				//Se quests acaba, toca musica
				if (this->currentSmall->getCurrentTask() == nullptr) {
					//Musica
					this->questComplete.setPlayingOffset(sf::Time::Zero);
					this->questComplete.play();
				}
			}
			
			//Atualiza interface
			this->task->update();

			this->testAllCompleted();

		//Caso ultima quest do jogo
		}else {
			this->end->advance();

			this->running = false;
		}
		//Atualiza interface
		this->task->update();
	}

	//testa se  trio de quests foi completo
	void testAllCompleted() {
		if (this->currentLarge->isFinished() && this->currentMedium->isFinished() && this->currentSmall->isFinished()) {
			//verifica se esta no fim de jogo
			if (this->waves < this->lastWave-1)
				this->drawQuests();
			else 
				this->end->resetQuest();
			
			this->waves++;
			delete(this->task);
			this->iniTasks();
			
		}
	}

	//atualiza o recorde 
	void attScoreData() {
		float new_score = score.getElapsedTime().asSeconds();
		if (new_score < this->melhorTempo)
			this->melhorTempo = new_score;
	}

																
	//limita o caracter sendo digitado
	bool verifyChar(char in) {
		return ((in == 33) ||                      //  ! 
			(in > 40 && in < 42) ||                         // ( e )
			(in > 43 && in != 45 && in != 47 && in < 58) || // , e . e 0123456789
			(in > 64 && in < 91) ||                         // ABCDEFGHIJKLMNOPQRSTUVWXYZ
			(in == 95) ||                                   // _
			(in > 96 && in < 123));                         // abcdefghijklmnopqrstuvwxyz
	}

	//-----Variaveis---------------------------------------------

	//Window e video mode
	RenderWindow* window;
	VideoMode videoMode;
	Event eve;
	Image windowIcon;
	
	//Interface logic
	Font fonte1;
	Font fonte2;
	string playerDirectory;

	//Game logic
	int waves;
	int lastWave;
	bool running;
	float melhorTempo;
	Clock score;

	//Interface Objects
	PlayerInterface* player;
	EnvironmentInterface* environment;
	TaskInterface* task;
	Menu* menu;

	//Dados
	Environment* starter;
	DrawList<Quest*>* large;
	DrawList<Quest*>* medium;
	DrawList<Quest*>* small;
	DrawList<string>* words;

	//Tasks
	Quest* currentLarge;
	Quest* currentMedium;
	Quest* currentSmall;
	Quest* end;

	//Sons
	Music menuMusic;
	Music gameMusic;
	Music endMusic;
	Music wordOpen;
	Music success;
	Music fail;
	Music questComplete;
	Music startGame;
};

#endif 