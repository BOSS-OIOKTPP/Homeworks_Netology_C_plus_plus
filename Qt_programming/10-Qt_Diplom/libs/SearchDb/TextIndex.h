#pragma once

#include <QHash>
#include <QString>

/**
 * Разбор текста для индексации (как в задании диплома Qt):
 * нижний регистр, только «слова», длина 3–32 символа.
 */
namespace TextIndex {

QHash<QString, int> countWordsInText(const QString &text);

} // namespace TextIndex
