#include <QtGui>
#include "include/findDialog.h"

FindDialog::FindDialog(QWidget *parent)
  : QDialog(parent)
{
  label = new QLabel( tr("Find &what") );
  lineEdit = new QLineEdit;
  label->setBuddy(lineEdit);
  
  hblayouts[0] = new QHBoxLayout;
  hblayouts[0]->addWidget(label);
  hblayouts[0]->addWidget(lineEdit);

  boxes[0] = new QCheckBox(tr("Match &case"), this);
  boxes[1] = new QCheckBox(tr("&Backwards"), this);
  boxes[2] = new QCheckBox(tr("&Whole words"), this);

  hblayouts[1] = new QHBoxLayout;
  hblayouts[1]->addWidget(boxes[0]);
  hblayouts[1]->addWidget(boxes[1]);
  hblayouts[1]->addWidget(boxes[2]);
 
  buttons[0] = new QPushButton(tr("&Find"), this);
  buttons[0]->setDefault(true);
  buttons[1] = new QPushButton(tr("Ca&ncel"), this);
  buttons[1]->setAutoDefault(false);

  hblayouts[2] = new QHBoxLayout;
  hblayouts[2]->addWidget(buttons[0]);
  hblayouts[2]->addWidget(buttons[1]);

  vblayout = new QVBoxLayout;
  vblayout->addLayout(hblayouts[0]);
  vblayout->addLayout(hblayouts[1]);
  vblayout->addLayout(hblayouts[2]);

  setLayout(vblayout);
  setWindowTitle(tr("Find Text"));
  connect( buttons[0], SIGNAL(clicked(bool)), this, SLOT(accept()) );
  connect( buttons[1], SIGNAL(clicked(bool)), this, SLOT(reject()) );
}

const QTextDocument::FindFlags FindDialog::flags() {
  QTextDocument::FindFlags rval = 0;

  if(boxes[0]->checkState() == Qt::Checked)
    rval |= QTextDocument::FindCaseSensitively;

  if(boxes[1]->checkState() == Qt::Checked)
    rval |= QTextDocument::FindBackward;

  if(boxes[2]->checkState() == Qt::Checked)
    rval |= QTextDocument::FindWholeWords;

  return rval;
}

const QString FindDialog::terms() {
  return lineEdit->text();
}

