#ifndef DADOS_MATRIZ_GRAFO_H
#define DADOS_MATRIZ_GRAFO_H

#include <QString>


class Dados_Matriz_Grafo {
private:
    int peso;

public:
    Dados_Matriz_Grafo();
    void setPeso(int peso);
    int getPeso() const;
    QString toString() const;

};

#endif // DADOS_MATRIZ_GRAFO_H
