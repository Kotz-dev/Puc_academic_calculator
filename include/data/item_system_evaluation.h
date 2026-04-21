//
// Created by KoTz on 20/04/2026.
//

#ifndef PUCSIMULATOR_ITEM_SYSTEM_EVALUATION_H
#define PUCSIMULATOR_ITEM_SYSTEM_EVALUATION_H

#include <QPixmap>
#include <QString>

#pragma once
#include <QString>
#include <QPixmap>
#include <windows/system_evaluation.h>

class ITEM {
private:
    QString nome_universidade;
    QString list_nome_universidade;
    QPixmap logo_universidade;
    bool    is_selected;
    int     nota_minima;
    int     nota_minima_final;
    int     frequencia_minima;
    QString formula_da_media;
    bool    is_apply;

public:
    ITEM();

    ITEM(QPixmap logo,QString list_nome,QString Nome_unviversade);


    void setListNomeUniversidade(QString nome);

    void setNomeUniversidade(const QString &nome);
    void setLogoUniversidade(const QPixmap &logo);
    void setIsSelected(bool selected);
    void setNotaMinima(int nota);
    void setNotaMinimaFinal(int nota);
    void setFrequenciaMinima(int frequencia);
    void setFormulaDaMedia(const QString &formula);
    void setIsApply(bool apply);

    QString getNomeUniversidade()  const;
    QPixmap getLogoUniversidade()  const;
    bool    getIsSelected()        const;
    int     getNotaMinima()        const;
    int     getNotaMinimaFinal()   const;
    int     getFrequenciaMinima()  const;
    QString getFormulaDaMedia()    const;
    bool    getIsApply()           const;
    QString getListNomeUniversidade() const;
};


#endif //PUCSIMULATOR_ITEM_SYSTEM_EVALUATION_H
