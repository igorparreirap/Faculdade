#ifndef GRAFO_POR_MATRIZ_DE_ADJACENCIA_H
#define GRAFO_POR_MATRIZ_DE_ADJACENCIA_H

#include "matriz.h"
#include "dados_matriz_grafo.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>


template <class TipoDeDadosMatriz>
class GrafoPorMatriz {
private:
    Matriz<TipoDeDadosMatriz> matrizAdjacencia;

public:
    GrafoPorMatriz(int numVertices);
    void carregarDados(QString nomeArquivo);
    void inserirVerticeBidirecional(int vertice1, int vertice2, int peso);
    void removerConexaoBidirecional(int vertice1, int vertice2);
    void alterarConexaoBidirecional(int vertice1, int vertice2, TipoDeDadosMatriz novaConexao);
    TipoDeDadosMatriz obterElementoMatriz(int linha, int coluna) const;
    void redimensionarMatriz(int numRows, int numCols);
    int obterQuantidadeVertices() const;

private:
    void ajustarDimensoesArquivo(QString nomeArquivo);
};

template <class TipoDeDadosMatriz>
GrafoPorMatriz<TipoDeDadosMatriz>::GrafoPorMatriz(int numVertices) : matrizAdjacencia(numVertices, numVertices) {
}


template <class TipoDeDadosMatriz>
void GrafoPorMatriz<TipoDeDadosMatriz>::ajustarDimensoesArquivo(QString nomeArquivo) {
    try {
        QString diretorio = "/Users/Lucas/OneDrive/Área de Trabalho/Faculdade/Grafo_Matriz";
        QDir dir(diretorio);

        if (!dir.exists()) {
            qDebug() << "O diretório especificado não existe.";
            return;
        }

        nomeArquivo = diretorio + "MatrizDeAdjacencia.txt";

        QFile file(nomeArquivo);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            throw std::runtime_error("Não foi possível abrir o arquivo");
        }

        QTextStream in(&file);

        int numRows, numCols;
        if (!in.atEnd()) {
            QString primeiraLinha = in.readLine();
            QStringList primeiraLinhaLista = primeiraLinha.split("\t", Qt::SkipEmptyParts);
            numRows = primeiraLinhaLista.size();
            numCols = numRows;  // Considerando uma matriz quadrada

            // Adiciona novas linhas e colunas, se necessário
            if (numRows > matrizAdjacencia.obterQuantidadeLinhas() || numCols > matrizAdjacencia.obterQuantidadeColunas()) {
                matrizAdjacencia.redimensionarMatriz(numRows, numCols);
            }

            in.seek(0);  // Volta para o início do arquivo para ler desde o início
        }

        int i = 0;
        while (!in.atEnd()) {
            QString linha = in.readLine();
            QStringList lista = linha.split("\t", Qt::SkipEmptyParts);

            for (int j = 0; j < lista.size(); j++) {
                // Converta para int - ajuste conforme necessário
                bool isConexaoValid;
                int conexao = lista[j].toInt(&isConexaoValid);

                if (isConexaoValid) {
                    TipoDeDadosMatriz dadosMatrizGrafo;
                    dadosMatrizGrafo.setPeso(conexao);
                    matrizAdjacencia.definirElemento(i, j, dadosMatrizGrafo);
                }
            }
            i++;
        }

        file.close();
    } catch (const std::exception &e) {
        qDebug() << "Erro ao carregar dados: " << e.what();
    }
}

template <class TipoDeDadosMatriz>
void GrafoPorMatriz<TipoDeDadosMatriz>::carregarDados(QString nomeArquivo) {
    try {
        ajustarDimensoesArquivo(nomeArquivo);

        QFile file(nomeArquivo);
        QTextStream in(&file);

        int i = 0;
        while (!in.atEnd()) {
            QString linha = in.readLine();
            QStringList lista = linha.split(" ");

            for (int j = 0; j < lista.size(); j++) {
                // Converta para int - ajuste conforme necessário
                bool isConexaoValid;
                int conexao = lista[j].toInt(&isConexaoValid);

                if (isConexaoValid) {
                    TipoDeDadosMatriz dadosMatrizGrafo;
                    dadosMatrizGrafo.setPeso(conexao);
                    matrizAdjacencia.definirElemento(i, j, dadosMatrizGrafo);
                }
            }
            i++;
        }

        file.close();
    } catch (const std::exception &e) {
        qDebug() << "Erro ao carregar dados: " << e.what();
    }
}

