#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <stdexcept>
#include <QDebug>

template <class T>
class Matriz {
private:
    std::vector<T> dados;
    int numLinhas;
    int numColunas;

public:
    Matriz(int numLinhas, int numColunas);

    T obterElemento(int linha, int coluna) const;
    void definirElemento(int linha, int coluna, T valor);

    int obterQuantidadeLinhas() const;
    int obterQuantidadeColunas() const;

    void redimensionarMatriz(int numLinhas, int numColunas);
};

template <class T>
Matriz<T>::Matriz(int numLinhas, int numColunas) : numLinhas(numLinhas), numColunas(numColunas) {
    dados.resize(numLinhas * numColunas);
}

template <class T>
T Matriz<T>::obterElemento(int linha, int coluna) const {
    try {
        if (linha < 0 || linha >= numLinhas || coluna < 0 || coluna >= numColunas) {
            qDebug()<<"Índices fora do intervalo da matriz .";
        }

        return dados.at(linha * numColunas + coluna);
    } catch (const std::out_of_range&) {
        // Tratamento personalizado para índices fora do intervalo
        qDebug()<<"Índices fora do intervalo da matriz .";
    }
}

template <class T>
void Matriz<T>::definirElemento(int linha, int coluna, T valor) {
    try {
        if (linha < 0 || linha >= numLinhas || coluna < 0 || coluna >= numColunas) {
            qDebug()<<"Índices fora do intervalo da matriz .";
        }

        dados.at(linha * numColunas + coluna) = valor;
    } catch (const std::out_of_range&) {
        // Tratamento personalizado para índices fora do intervalo
        qDebug()<<"Índices fora do intervalo da matriz .";
    }
}

template <class T>
int Matriz<T>::obterQuantidadeLinhas() const {
    return numLinhas;
}

template <class T>
int Matriz<T>::obterQuantidadeColunas() const {
    return numColunas;
}

template <class T>
void Matriz<T>::redimensionarMatriz(int numLinhas, int numColunas) {
    try {
        std::vector<T> novaMatriz(numLinhas * numColunas, T());  // Cria uma nova matriz com o novo tamanho

        // Copia os elementos existentes para a nova matriz
        for (int i = 0; i < std::min(numLinhas, this->numLinhas); ++i) {
            for (int j = 0; j < std::min(numColunas, this->numColunas); ++j) {
                novaMatriz[i * numColunas + j] = obterElemento(i, j);
            }
        }

        // Substitui a matriz existente pela nova matriz
        dados = novaMatriz;

        this->numLinhas = numLinhas;
        this->numColunas = numColunas;
    } catch (const std::bad_alloc&) {
        // Tratamento personalizado para falha na alocação de memória
        qDebug()<<"Falha na alocação de memória ao redimensionar a matriz.";
    }
}

#endif // MATRIZ_H
