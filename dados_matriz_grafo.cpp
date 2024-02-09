// dados_matriz_grafo.cpp
#include "dados_matriz_grafo.h"


Dados_Matriz_Grafo::Dados_Matriz_Grafo() : peso(0) {
}

void Dados_Matriz_Grafo::setPeso(int peso) {
    this->peso = peso;
}

int Dados_Matriz_Grafo::getPeso() const {
    return peso;
}

QString Dados_Matriz_Grafo::toString() const {
    return QString::number(peso);
}

