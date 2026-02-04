#include "logger.h"
#include <QDateTime>

Logger::Logger() : m_dir(QCoreApplication::applicationDirPath()),m_path(QDir(m_dir).filePath("RyomaResourceMonitor.log")),m_file(m_path)
{
    if (!m_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Failed to open log file:" << m_path << m_file.errorString();
        m_isrunning = false;
    }
}

Logger::~Logger()
{

}

void Logger::WriteLine(QString text)
{
    if (!m_file.isOpen()) {
        if (!m_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            m_isrunning = false;
            qWarning() << "Failed to open log file:" << m_path << m_file.errorString();
            return;
        }
    }

    m_isrunning = true;

    QTextStream out(&m_file);
    out <<  QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz ") << text << "\n";
    out.flush();
}
