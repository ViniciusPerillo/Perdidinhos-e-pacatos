#pragma once


template <typename T>
class BinaryTree {
public:
    BinaryTree() {
        this->height = 1;
        this->mother = nullptr;
        this->right = nullptr;
        this->left = nullptr;
        this->getAllState = 'A';
    }

    //contrutor alternativo
    BinaryTree(T info, BinaryTree<T>* mother) {
        this->info = info;
        this->height = 1;
        this->mother = mother;
        this->right = nullptr;
        this->left = nullptr;
        this->getAllState = 'A';
    }

    /*  isInTree: verifica se o valor info esta na arvore binaria
        entrada: inteiro a ser verificado
        retorno: true, se for encontrado, e false, caso contrario
    */
    bool isInTree(T info) {
        //caso vazia
        if (this->isEmpty())
            return false;

        //caso no encontrado
        if (this->info == info && !this->isHeader())
            return true;

        //recursividade
        if (info > this->info)
            return this->right == nullptr ? false : this->right->isInTree(info);
        else
            return this->left == nullptr ? false : this->left->isInTree(info);
    }


    /*  insere: insere um inteiro nao repetido na arvore
        entrada: inteiro a ser inserido
        retorno: true, se for inserido, e false, caso contrario
    */
    bool insere(T info) {
        //caso vazio
        if (this->isEmpty() && this->isHeader()) {
            this->right = new BinaryTree(info, this);
            this->left = this->right;

            this->attHeight();
            return true;
        }

        //caso ja exista
        if ((info == this->info) && (!this->isHeader()))
            return false;

        //recursividade
        bool worked;

        if (info > this->info) {
            //caso no folha
            if (this->right == nullptr) {
                this->right = new BinaryTree(info, this);
                worked = true;
            }else
                worked = this->right->insere(info);
        }
        else {
            //caso no folha
            if (this->left == nullptr) {
                this->left = new BinaryTree(info, this);
                worked = true;
            }else
                worked = this->left->insere(info);
        }

        //rebalance
        this->attHeight();
        this->rebalance();
        return worked;

    }

    /*  remove: remove um inteiro da arvore
        entrada: inteiro a ser retirado
        retorno: true, se for retirado, e false, caso contrario
    */
    bool remove(T info) {
        //caso vazia
        if (this->isEmpty() && this->info != info)
            return false;

        //caso no encontrado
        if (this->info == info && !this->isHeader()) {

            //no folha
            if (this->isEmpty()) {
                this->setMothersPointer(this, nullptr);
                delete(this);

                //no unico filho
            }
            else if (this->right == nullptr || this->left == nullptr) {
                (this->right == nullptr ? this->left : this->right)->mother = this->mother;
                this->setMothersPointer(this, (this->right == nullptr ? this->left : this->right));
                delete(this);

                //caso no com dois filhos
            }
            else {
                //declaracoes locais
                BinaryTree* aux;
                T old_info;

                //para evitar balanceamentos desnecessarios
                if (this->getBalanceRate() >= 0) {
                    //valor inicial
                    aux = this->right;

                    //procurando o menor dos maiores;
                    while (aux->left != nullptr)
                        aux = aux->left;

                }else {
                    //valor inicial
                    aux = this->left;

                    //procurando o maior dos menores;
                    while (aux->right != nullptr)
                        aux = aux->right;
                }

                //removendo
                old_info = aux->info;
                this->remove(old_info);
                this->info = old_info;
            }

            return true;
        }

        //recursividade
        bool worked;

        if (info > this->info)
            worked = this->right == nullptr ? false : this->right->remove(info);
        else
            worked = this->left == nullptr ? false : this->left->remove(info);

        //rebalance
        this->attHeight();
        this->rebalance();
        return worked;
    }

    /*  getAll: retorna um elemento da arvore a partir da comparaao do elemento com um inteiro, se a igualdade(==) for true, o elemento e retornado
        entrada: valor do index
        retorno: Elemento encontrado, ou nullptr, caso nao seja encontrado nenhum
    */
    T* getByIndex(int index) {
        //caso no encontrado
        if ((this->info) == index && !this->isHeader())
            return &this->info;

        //recursividade
        if ((this->info) < index)
            return (this->right) == nullptr ? nullptr : this->right->getByIndex(index);
        else
            return (this->left) == nullptr ? nullptr : this->left->getByIndex(index);

    }

    /*  getAll: retorna um elemento diferente a cada execucao, varrendo toda arvore, na ordem: no esquerda, no direita, no mae
        entrada: ponteiro que recebera o endereço do ponteiro para o elemento
        retorno: true, se toda a arvore tiver sido varrida, false caso contrario
    */
    bool getAll(T** ref) {
        

        
        if (this->getAllState == 'A') {
            if (this->left != nullptr) {
                if (this->left->getAll(ref))
                    this->getAllState += !this->isHeader() ? 1 : 2;
                return false;
            }else
                this->getAllState++;
        }
        if (this->getAllState == 'B') {
            if (this->right != nullptr) {
                if (this->right->getAll(ref))
                    this->getAllState++;
                return false;
            }else
                this->getAllState++;
            
                
        }
        if (this->isEmpty() || this->getAllState == 'C') {
            if (!this->isHeader())
                *ref = &this->info;
            this->getAllState = 'A';
            return true;
        }

    }

