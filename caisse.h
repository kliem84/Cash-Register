#pragma once

#include "Article.h"
#include <QObject>
#include <iostream>
#include <vector>

using namespace std;

class Caisse : public QObject
{
    Q_OBJECT

public:
    vector<Article>& getArticles();
    double getTotalAvantTaxes();
    unsigned getSize();
public slots:
    void ajouterArticle(Article& article);
    void retirerArticle(Article* article);
    double calculerTotalTaxes(double taux);
    double calculerTotal(double taux);
    void nouvelleCommande();
signals:
    void articleAjoute();
    void articleRetire();
    void nouvCommande();
private:
    vector<Article> articles_;
    double totalAvantTaxes_ = 0.00;
};

