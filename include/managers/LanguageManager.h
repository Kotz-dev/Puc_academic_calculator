#ifndef LANGUAGE_MANAGER_H
#define LANGUAGE_MANAGER_H

#include <vector>
#include <filesystem>

#include "JsonParser.h"
#include <GlobalAccess.h>

enum LAGUAGEM {
    Portugueses = 0,
    English = 1
};



class LanguageManager : JsonParser {
private :
     static QString Language;
     static QString  Languagem();
public :
    static void initialize_language();
    static void TraduzirMainWindow();
    static void TraduzirPrencesWindow();
    static LAGUAGEM getLanguage();

};

#endif //LANGUAGE_MANAGER_H