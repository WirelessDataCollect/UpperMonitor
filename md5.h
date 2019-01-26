#ifndef MD5_H
#define MD5_H
#include   <stdio.h>
#include   <stdlib.h>
#include   <time.h>
#include   <string.h>
#include <QByteArray>
void   MD5Digest(char   *pszInput,   unsigned   long   nInputSize,   char   *pszOutPut);
QByteArray MD5Process(QString SALT, QString PASSWD);

#endif // MD5_H
