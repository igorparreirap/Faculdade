#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), grafo(6)
{
    ui->setupUi(this);

    QString nomeArquivo = "/Users/Lucas/OneDrive/Área de Trabalho/Faculdade/Grafo_Matriz/MatrizDeAdjacencia.txt";
                          grafo.carregarDados(nomeArquivo);

    // Configuração do número de linhas e colunas reais da matriz
    int numRowsActual = grafo.obterQuantidadeVertices();
    int numColsActual = grafo.obterQuantidadeVertices();

    // Define o número de linhas e colunas na tabela
    ui->matriz->setRowCount(numRowsActual);
    ui->matriz->setColumnCount(numColsActual);

    // Certifique-se de que o tamanho padrão de seção não seja zero para evitar divisão por zero
    int sectionHeight = std::max(1, ui->matriz->height() / numRowsActual);
    int sectionWidth = std::max(1, ui->matriz->width() / numColsActual);

    ui->matriz->verticalHeader()->setDefaultSectionSize(sectionHeight);
    ui->matriz->horizontalHeader()->setDefaultSectionSize(sectionWidth);

    // Preencher a tabela com os dados carregados
    preencherMatrizNaTabela();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_tamanhoDaMatriz_clicked() {
    try {
        int tamanhoGrafo = ui->tamanho->text().toInt();

        if (tamanhoGrafo <= 0) {
            throw std::runtime_error("Tamanho inválido. Insira um valor maior que zero.");
        }

        grafo.redimensionarMatriz(tamanhoGrafo, tamanhoGrafo);

        // Configuração do número de linhas e colunas reais da matriz
        int numRowsActual = grafo.obterQuantidadeVertices();
        int numColsActual = grafo.obterQuantidadeVertices();

        // Limpa a tabela
        ui->matriz->clear();

        // Define o número de linhas e colunas na tabela
        ui->matriz->setRowCount(numRowsActual);
        ui->matriz->setColumnCount(numColsActual);

        // Certifique-se de que o tamanho padrão de seção não seja zero para evitar divisão por zero
        int sectionHeight = std::max(1, ui->matriz->height() / numRowsActual);
        int sectionWidth = std::max(1, ui->matriz->width() / numColsActual);

        ui->matriz->verticalHeader()->setDefaultSectionSize(sectionHeight);
        ui->matriz->horizontalHeader()->setDefaultSectionSize(sectionWidth);

        preencherMatrizNaTabela();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Erro", e.what());
    }
}


void MainWindow::preencherMatrizNaTabela() {
    // Configuração do número de linhas e colunas reais da matriz
    int numRows = grafo.obterQuantidadeVertices();
    int numCols = grafo.obterQuantidadeVertices();

    // Define o número de linhas e colunas na tabela
    ui->matriz->setRowCount(numRows);
    ui->matriz->setColumnCount(numCols);

    // Configura os cabeçalhos
    ui->matriz->verticalHeader()->setDefaultSectionSize(ui->matriz->height() / numRows);
    ui->matriz->horizontalHeader()->setDefaultSectionSize(ui->matriz->width() / numCols);

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            Dados_Matriz_Grafo elemento = grafo.obterElementoMatriz(i, j);
            QString elementoStr = (elemento.getPeso() > 0) ? QString::number(elemento.getPeso()) : ".";
            QTableWidgetItem *item = new QTableWidgetItem(elementoStr);

            // Define o item apenas para as células correspondentes aos dados reais da matriz
            ui->matriz->setItem(i, j, item);
        }
    }
}

void MainWindow::on_Inserir_clicked()
{
    try {
        int vertice1 = ui->VerticeO->text().toInt();
        int vertice2 = ui->VerticeD->text().toInt();
        int peso = ui->Peso->text().toInt();

        if (vertice1 <= 0 || vertice2 <= 0 || peso <= 0) {
            throw std::runtime_error("Espaços vazios, por favor informar o vertice de origem, o vertice de destino e o peso");
        }
        if (vertice1 <= 0 || vertice2 <= 0 || peso <= 0 ||
            vertice1 > grafo.obterQuantidadeVertices() || vertice2 > grafo.obterQuantidadeVertices()) {
            throw std::runtime_error("Vértices inválidos, por favor informar vértices dentro dos limites da matriz");
        }



        // Chama a função de inserção bidirecional no grafo
        grafo.inserirVerticeBidirecional(vertice1, vertice2, peso);

        // Atualiza a exibição da matriz na tabela
        preencherMatrizNaTabela();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Erro", e.what());
    }
}

void MainWindow::on_Remover_clicked()
{
    try {
        int vertice1 = ui->VerticeO->text().toInt();
        int vertice2 = ui->VerticeD->text().toInt();

        if (vertice1 <= 0 || vertice2 <= 0) {
            throw std::runtime_error("Espaços vazios, por favor informar o vertice de origem e o vertice de destino");
        }

        // Chama a função de remoção bidirecional no grafo
        grafo.removerConexaoBidirecional(vertice1, vertice2);

        // Atualiza a exibição da matriz na tabela
        preencherMatrizNaTabela();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Erro", e.what());
    }
}

void MainWindow::on_Alterar_clicked()
{
    try {
        int vertice1 = ui->VerticeO->text().toInt();
        int vertice2 = ui->VerticeD->text().toInt();
        int novoPeso = ui->Peso->text().toInt();

        if (vertice1 <= 0 || vertice2 <= 0 || novoPeso <= 0) {
            throw std::runtime_error("Espaços vazios, por favor informar o vertice de origem, o vertice de destino e o novo peso");
        }

        // Cria um objeto Dados_Matriz_Grafo com o novo peso especificado
        Dados_Matriz_Grafo novoDado;
        novoDado.setPeso(novoPeso);

        // Chama a função de alteração bidirecional no grafo
        grafo.alterarConexaoBidirecional(vertice1, vertice2, novoDado);

        // Atualiza a exibição da matriz na tabela
        preencherMatrizNaTabela();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Erro", e.what());
    }
}
