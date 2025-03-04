#ifndef LISTAGENERICA_H_INCLUDED
#define LISTAGENERICA_H_INCLUDED

template<typename T>
struct Nodo
{
    T valor;
    Nodo<T> *proximo;
    Nodo<T> *anterior;
};

template<typename T>
struct Lista
{
    int cardinalidade;
    Nodo<T> *inicio;
};

template<typename T>
void cria(Lista<T> &lista){
    lista.cardinalidade = 0;
}

template<typename T>
void destroi(Lista<T> &lista){
    Nodo<T> *aux;
    for (int i = 1; i <= lista.cardinalidade; i++)
    {
        aux = lista.inicio;
        if (lista.inicio->proximo)
            lista.inicio = lista.inicio->proximo;
        
        delete aux;
    }
    lista.cardinalidade = 0;
}

template<typename T>
bool ehVazia(Lista<T> &lista){
    return lista.cardinalidade == 0;
}

template<typename T>
T retornaElemento(Lista<T> &lista, int pos){
    if (pos < 1 || pos > lista.cardinalidade)
    {
        throw "POSICAO INVALIDA";
    }
    Nodo<T> *aux = lista.inicio;

    for (int i = 1; i < pos; i++)
    {
        aux = aux->proximo;
    }

    return aux->valor;
}

template<typename T>
Nodo<T> *retornaNodo(Lista<T> &lista, int pos){
    if (pos < 1 || pos > lista.cardinalidade)
    {
        throw "POSICAO INVALIDA";
    }
    Nodo<T> *aux = lista.inicio;

    for (int i = 1; i < pos; i++)
    {
        aux = aux->proximo;
    }

    return aux;    
}

template<typename T>
bool temElemento(Lista<T> &lista, T elem){
    Nodo<T> *aux = lista.inicio;
    for (int i = 1; i < lista.cardinalidade; i++)
    {
        if (aux->valor == elem)
        {
            return true;
        }
        
        aux = aux->proximo;
    }
    return false;
}

template<typename T>
void trocarPosicao(Lista<T> &lista, int posCarta1, int posCarta2){
    Nodo<T> *carta1 = retornaNodo(lista, posCarta1);
    Nodo<T> *carta2 = retornaNodo(lista, posCarta2);

    T aux;
    aux = carta1->valor;
    carta1->valor = carta2->valor;
    carta2->valor = aux;
}

template<typename T>
void insere(Lista<T> &lista, T elem, int pos){
    Nodo<T> *novo = new Nodo<T>;
    novo->valor = elem;
    novo->anterior = nullptr;
    novo->proximo = nullptr;

    if (pos < 1 || pos > lista.cardinalidade + 1)
    {
        throw "POSICAO INVALIDA";
    }

    if (ehVazia(lista))
    {
        lista.inicio = novo;
    }else {
        if (pos == 1)
        {
            novo->proximo = lista.inicio;
            lista.inicio->anterior = novo;
            lista.inicio = novo;
        } else{
            Nodo<T> *ant = lista.inicio;

            for (int i = 1; i < pos - 1; i++)
            {
                ant = ant->proximo;
            }
            novo->proximo = ant->proximo;
            novo->anterior = ant;
            if (ant->proximo) ant->proximo->anterior = novo;
            ant->proximo = novo;
        }
        
    }
    lista.cardinalidade++;
}

template<typename T>
void retira(Lista<T> &lista, int pos){
    if (ehVazia(lista))
    {
        throw "UNDERFLOW";
    }
    if (pos < 1 || pos > lista.cardinalidade)
    {
        throw "POSICAO INVALIDA";
    }

    Nodo<T> *atual = lista.inicio;
    
    if (pos == 1)
    {
        lista.inicio = lista.inicio->proximo;
        if (lista.inicio) lista.inicio->anterior = nullptr;
    }else {
        for (int i = 1; i < pos; i++)
        {
            atual = atual->proximo;
        }
        atual->anterior->proximo = atual->proximo;
        if (atual->proximo) atual->proximo->anterior = atual->anterior;
    }
    delete atual;
    lista.cardinalidade--;
}

template<typename T>
void mostra(Lista<T> &lista){
    Nodo<T> *aux = lista.inicio;
    std::cout << "[";
    while (aux)
    {
        std::cout << " " << aux->valor;
        (aux->proximo) ? std::cout << "," : std::cout << " ";
        aux = aux->proximo;
        
    }
    std::cout << "]";
}

#endif