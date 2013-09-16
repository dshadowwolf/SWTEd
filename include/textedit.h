#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class QWidget;
class QTextCharFormat;

class TextEdit: public QTextEdit {
  Q_OBJECT

  public:
    TextEdit( QWidget *parent=0 );
  
  private slots: 
    void Bold();
    void Italic();
    void Underline();
    void Super();
    void Sub();
    void align_left();
    void align_right();
    void align_center();
    void align_just();

  private:
    QTextCharFormat currentFormat();
};

#endif // !defined TEXTEDIT_H
