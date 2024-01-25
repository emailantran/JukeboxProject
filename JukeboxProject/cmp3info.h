#ifndef CMP3INFO_H
#define CMP3INFO_H

#include <QString>


class CMP3Info
{
public:
    CMP3Info();
    CMP3Info(QString title, QString path);
    QString getTitle();
    QString getPath();
private:
    QString title;
    QString path;

};

#endif // CMP3INFO_H
