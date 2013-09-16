#ifndef FONTSIZECOMBO_H
#define FONTSIZECOMBO_H

#include <QComboBox>

class QString;
class QFontDatabase;

class FontSizeCombo: public QComboBox
{
  Q_OBJECT
 public:
  FontSizeCombo( QWidget *parent=0 );
  void update( const QFont &font );
  int currentSize();
  void Select( int size );
  int sizeAt(int ind);

 private:
  void init();
  QList<int> sizes;
};

#endif // !defined FONTSIZECOMBO_H

