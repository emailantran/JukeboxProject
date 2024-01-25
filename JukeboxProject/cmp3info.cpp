#include "cmp3info.h"

CMP3Info::CMP3Info()
{
    this->title = nullptr;
    this->path = nullptr;
}

CMP3Info::CMP3Info(QString title, QString path)
{
    this->title = title;
    this->path = path;
}

QString CMP3Info::getPath() {
    return path;
}

QString CMP3Info::getTitle() {
    return title;
}
