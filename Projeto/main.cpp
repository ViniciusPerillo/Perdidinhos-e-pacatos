#include "Game.h"
#include "fase.h"
#include <iostream>

using namespace sf;

void iniWords(DrawList<string>&);

int main() {
    //Inizializando dados
    DrawList<string> words(true);

    fase::iniFase();

    iniWords(words);

    std::cout << "Esc - Fechar Janela\n\nA - Mover para a esquerda\n\nD - Mover para a direita\n\nW - Abrir porta\n\nSpace - Interagir com objetos";


    Game game(&fase::quarto1, &fase::drawLarge, &fase::drawMedium, &fase::drawSmalls, &words, &fase::end);

    //runs o game
    game.run();

    //fim
    return 0;
}

void iniWords(DrawList<string>& words) {
    //equipe 7
    words.append("BALIERO");
    words.append("ANAEREN");
    words.append("VINICIO");

    words.append("Menotti");
    words.append("verilog");
    words.append("jogebra");
    words.append("jojobro");
    words.append("jojofag");
    words.append("abacaxi");
    words.append("abacate");
    words.append("conicas");
    words.append("Roberto");
    words.append("Ricardo");
    words.append("carecas");
    words.append("calvice");
    words.append("Ferrari");
    words.append("ajeitar");
    words.append("mascara");
    words.append("pacatos");
    words.append("perdido");
    words.append("arrumar");
    words.append("UFSCar!");
    words.append("Carros3");
    words.append("Shrek_1");
    words.append("Shrek_2");
    words.append("Shrek_3");
    words.append("alegria");
    words.append("Jumanji");
    words.append("TheRock");
    words.append("torador");
    words.append("7355608");
    words.append("Madoka!");
    words.append("3.14159");
    words.append("garrafa");
    words.append("GBDfoda");
    words.append("zaralho");
    words.append("aspinha");
    words.append("pancada");
    words.append("Ubatuba");
    words.append("Afranio");
    words.append("Perillo");
    words.append("discord");
    words.append("EADENPE");
    words.append("Faz_o_L");
    words.append("Mt_sono");
    words.append("Oi_bala");
    words.append("Desculp");
    words.append("SouBuro");
    words.append("AVAcaiu");
    words.append("LOLzin!");
    words.append("VaiLOUD");


};