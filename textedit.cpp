#include <QtCore>
#include <QtGui>
#include "include/textedit.h"

TextEdit::TextEdit( QWidget *parent )
  : QTextEdit( parent ) {
}

QTextCharFormat TextEdit::currentFormat() {
  QTextCursor curs(document());
  curs.setPosition(textCursor().selectionStart());
  curs.setPosition(textCursor().selectionEnd(), QTextCursor::KeepAnchor);
  return curs.charFormat();
}

void TextEdit::Super() {
  QTextCharFormat form( currentFormat() );
  
  if( form.verticalAlignment() == QTextCharFormat::AlignSuperScript )
    form.setVerticalAlignment( QTextCharFormat::AlignNormal );
  else
    form.setVerticalAlignment( QTextCharFormat::AlignSuperScript );

  this->setCurrentCharFormat( form );
}

void TextEdit::Sub() {
  QTextCharFormat form( currentFormat() );
  
  if( form.verticalAlignment() == QTextCharFormat::AlignSubScript )
    form.setVerticalAlignment( QTextCharFormat::AlignNormal );
  else
    form.setVerticalAlignment( QTextCharFormat::AlignSubScript );

  this->setCurrentCharFormat( form );
}

void TextEdit::Bold() {
  QTextCharFormat form( currentFormat() );
  
  if( form.fontWeight() == QFont::Bold )
    form.setFontWeight( QFont::Normal );
  else
    form.setFontWeight( QFont::Bold );

  this->setCurrentCharFormat( form );
}

void TextEdit::Italic() {
  QTextCharFormat form( currentFormat() );
  
  form.setFontItalic( !form.fontItalic() );

  this->setCurrentCharFormat( form );
}

void TextEdit::Underline() {
  QTextCharFormat form( currentFormat() );
  
  form.setFontUnderline( !form.fontUnderline() );

  this->setCurrentCharFormat( form );
}

void TextEdit::align_left() {
  QTextCursor curs( this->textCursor() );
  QTextBlockFormat form( curs.blockFormat() );
  form.setAlignment(Qt::AlignLeft);
  curs.setBlockFormat( form );
  this->setTextCursor( curs );
}

void TextEdit::align_right() {
  QTextCursor curs( this->textCursor() );
  QTextBlockFormat form( curs.blockFormat() );
  form.setAlignment(Qt::AlignRight);
  curs.setBlockFormat( form );
  this->setTextCursor( curs );
}

void TextEdit::align_center() {
  QTextCursor curs( this->textCursor() );
  QTextBlockFormat form( curs.blockFormat() );
  form.setAlignment(Qt::AlignHCenter);
  curs.setBlockFormat( form );
  this->setTextCursor( curs );
}

void TextEdit::align_just() {
  QTextCursor curs( this->textCursor() );
  QTextBlockFormat form( curs.blockFormat() );
  form.setAlignment(Qt::AlignJustify);
  curs.setBlockFormat( form );
  this->setTextCursor( curs );
}
