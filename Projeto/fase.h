#include "Game.h"
namespace fase{
    Environment sala("Textures/Ambientes/Sala/SalaFundo.png");
    Environment cozinha("Textures/Ambientes/Cozinha/CozinhaFundo.png");
    Environment lavanderia("Textures/Ambientes/Lavanderia/LavanderiaFundo.png");
    Environment quarto1("Textures/Ambientes/Quarto1/QuartoFundo.png");
    Environment quarto2("Textures/Ambientes/Quarto2suite/Quarto2suiteFundo.png");
    Environment quarto3("Textures/Ambientes/Quarto3/Quarto3Fundo.png");
    Environment banheiro("Textures/Ambientes/Banheiro/BanheiroFundo.png");
    Environment suite("Textures/Ambientes/Suite/BanheiroSuiteFundo.png");
    Environment corredor("Textures/Ambientes/Corredor/CorredorFundo.png");

    bool tasks[28] = {false};

    Quest* large[4] = { nullptr };
    Quest* medium[4] = { nullptr };
    Quest* small[4] = { nullptr };
    string rei[2] = { "Completa", "  E abrace a  \n   Rei-chan   " };
    Quest end(&tasks[1], "Veja o melhor \nanime do mundo", rei);


    DrawList<Quest*> drawLarge(true);
    DrawList<Quest*> drawMedium(true);
    DrawList<Quest*> drawSmalls(true);


    inline void iniTargets() {
        Target* targets[32]{
            new Target(702, 287, "Textures/Ambientes/Sala/Sofa_LeituraSala.png", &tasks[0]),                //taskSofaDir
            new Target(402, 299, "Textures/Ambientes/Sala/Sofa_ReiSala.png", &tasks[1]),                    //taskSofaEsq
            new Target(1212, 194, "Textures/Ambientes/Sala/MesaLivroSala.png", &tasks[2]),                  //taskMesaDir
            new Target(1008, 203, "Textures/Ambientes/Sala/MesaFlorSala.png", &tasks[3]),                   //taskMesaEsq

            new Target(18, 125, "Textures/Ambientes/Cozinha/LixoCozinha.png", &tasks[4]),                   //taskLixoC
            new Target(144, 401, "Textures/Ambientes/Cozinha/ArmarioCozinha.png", &tasks[5]),               //taskArmarioC
            new Target(546, 263, "Textures/Ambientes/Cozinha/PiaCozinha.png", &tasks[6]),                   //taskPia
            new Target(810, 281, "Textures/Ambientes/Cozinha/FogaoCozinha.png", &tasks[7]),                 //taskFogao
            new Target(1092, 347, "Textures/Ambientes/Cozinha/GeladeiraCozinha.png", &tasks[8]),            //taskGeladeira

            new Target(756, 257, "Textures/Ambientes/Lavanderia/TanqueLavanderia.png", &tasks[9]),          //taskTanque
            new Target(456, 275, "Textures/Ambientes/Lavanderia/LavaRoupasLavanderia.png", &tasks[10]),     //taskMaquina
            new Target(144, 239, "Textures/Ambientes/Lavanderia/LucasLavanderia.png", &tasks[11]),          //taskLixoL
            new Target(1038, 365, "Textures/Ambientes/Lavanderia/ArmarioLavanderia.png", &tasks[12]),       //taskArmarioL

            new Target(60, 149, "Textures/Ambientes/Quarto1/CestoRoupaQuarto.png", &tasks[13]),             //taskCestoQ1
            new Target(390, 365, "Textures/Ambientes/Quarto1/ComputadorQuarto.png", &tasks[14]),            //taskMesaQ1
            new Target(984, 449, "Textures/Ambientes/Quarto1/ArmarioQuarto.png", &tasks[15]),               //taskArmarioQ

            new Target(60, 149, "Textures/Ambientes/Quarto2suite/CestoRoupaQuarto2suite.png", &tasks[16]),  //taskCestoQ2
            new Target(966, 365, "Textures/Ambientes/Quarto2suite/PCQuarto2suite.png", &tasks[17]),         //taskMesaQ2

            new Target(1200, 149, "Textures/Ambientes/Quarto3/CestoRoupaQuarto3.png", &tasks[18]),          //taskCestoQ3
            new Target(672, 443, "Textures/Ambientes/Quarto3/CelularQuarto3.png", &tasks[19]),              //taskPrateleira

            new Target(42, 452, "Textures/Ambientes/Banheiro/PiaBanheiro.png", &tasks[20]),                 //taskPiaB1
            new Target(842, 107, "Textures/Ambientes/Banheiro/LucasBanheiro.png", &tasks[21]),              //taskLixoB1
            new Target(1068, 371, "Textures/Ambientes/Banheiro/ChuveiroBanheiro.png", &tasks[22]),          //taskBoxB1
            new Target(534, 284, "Textures/Ambientes/Banheiro/SanitarioBanheiro.png", &tasks[23]),          //taskVasoB1

            new Target(936, 452, "Textures/Ambientes/Suite/PiaBanheiroSuite.png", &tasks[24]),              //taskPiaB2
            new Target(475, 107, "Textures/Ambientes/Suite/LucasBanheiroSuite.png", &tasks[25]),           //taskLixoB2
            new Target(606, 287, "Textures/Ambientes/Suite/SanitarioBanheiroSuite.png", &tasks[26]),        //taskVasoB2

            new Target(534, 131, "Textures/Ambientes/Corredor/ManchaCorredor.png", &tasks[27])};            //taskMancha
        int i = 0;
        int lf;
        for (lf = i; i < 4 + lf; i++) {
            sala.addTarget(*targets[i]);
            delete(targets[i]);
        }
        for (lf = i; i < 5 + lf; i++) {
            cozinha.addTarget(*targets[i]);
            delete(targets[i]);
        }
        for (lf = i; i < 4 + lf; i++) {
            lavanderia.addTarget(*targets[i]);
            delete(targets[i]);
        }
        for (lf = i; i < 3 + lf; i++) {
            quarto1.addTarget(*targets[i]);
            delete(targets[i]);
        }
        for (lf = i; i < 2 + lf; i++) {
            quarto2.addTarget(*targets[i]);
            delete(targets[i]);
        }
        for (lf = i; i < 2 + lf; i++) {
            quarto3.addTarget(*targets[i]);
            delete(targets[i]);
        }
        for (lf = i; i < 4 + lf; i++) {
            banheiro.addTarget(*targets[i]);
            delete(targets[i]);
        }
        for (lf = i; i < 3 + lf; i++) {
            suite.addTarget(*targets[i]);
            delete(targets[i]);
        }
        corredor.addTarget(*targets[i]);
        delete(targets[i]);
    }

