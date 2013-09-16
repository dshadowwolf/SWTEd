#ifndef WT_HIGHLIGHT_HPP
#define WT_HIGHLIGHT_HPP

#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>

class QTextDocument;

class WolfTechEdit:public QSyntaxHighlighter {
  Q_OBJECT

  public:
    WolfTechEdit(QTextDocument *parent = 0);

  protected:
    void highlightBlock(const QString &text);

  private:
    struct highlight_rule {
      QRegExp pattern;
      QTextCharFormat format;
    };

    QVector<highlight_rule> highlightingRules;

    QRegExp commentStartExp;
    QRegExp commentEndExp;

    QTextCharFormat commentFormat;
};
#endif