    /*  clean: remove todos os elementos da arvore(libera memoria)
        entrada: nada
        retorno: nada
    */
    void clean() {
        while (!this->isEmpty())
            this->remove(this->right->info);
    }

    //getters

    /*  isEmpty: verifica se a arvore esta vazia ou se e um no folha
        entrada: nada
        retorno: true, se estiver vazia, e false, caso contrario
    */
    bool isEmpty() {
        return this->right == nullptr && this->left == nullptr;
    }

    /*  getHeight: retorna a altura da arvore
        entrada: nada
        retorno: valor da altura
    */
    int getHeight() {
        return this->height - 1;
    }

private:
    //atributes             
    T info;
    char getAllState;   //getAllState é um char para ocupar menos menor memoria por no
    short int height;
    BinaryTree* right;
    BinaryTree* left;
    BinaryTree* mother;

    /*  getHeight: retorna o coeficiente de balanceamento
        entrada: nada
        retorno: valor do coeficiente de balanceamento
    */
    int getBalanceRate() {
        //caso no nulo
        if (this == nullptr)
            return 0;

        //declaracoes locais
        int rH = this->right != nullptr ? this->right->height : 0;
        int lH = this->left != nullptr ? this->left->height : 0;

        return rH - lH;
    }

    /*  isHeader: verifica se e o no cabeça
        entrada: nada
        retorno: true, se for, false, caso contrario
    */
    bool isHeader() {
        return this->mother == nullptr;
    }


    //setters
    /*  attHeight: atualiza a altura da arvore
        entrada: nada
        retorno: nada
    */
    void attHeight() {
        //declaracoes locais
        int rH = this->right != nullptr ? this->right->height : 0;
        int lH = this->left != nullptr ? this->left->height : 0;

        //atualizando altura
        this->height = 1 + (rH + lH + abs(rH - lH)) / 2;
    }

    /*  attHeight: atualiza o ponteiro mae
        entrada: ponteiro do no filho e novo valor do no mae
        retorno: nada
    */
    void setMothersPointer(BinaryTree<T>* son, BinaryTree<T>* new_pointer) {
        (son->mother->info < son->info ? son->mother->right : son->mother->left) = new_pointer;

        //caso no cabeca
        if (son->mother->mother == nullptr)
            (son->mother->info < son->info ? son->mother->left : son->mother->right) = new_pointer;
    }


    //methods
    /* rebalance: rebalanceia a arvore para reduzir a altura da arvore
        entrada: nada
       retorno: true, se for rebalanceada, e false, caso contrario
    */
    bool rebalance() {
        //caso nao precisa de balanceamento
        if (abs(this->getBalanceRate()) < 2)
            return false;

        //calculo para a decisao do algoritmo. 
        int algorithm = this->getBalanceRate() * 2;

        if (abs(this->right == nullptr ? 0 : this->right->getBalanceRate()) > abs(this->left == nullptr ? 0 : this->left->getBalanceRate()))
            algorithm += this->right->getBalanceRate();
        else
            algorithm += this->left->getBalanceRate();

        //rebalanceamento
        BinaryTree* old_root, * new_root;
        old_root = this;

        //caso EE e ED
        if (algorithm < 0) {
            new_root = this->left;

            //ED
            if (algorithm == -3) {
                //adaptacao do caso
                new_root = new_root->right;

                //ajuste adicionais
                old_root->left->right = new_root->right;
                new_root->left = old_root->left;

            }
            old_root->left = new_root->right;
            new_root->right = old_root;

            //caso DD e DE  
        }
        else {
            new_root = this->right;

            //DE
            if (algorithm == 3) {
                //adaptacao do caso
                new_root = new_root->left;

                //ajuste adicionais
                old_root->right->left = new_root->left;
                new_root->right = old_root->right;

            }

            old_root->right = new_root->left;
            new_root->left = old_root;
        }


        //arrumando raiz
        if (new_root->info > old_root->mother->info) {
            old_root->mother->right = new_root;

            //caso no cabeca
            if (old_root->mother->mother == nullptr)
                old_root->mother->left = old_root->mother->right;
        }
        else {
            old_root->mother->left = new_root;

            //caso no cabeca
            if (old_root->mother->mother == nullptr)
                old_root->mother->right = old_root->mother->left;
        }

        //arrumando nos maes
        new_root->mother = old_root->mother;

        if (old_root->right != nullptr)
            old_root->right->mother = old_root;
        if (old_root->left != nullptr)
            old_root->left->mother = old_root;
        if (new_root->right != nullptr)
            new_root->right->mother = new_root;
        if (new_root->left != nullptr)
            new_root->left->mother = new_root;

        this->attHeight();
    }
};