    inline void iniLinkers() {
        Linker left(-5, 10, 1430);
        Linker right(1435, 10, 10);


        sala.addBorder(left, &cozinha);
        sala.addBorder(right, &corredor);
        Linker porta1(24, 366, 120);
        sala.addBorder( porta1, &banheiro);

        cozinha.addBorder(left, &lavanderia);
        cozinha.addBorder(right, &sala);

        lavanderia.addBorder(right, &cozinha);
    
        Linker porta2(342, 366, 1320);
        quarto2.addBorder(left, &corredor);
        quarto2.addBorder(porta2, &suite);

        Linker leftP3(-5, 10, 240);
        quarto1.addBorder(leftP3, &corredor);

        Linker rightP4(1435, 10, 1200);
        quarto3.addBorder(rightP4, &corredor);
    
        Linker leftP1(-5, 10, 210);
        banheiro.addBorder(leftP1, &sala);

        Linker rightP2(1435, 10, 522);
        suite.addBorder(rightP2, &quarto2);

        Linker porta3(54, 366, 120);
        Linker porta4(1014, 366, 1320);
        corredor.addBorder(left, &sala);
        corredor.addBorder(right, &quarto2);
        corredor.addBorder(porta3, &quarto1);
        corredor.addBorder(porta4, &quarto3);
    }

