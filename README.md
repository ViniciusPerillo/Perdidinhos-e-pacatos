# Perdidinhos e Pacatos - The Adventure

Perdidinhos e Pacatos é um trabalho para a matéria de Arquitetura e Estrutura de Dados 1, feita no segundo semestre do Bacharelado de Ciência da Computação UFSCar - São Carlos, ministrada pelo pelo professor Roberto Ferrari no ano de 2022 (ENPE 2021/2).

___

## AUTORES

### Ana Ellen Deodato Pereira da Silva 
> Arte e Interface

[![Gmail Badge](https://img.shields.io/badge/-anaellen.uba@gmail.com-c14438?style=flat-square&logo=Gmail&logoColor=white&link=mailto:anaellen.uba@gmail.com)](mailto:anaellen.uba@gmail.com)

### Lucas Maciel Balieiro 
> Jogabilidade e Fases

[![Gmail Badge](https://img.shields.io/badge/-lucas.macbali@gmail.com-c14438?style=flat-square&logo=Gmail&logoColor=white&link=mailto:lucas.macbali@gmail.com)](mailto:lucas.macbali@gmail.com)

### Vinícius Gonçalves Perillo 
> Dados e Lógica

[![Gmail Badge](https://img.shields.io/badge/-vinicius.perillo25@gmail.com-c14438?style=flat-square&logo=Gmail&logoColor=white&link=mailto:vinicius.perillo25@gmail.com)](mailto:vinicius.perillo25@gmail.com)

___

## Teaser
___

## APLICAÇÃO

Nesse jogo, você é um estudante universitário tentando sobreviver às adversidades (e à bagunça) que vem com morar em um apartamento com seus colegas, tendo que fazer todas as suas tarefas escolares e domiciliares o mais rápido possível para poder passar o resto do dia assistindo animes.


___

## COMO DESENVOLVER UM PROJETO COMO ESTE

O projeto pode ser dividido em 3 grandes unidades de software: Dados, Interface e Estrutura de Dados, que são inicializadas em `fase.h` e gerenciadas pelo motor `Game.h`.

![Unidades de Software](https://user-images.githubusercontent.com/76188994/164943225-2593e8cc-b14d-4ae4-bc22-a4bae79f457a.png)

### Dados
Os dados são um conjunto de classes que fornece os dados de funcionamento do jogo, eles são completamente desconectados da interface e foram planejados a fim de proporcionar uma boa modularização.

Para entender essas classes, é necessário entender como o jogo funciona. Primeiramente, a fase é constituída por `Environments.h`, ou ambientes/cômodos, esses ambientes são compostos por dois tipos de membros: os `Targets.h` e os `Linkers.h`, ambos herdam atributos em comum de `EnvironmentMember.h`. 

- `Targets.h`: ou alvos, são responsáveis por compor os móveis do cômodo, são objetos que o jogador irá interagir para realizar as tarefas. Com isso conseguimos criar qualquer cômodo manipulando suas imagens e posições. 

- `Linkers.h`: ou conectores, são regiões no ambiente que realizam a troca de ambiente, eles interligam os ambientes no grafo que representa a casa. Dessa forma podemos construir qualquer disposição de residência apenas mudando os ambientes que os apontam. 

As quatros classes podem compor um grupo que forma os ambientes. Nossa fase se dispõe como o grafo a seguir:

![Grafo da Fase](https://user-images.githubusercontent.com/76188994/164943227-731ce7ae-e357-4719-91d2-3ca5b55faee5.png)

*Pontas são passagem direta e bases são portas*

Além delas, temos duas classes que se relacionam de forma mais direta com `Game.h` e acabam por representar mais na jogabilidade: `Quest.h` e `Player.h`. 
`Player.h` guarda dados de movimentação e um ponteiro de ambiente que aponta para o ambiente em que o player está no grafo. 

Por fim, `Quest.h` é uma classe (que pode ser considerada uma estrutura de dados, mas devido ao seu uso extremamente específico, ela se encaixa melhor na sessão de dados) que encadeia ponteiros de booleanos, cada ponteiro é apontado exclusivamente por um Target, dessa forma quando ele é true a tarefa naquele alvo fica ativa. Dessa forma podemos montar qualquer sequência de tarefas a fim de compor uma missão.

## Interface
As classes que compõem a interface (vermelho) são compostas por objetos da biblioteca SFML.

Cada objeto renderizado possui diferentes especificidades, logo, para supri-las, foram criadas as classes:  

- `Animation.h`: compõe todas as outras interfaces de objetos interativos, como no SFML não é possível inserir arquivos .gif, para que algo troque seu estado, uma classe que converta uma spritesheet em objeto na tela é necessária. Esta classe faz tipos diferentes de animação de acordo com a necessidade de cada objeto: o player muda de sprite de acordo com a direção e a velocidade com que anda, os objetos de acordo com seu estado.
- `ObjectInterface.h`: é composta por uma Animation, é responsavel por conter os objetos SFML resposáveis por colocar imagens na janela.
- `PlayerInterface.h`: tem uma relação íntima com a classe de dados Player, pois a herda, fazendo update da textura e da posição do jogador, trocando suas sprites de acordo com a direção que o boneco for comandado a andar e sua localização conforme o movimento e posição inicial com os ambientes.
- `EnvironmentMember.h`: controla o plano de fundo atual, o posicionamento e o estado dos objetos de cada cômodo.
- `Menu.h`: inicializa o menu de tela cheia.
- `TaskInterface.h`: ordena as tarefas que devem ser realizadas, controla os objetivos atuais e os renderiza na tela.

 
## Estruturas de dados
As estruturas de dados estão espalhadas pelas outras unidades de software. Delas temos três estruturas: BinaryTree, Array e DrawList. 

- `BinaryTree.h`: ou árvore binária, é utilizada para armazenar os Targets e Linkers do ambiente, como o verifica se o player está sobre algum dos dois em determinados momentos a tarefa de varredura em uma árvore é mais eficiente do que a em um vetor, dessa forma economizamos poder de processamento. 

- `Array.h`: foi usado no lugar da árvore em casa que a indexação é crucial para o funcionamento da manipulação dos dados, há uma perda de processamento, mas há um ganho na simplicidade de implementação. Essa classe utiliza Node para funcionar. 

- `DrawList.h`: foi feita para gerar aleatoriedades pras fases, ela é uma lista encadeada que sorteia um item de seu interior, caso a DrawList seja instanciada com true, esse item não será mais sorteado até que todos os outros tenham sido sorteados. Ela utiliza Card e Array para funcionar. 

- `Quest.h`: acredito que possa ser considerada uma estrutura de dados, encadeia ponteiros de booleanos e os indexa, o índice está relacionado a um vetor de strings que dá nome às tarefas.	

___

## CONCLUSÕES 

O desenvolvimento do jogo proporcionou oportunidades de aprimorar nossos conhecimentos em código, além de trazer experiência em produções de larga escala em grupo. O projeto requereu a aplicação prática de diversos conceitos aprendidos ao longo do ano, principalmente das matérias de Programação Orientada a Objetos e Algoritmos e Estruturas de Dados. Aprendemos também a buscar respostas independentemente, pelo fato de termos que aprender a utilizar uma biblioteca gráfica sem experiência prévia.

___

## Instruções para Jogar

Extraia o arquivo `.zip` e execute o jogo!
Para mais informações sobre o jogo leia o README.txt

