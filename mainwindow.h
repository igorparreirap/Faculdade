// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "grafo_por_matriz_de_adjacencia.h"
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tamanhoDaMatriz_clicked();

    void on_Inserir_clicked();

    void on_Remover_clicked();

    void on_Alterar_clicked();

private:
    Ui::MainWindow *ui;
    GrafoPorMatriz<Dados_Matriz_Grafo> grafo;

    void preencherMatrizNaTabela();
};

#endif // MAINWINDOW_H
