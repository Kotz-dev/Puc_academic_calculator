//
// Created by KoTz on 20/11/2025.
//

#ifndef ERROR_LOG_H
#define ERROR_LOG_H

#include <QString>


class DATA {
public :
     QString nome;
     QString erro;
     QString mensagem;
};
class DataInfoLog {
private :
    DATA data;
public :
    void DataErroJson(DATA data_ptr);
    QString GetMensagemErro();
    DataInfoLog();
};


#endif //ERROR_LOG_H