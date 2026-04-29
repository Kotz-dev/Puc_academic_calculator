//
// Created by KoTz on 20/04/2026.
//

#include "item_system_evaluation.h"

ITEM::ITEM(QPixmap logo, QString list_nome, QString Nome_universidade) {
    this->logo_universidade      = logo;
    this->list_nome_universidade = list_nome;
    this->nome_universidade      = Nome_universidade;
}

ITEM::ITEM(const QString &logoPath, const QString &list_nome, const QString &Nome_universidade, int frequencia)
    : logo_universidade(logoPath),
      list_nome_universidade(list_nome),
      nome_universidade(Nome_universidade),
      is_selected(false),
      nota_minima(0),
      nota_minima_final(0),
      frequencia_minima(frequencia),
      is_apply(false) {}

ITEM::ITEM()
    : is_selected(false),
      nota_minima(0),
      nota_minima_final(0),
      frequencia_minima(0),
      is_apply(false) {}

void ITEM::setNomeUniversidade(const QString &nome) {
    nome_universidade = nome;
}
void ITEM::setLogoUniversidade(const QPixmap &logo) {
    logo_universidade = logo;
}
void ITEM::setIsSelected(bool selected) {
    is_selected       = selected;
}
void ITEM::setNotaMinima(int nota) {
    nota_minima       = nota;
}
void ITEM::setNotaMinimaFinal(int nota) {
    nota_minima_final = nota;
}
void ITEM::setFrequenciaMinima(int frequencia) {
    frequencia_minima = frequencia;
}
void ITEM::setFormulaDaMedia(const QString &formula) {
    formula_da_media  = formula;
}
void ITEM::setIsApply(bool apply) {
    is_apply          = apply;
}

QString ITEM::getNomeUniversidade()  const {
    return nome_universidade;
}
QPixmap ITEM::getLogoUniversidade()  const {
    return logo_universidade;
}
bool    ITEM::getIsSelected()        const {
    return is_selected;
}
int     ITEM::getNotaMinima()        const {
    return nota_minima;
}
int     ITEM::getNotaMinimaFinal()   const {
    return nota_minima_final;
}
int     ITEM::getFrequenciaMinima()  const {
    return frequencia_minima;
}
QString ITEM::getFormulaDaMedia()    const {
    return formula_da_media;
}
bool    ITEM::getIsApply()           const {
    return is_apply;
}
QString ITEM::getListNomeUniversidade() const {
    return this->list_nome_universidade;
}

void ITEM::setListNomeUniversidade(QString nome) {
    this->list_nome_universidade = nome;
}