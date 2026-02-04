#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>

class Logger
{
public:
    Logger();
    ~Logger();
    void WriteLine(QString text);
    // ------------------ //
    bool m_isrunning = true;

private:
    QString m_dir;
    QString m_path;
    QFile m_file;
};

#endif // LOGGER_H
