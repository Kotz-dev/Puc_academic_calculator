//
// Created by Valter on 13/01/2026.
//

#ifndef FILE_CONVERTER_H
#define FILE_CONVERTER_H

#include <QFile>
#include <fstream>
#include <istream>
#include  <QDebug>
#include <ostream>
#include <qurl.h>


class FileVx {

public :
    FileVx();
    static int converteJsonFromFileVX(QString Patch);
};


#endif //FILE_CONVERTER_H