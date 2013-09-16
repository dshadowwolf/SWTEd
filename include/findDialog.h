#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QTextDocument>

class QLabel;
class QCheckBox;
class QPushButton;
class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QLineEdit;

class FindDialog: public QDialog {
  Q_OBJECT
public:
  FindDialog( QWidget *parent = 0 );
  const QTextDocument::FindFlags flags();
  const QString terms();

private:
  QLabel      *label;
  QLineEdit   *lineEdit;
  QCheckBox   *boxes[3];
  QPushButton *buttons[2];
  QVBoxLayout *vblayout;
  QHBoxLayout *hblayouts[3];
};

#endif /* not defined FINDDIALOG_H */
