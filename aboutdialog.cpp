#include <QtGui>
#include <QFile>
#include "include/aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent)
  : QDialog(parent)
{
  mainLabel = new QLabel(tr("WolfTech Editor, version 0.0.1B\n"
			    "Copyright (c) 2007, 2013, Daniel Hazelton"));

  OK = new QPushButton(tr("Ok"));
  OK->setDefault(true);

  connect( OK, SIGNAL(clicked(bool)), this, SLOT(accept()) );
  places[0] = new QLabel(tr("  "));
  places[1] = new QLabel(tr("  "));

  text = new QTextEdit;
  text->setAcceptRichText(false);
  text->setReadOnly(true);
  text->setLineWrapMode( QTextEdit::NoWrap );
  text->setWordWrapMode( QTextOption::NoWrap );
  QFile input(":LICENSE");
  input.open(QFile::ReadOnly | QFile::Text);
  QTextStream in(&input);
  text->setText( in.readAll() );
  input.close();

  tabs = new QTabWidget;
  tabs->addTab(mainLabel, tr("About"));
  tabs->addTab(text, tr("License"));

  vblayout = new QVBoxLayout;
  vblayout->addWidget( tabs );
  
  hblayout = new QHBoxLayout;
  hblayout->addWidget( places[0] );
  hblayout->addWidget( OK );
  hblayout->addWidget( places[1] );
  
  vblayout->addLayout( hblayout );

  setLayout(vblayout);
  setWindowTitle(tr("About WolfTech Editor"));
}
