#include "caisse.h"
#include "Article.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <stdexcept>

using namespace std;

vector<Article>& Caisse::getArticles()  { return articles_; }
double           Caisse::getTotalAvantTaxes() { return totalAvantTaxes_; }
unsigned         Caisse::getSize()         { return articles_.size(); }

void Caisse::ajouterArticle(Article& article) {
        if (article.description.size() == 0)
            throw logic_error("Il n'y a aucune description");
        else if (article.prix == 0)
            throw logic_error("Le prix est nul");

        articles_.push_back(article);
        totalAvantTaxes_ += article.prix;
        emit articleAjoute();
}

void Caisse::retirerArticle(Article* article) {
        totalAvantTaxes_ -= article->prix;
        auto it = remove_if(articles_.begin(), articles_.end(), [&] (Article& a) { return &a == article; } );
        articles_.erase(it, articles_.end());
        emit articleRetire();
}

void Caisse::nouvelleCommande() {
    articles_.clear();
    totalAvantTaxes_ = 0.00;
    emit nouvCommande();
}

double Caisse::calculerTotalTaxes(double taux) {
    return transform_reduce(articles_.begin(), articles_.end(), 0.00, plus{}, [taux] (const Article& a) { if(a.taxable) return a.prix * taux; else return 0.00;});
}

double Caisse::calculerTotal(double taux) {
    double taxes = calculerTotalTaxes(taux);
    return totalAvantTaxes_ + taxes;
}




