#include <QList>
#include <QString>
#include <QStringList>
#include <QComboBox>
#include <QFontDatabase>
#include <QMessageBox>
#include "include/fontsizecombo.h"

FontSizeCombo::FontSizeCombo(QWidget *parent)
  : QComboBox(parent)
{
  init();
}

void FontSizeCombo::update( const QFont &font )
{
  sizes = QFontDatabase().pointSizes(font.family());
  if(!sizes.empty()) {
    this->clear();
    for( int i = 0; i < sizes.size(); i++ ) {
      this->addItem( tr("%1").arg(sizes[i]) );
    }
  }
}

void FontSizeCombo::init( )
{
  sizes = QFontDatabase().pointSizes(tr("Sans Serif"));
  if(!sizes.empty()) {
    for( int i = 0; i < sizes.size(); i++ ) {
      this->addItem( tr("%1").arg(sizes[i]) );
    }
  }
}

int FontSizeCombo::currentSize()
{
  return sizes[this->currentIndex()];
}

void FontSizeCombo::Select( int size )
{
  this->setCurrentIndex( sizes.indexOf( size ) );
}

int FontSizeCombo::sizeAt( int index )
{
  return sizes[index];
}
