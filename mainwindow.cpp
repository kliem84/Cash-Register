#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Article.h"
#include "caisse.h"
#include <iostream>
#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QVariant>
#include <QString>
#include <QMessageBox>
#include <stdexcept>

using namespace std;

Q_DECLARE_METATYPE(Article*);

const double TAUX_TAXES = 0.1475;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&caisse_, SIGNAL(articleAjoute()), this, SLOT(actualiser()));
    connect(&caisse_, SIGNAL(articleRetire()), this, SLOT(actualiser()));
    connect(&caisse_, SIGNAL(nouvCommande()), this, SLOT(actualiser()));

    connect(ui->ajouterArticle, SIGNAL(clicked()), this, SLOT(ajouter()));
    connect(ui->retirerArticle, SIGNAL(clicked()), this, SLOT(retirer()));
    connect(ui->nouvelleCommande, SIGNAL(clicked()), &caisse_, SLOT(nouvelleCommande()));

    ui->Prix->setValidator( new QDoubleValidator(0, 9999, 2, this));

}

void MainWindow::charger() {
    ui->Caisse->clear();
    for (Article& article : caisse_.getArticles())
    {
        QString text = QString::fromStdString(article.description + "\t")
                       + QString::number(article.prix, 'f', 2);
        if (article.taxable)
            text += "\t + Taxes";

        QListWidgetItem* item = new QListWidgetItem(text, ui->Caisse);
        item->setData(Qt::UserRole, QVariant::fromValue<Article*>(&article));
    }
}

void MainWindow::actualiser() {
    ui->retirerArticle->setEnabled(caisse_.getSize() != 0);
    ui->Description->clear();
    ui->Prix->clear();
    ui->Taxable->setCheckState(Qt::Unchecked);

    QString sousTotal = QString::number(caisse_.getTotalAvantTaxes(),'f', 2);
    QString taxes = QString::number(caisse_.calculerTotalTaxes(TAUX_TAXES),'f', 2);
    QString total = QString::number(caisse_.calculerTotal(TAUX_TAXES),'f', 2);

    ui->SousTotal->setText(sousTotal);
    ui->Taxes->setText(taxes);
    ui->Total->setText(total);
    charger();
}


void MainWindow::ajouter() {
    Article article;
    article.description = ui->Description->text().toStdString();
    article.prix = ui->Prix->text().toDouble();
    article.taxable = ui->Taxable->isChecked();

    try {
        caisse_.ajouterArticle(article);
    }
    catch (logic_error& erreur) {
        QMessageBox::critical(0, "Erreur", erreur.what());
    }
}

void MainWindow::retirer() {
    if (caisse_.getSize() != 0) {
        ui->retirerArticle->activateWindow();
        QListWidgetItem* item = ui->Caisse->currentItem();
        Article* ptrArticle = item->data(Qt::UserRole).value<Article*>();
        caisse_.retirerArticle(ptrArticle);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