    inline void iniQuests() {
        //Recolher lixo 4 21 25 11
         //Recolher lixo 4 21 25 11
        static string lixo[5] = { "Completa", "Recolha o lixo\n  da cozinha  ", "...o da suite ", "E no banheiro ", "Joga tudo la\n     fora     " };
        large[0] = new Quest(&tasks[4], "Retire-se", lixo);
        large[0]->append(&tasks[25]);
        large[0]->append(&tasks[21]);
        large[0]->append(&tasks[11]);

        //Lavar roupa 13 16 18 10
        static string roupa[5] = { "Completa", " Pegue  as  \nroupas sujas", "Agora  do\namiguinho", "De mais  um\n quarto... ", "Coloque tudo\n para lavar " };
        large[1] = new Quest(&tasks[13], "Cheirinho\nde  otaku", roupa);
        large[1]->append(&tasks[16]);
        large[1]->append(&tasks[18]);
        large[1]->append(&tasks[10]);

        //Fazer comida 8 7 8 6
        static string comida[5] = { "Completa", "   Pegue os   \n ingredientes ", " TA QUEIMANDO \n   O ARROZ    ", "Guarde  as\n  sobras  ", "Lave os pratos" };
        large[2] = new Quest(&tasks[8], "Hmmm que fome", comida);
        large[2]->append(&tasks[7]);
        large[2]->append(&tasks[8]);
        large[2]->append(&tasks[6]);

        //Limpar Casa 12 22 5 27
        static string limpar[5] = { "Completa", " Material de  \n   limpeza    ", "O que eh isso\n   no box?     ", "Mataram alguem\nnessa cozinha?", 
            "O creeper quase\n  explodiu...  " };
        large[3] = new Quest(&tasks[12], "Essa casa ta\n um aterro ", limpar);
        large[3]->append(&tasks[22]);
        large[3]->append(&tasks[5]);
        large[3]->append(&tasks[27]);

        //Trollar amiguinho 17 19
        static string trollar[3] = { "Completa", "  Perca no  \njogo do amigo", " Coloque um   \nalarme pra 4am" };
        medium[0] = new Quest(&tasks[17], "Reforce a\n amizade ", trollar);
        medium[0]->append(&tasks[19]);

        //Aguar Planta 9 3
        static string planta[3] = { "Completa", "Pegue  agua\n no tanque ", "   Toma agua  \n   plantinha  " };
        medium[1] = new Quest(&tasks[9], "Como ela ainda\n esta  viva? ", planta);
        medium[1]->append(&tasks[3]); //Te odeio ana ele

        //Escovar os Dentes 20 24
        static string dentes[3] = { "Completa", "Escove  seus\n   dentes   ", "Nao tem pasta \nnesse banheiro" };//desculpa fui chato ;-; te odeio
        medium[2] = new Quest(&tasks[20], "Bafo de esgoto", dentes);
        medium[2]->append(&tasks[24]);

        //Ler 2 0
        static string ler[3] = { "Completa", "Pegue o livro\n  Amanhecer  ", "A pagina 40 eh\n  curiosa...  " };
        medium[3] = new Quest(&tasks[2], "Sente se  para\nler Crepusculo", ler);
        medium[3]->append(&tasks[0]);

        //Usar o banheiro 23
        static string mijar[2] = { "Completa", "Use o banheiro" };
        small[0] = new Quest(&tasks[23], "Bebi  agua\n  demais  ", mijar);

        //Codar 14
        static string codar[2] = { "Completa", "    O prazo   \n termina hoje " };
        small[1] = new Quest(&tasks[14], "Tem tarefa\n  no AVA  ", codar);

        //Arrumar o guarda-roupa 15
        static string guardaRoupa[2] = { "Completa", " Tem roupa ate\n    no chao   " };
        small[2] = new Quest(&tasks[15], " Cara, arruma \n     isso     ", guardaRoupa);

        //Procurar o celular 26
        static string celular[2] = { "Completa", "Procure seu\n  celular  " };
        small[3] = new Quest(&tasks[26], " Acontece com \nos melhores...", celular);


        drawLarge.append(large[0]);
        drawLarge.append(large[1]);
        drawLarge.append(large[2]);
        drawLarge.append(large[3]);


        drawMedium.append(medium[0]);
        drawMedium.append(medium[1]);
        drawMedium.append(medium[2]);
        drawMedium.append(medium[3]);


        drawSmalls.append(small[0]);
        drawSmalls.append(small[1]);
        drawSmalls.append(small[2]);
        drawSmalls.append(small[3]);
    }

    inline void iniFase(){
        iniTargets();
        iniLinkers();
        iniQuests();

    }
}