template <class TipoDeDadosMatriz>
void GrafoPorMatriz<TipoDeDadosMatriz>::inserirVerticeBidirecional(int vertice1, int vertice2, int peso) {
    try {
        // Verifica se a conexão já existe
        if (matrizAdjacencia.obterElemento(vertice1 - 1, vertice2 - 1).getPeso() >= 1 ||
            matrizAdjacencia.obterElemento(vertice2 - 1, vertice1 - 1).getPeso() >= 1) {
            QMessageBox::critical(nullptr, "Erro", "Conexão já existente, por favor altere o vertice de origem ou de destino");
            return;  // Adiciona um return para evitar a execução do código restante
        }

        // Cria um objeto Dados_Matriz_Grafo com o peso especificado
        TipoDeDadosMatriz valorConexao;
        valorConexao.setPeso(peso);  // Use o método apropriado para definir o valor desejado

        // Atualiza a matriz de adjacência para indicar a conexão bidirecional
        matrizAdjacencia.definirElemento(vertice1-1, vertice2-1 , valorConexao);
        matrizAdjacencia.definirElemento(vertice2-1, vertice1-1, valorConexao);
    } catch (const std::exception &e) {
        qDebug() << "Erro ao inserir conexão bidirecional: " << e.what();
    }
}

template <class TipoDeDadosMatriz>
void GrafoPorMatriz<TipoDeDadosMatriz>::removerConexaoBidirecional(int vertice1, int vertice2) {
    try {
        // Verifica se a conexão não existe
        if (matrizAdjacencia.obterElemento(vertice1 - 1, vertice2 - 1).getPeso() == 0 &&
            matrizAdjacencia.obterElemento(vertice2 - 1, vertice1 - 1).getPeso() == 0) {
            QMessageBox::critical(nullptr, "Erro", "Nenhuma conexão com esses dados foi encontrada, por favor trabalhe apenas com as conexões que existem");
            return;
        }

        // Remove a conexão bidirecional da matriz de adjacência
        TipoDeDadosMatriz valorZero;
        valorZero.setPeso(0);
        matrizAdjacencia.definirElemento(vertice1-1, vertice2-1, valorZero);
        matrizAdjacencia.definirElemento(vertice2-1, vertice1-1, valorZero);
    } catch (const std::exception &e) {
        qDebug() << "Erro ao remover conexão bidirecional: " << e.what();
    }
}

template <class TipoDeDadosMatriz>
void GrafoPorMatriz<TipoDeDadosMatriz>::alterarConexaoBidirecional(int vertice1, int vertice2, TipoDeDadosMatriz novaConexao) {
    try {
        // Verifica se a conexão não existe
        if (matrizAdjacencia.obterElemento(vertice1 - 1, vertice2 - 1).getPeso() == 0 &&
            matrizAdjacencia.obterElemento(vertice2 - 1, vertice1 - 1).getPeso() == 0) {
            QMessageBox::critical(nullptr, "Erro", "Nenhuma conexão com esses dados foi encontrada, por favor trabalhe apenas com as conexões que existem");
            return;
        }

        // Altera a conexão bidirecional na matriz de adjacência
        matrizAdjacencia.definirElemento(vertice1 - 1, vertice2 - 1, novaConexao);
        matrizAdjacencia.definirElemento(vertice2 - 1, vertice1 - 1, novaConexao);
    } catch (const std::exception &e) {
        qDebug() << "Erro ao alterar conexão bidirecional: " << e.what();
    }
}

template <class TipoDeDadosMatriz>
TipoDeDadosMatriz GrafoPorMatriz<TipoDeDadosMatriz>::obterElementoMatriz(int linha, int coluna) const {
    return matrizAdjacencia.obterElemento(linha, coluna);
}

template <class TipoDeDadosMatriz>
void GrafoPorMatriz<TipoDeDadosMatriz>::redimensionarMatriz(int numRows, int numCols) {
    matrizAdjacencia.redimensionarMatriz(numRows, numCols);
}

template <class TipoDeDadosMatriz>
int GrafoPorMatriz<TipoDeDadosMatriz>::obterQuantidadeVertices() const {
    return matrizAdjacencia.obterQuantidadeLinhas();
}


#endif // GRAFO_POR_MATRIZ_DE_ADJACENCIA_H
