#include "TextIndex.h"

#include <QRegularExpression>

namespace TextIndex {

namespace {
constexpr int kMinWordLen = 3;
constexpr int kMaxWordLen = 32;
}

QHash<QString, int> countWordsInText(const QString &text)
{
    QHash<QString, int> freq;
    QString lower = text.toLower();

    static const QRegularExpression nonWord(QStringLiteral("[^\\p{L}\\p{N}]+"));
    lower.replace(nonWord, QStringLiteral(" "));

    const QStringList parts = lower.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    for (QString w : parts) {
        w = w.trimmed();
        const int len = w.length();
        if (len < kMinWordLen || len > kMaxWordLen)
            continue;
        freq[w] = freq.value(w, 0) + 1;
    }
    return freq;
}

} // namespace TextIndex
