/**
 * Итоговая программа «Индексатор»: QSettings (INI) + SearchDatabase + TextIndex.
 */

#include "SearchDatabase.h"
#include "TextIndex.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QHash>
#include <QSet>
#include <QSettings>
#include <QStringList>
#include <QTextStream>
#include <QStringConverter>

namespace {

QStringList splitCommaList(const QString &raw)
{
    QStringList list;
    for (const QString &part : raw.split(QLatin1Char(','), Qt::SkipEmptyParts)) {
        const QString t = part.trimmed();
        if (!t.isEmpty())
            list.append(t);
    }
    return list;
}

QSet<QString> parseExtensions(const QString &raw)
{
    QSet<QString> exts;
    for (const QString &part : raw.split(QLatin1Char(','), Qt::SkipEmptyParts)) {
        QString e = part.trimmed().toLower();
        if (e.isEmpty())
            continue;
        if (!e.startsWith(QLatin1Char('.')))
            e.prepend(QLatin1Char('.'));
        exts.insert(e);
    }
    return exts;
}

} // namespace

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("Indexer"));
    QCoreApplication::setOrganizationName(QStringLiteral("NetologyDiplom"));

    const QString iniPath = QCoreApplication::applicationDirPath() + QStringLiteral("/indexer.ini");
    if (!QFile::exists(iniPath)) {
        qWarning() << "Не найден indexer.ini:" << iniPath;
        qWarning() << "Скопируйте indexer.ini.example и заполните [Paths] и [Database].";
        return 1;
    }

    QSettings settings(iniPath, QSettings::IniFormat);
    settings.sync();
    if (settings.status() != QSettings::NoError) {
        qWarning() << "Ошибка чтения indexer.ini";
        return 1;
    }

    const QString rootsRaw = settings.value(QStringLiteral("Paths/roots")).toString();
    const QString extRaw = settings.value(QStringLiteral("Paths/extensions")).toString();
    const QStringList roots = splitCommaList(rootsRaw);
    const QSet<QString> extensions = parseExtensions(extRaw);

    if (roots.isEmpty()) {
        qWarning() << "В секции [Paths] укажите roots (каталоги через запятую).";
        return 1;
    }
    if (extensions.isEmpty()) {
        qWarning() << "В секции [Paths] укажите extensions, например: txt,md,ini,csv";
        return 1;
    }

    SearchDatabase db(QStringLiteral("indexer_conn"));
    if (!db.openFromIni(iniPath)) {
        qWarning() << "Не удалось подключиться к БД.";
        return 1;
    }

    if (!db.createTables())
        return 1;

    qInfo() << "Очистка старых данных и новая индексация...";
    if (!db.truncateAll())
        return 1;

    int filesProcessed = 0;
    for (const QString &root : roots) {
        const QDir dir(root);
        if (!dir.exists()) {
            qWarning() << "Каталог не существует:" << root;
            continue;
        }

        QDirIterator it(root, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            const QFileInfo fi = it.fileInfo();
            const QString suffix = QStringLiteral(".%1").arg(fi.suffix().toLower());
            if (!extensions.contains(suffix))
                continue;

            QFile f(fi.absoluteFilePath());
            if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qWarning() << "Не открыть файл:" << fi.absoluteFilePath();
                continue;
            }
            QTextStream stream(&f);
            stream.setEncoding(QStringConverter::Utf8);
            const QString content = stream.readAll();
            f.close();

            const QHash<QString, int> freq = TextIndex::countWordsInText(content);
            if (freq.isEmpty())
                continue;

            if (db.saveIndexedDocument(fi.absoluteFilePath(), freq))
                ++filesProcessed;
        }
    }

    qInfo() << "Готово. Проиндексировано файлов (с непустым набором слов):" << filesProcessed;
    return 0;
}
