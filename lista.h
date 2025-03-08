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
    lista.inicio = nullptr;
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
int numeroDeElementos(Lista<T>& lista){
    return lista.cardinalidade;
}

template<typename T>
bool existeElemento(Lista<T> &lista, T elem){
    Nodo<T> *atual = lista.inicio;
    while (atual)
    {
        if (atual->valor == elem)
            return true;
        
        atual = atual->proximo;
    }
    return false;
}

template<typename T>
bool existePosicao(Lista<T>&lista, int pos){
    return ((pos > 0) && (pos < lista.cardinalidade + 1));
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
int retornaPosicao(Lista<T>& lista, T elem){
    if (!existeElemento(lista, elem))
    {
        throw "ELEMENTO NAO EXISTE NA LISTA.";
    }
    

    Nodo<T> *atual = lista.inicio;
    int cont = 1;
    while (atual)
    {
        if (atual->valor == elem)
            return cont;
        
        atual = atual->proximo;
        cont++;
    }
    
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

#endif