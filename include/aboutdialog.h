#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QLabel;
class QTextEdit;
class QPushButton;
class QTabWidget;
class QHBoxLayout;
class QVBoxLayout;
class QString;
class QWidget;

class aboutDialog: public QDialog {
  Q_OBJECT 
public:
  aboutDialog( QWidget *parent = 0);

private:
  QLabel      *mainLabel;
  QTextEdit   *text;
  QPushButton *OK;
  QLabel      *places[2];
  QTabWidget  *tabs;
  QHBoxLayout *hblayout;
  QVBoxLayout *vblayout;
};

#endif /* not defined ABOUTDIALOG_H */
 
