#include <QtCore>
#include "highlight.hpp"
#include <QtDebug>

struct rule {
  QString pattern;
  QString format;
};

static struct rule rules[] = {
  { "-",                               "red" },
  { "\\+",                             "red" },
  { "\\+\\+",                          "red" },
  { "--",                              "red" },
  { "*",                             "red" },
  { "/",                               "red" },
  { "%",                               "red" },
  { "<<",                              "red" },
  { ">>",                              "red" },
  { "<<<",                             "red" },
  { ">>>",                             "red" },
  { "&",                               "red" },
  { "\\|",                               "red" },
  { "\\|\\|",                              "red" },
  { "&&",                              "red" },
  { "~",                               "red" },
  { "\\^",                               "red" },
  { "=",                               "red" },
  { "==",                              "red" },
  { "char|int|long|float|double|void", "blue" },
  { "register|static|extern|signed|unsigned",          "red" },
  { "[0-9][0-9]*(\\.[0-9]*)?",            "cyan bold" },
  { NULL, NULL }
};
#define NRULES 22
WolfTechEdit::WolfTechEdit(QTextDocument *parent)
  : QSyntaxHighlighter( parent )
{
  for( int i = 0; i < NRULES; i++ ) {
    rule t = rules[i];
    QRegExp pat( t.pattern, Qt::CaseInsensitive, QRegExp::RegExp2 );
    QTextCharFormat form;
    form.setFont( QFont("Helvetica", 12) );
    QStringList forms = t.format.split(' ');
    foreach( QString k, forms ) {
      if( k == "bold" )
        form.setFontWeight( QFont::Bold );
      else if( k == "italic" )
        form.setFontItalic( true );
      else if( k == "underline" )
        form.setFontUnderline( true );
      else if( k == "white" )
        form.setForeground( Qt::white );
      else if( k == "red" )
        form.setForeground( Qt::red );
      else if( k == "green" )
        form.setForeground( Qt::green );
      else if( k == "blue" )
        form.setForeground( Qt::blue );
      else if( k == "cyan" )
        form.setForeground( Qt::cyan );
      else if( k == "magenta" )
        form.setForeground( Qt::magenta );
      else if( k == "yellow" )
        form.setForeground( Qt::yellow );
      else if( k == "gray" )
        form.setForeground( Qt::gray );
      else if( k == "black" )
        form.setForeground( Qt::black );
      else if( k == "dark_red" )
        form.setForeground( Qt::darkRed );
      else if( k == "dark_green" )
        form.setForeground( Qt::darkGreen );
      else if( k == "dark_blue" )
        form.setForeground( Qt::darkBlue );
      else if( k == "dark_cyan" )
        form.setForeground( Qt::darkCyan );
      else if( k == "dark_magenta" )
        form.setForeground( Qt::darkMagenta );
      else if( k == "dark_yellow" )
        form.setForeground( Qt::darkYellow );
      else if( k == "dark_gray" )
        form.setForeground( Qt::darkGray );
      else if( k == "light_gray" )
        form.setForeground( Qt::lightGray );
    }
    struct highlight_rule r = { pat, form };
    highlightingRules.push_back(r);
  }

  commentStartExp = QRegExp( "\\/\\*" );
  commentEndExp = QRegExp( "\\*\\/" );
  commentFormat = QTextCharFormat();
  commentFormat.setFont( QFont( "Times", 12 ) );
  commentFormat.setForeground( Qt::lightGray );
  commentFormat.setFontItalic( true );
}

void WolfTechEdit::highlightBlock(const QString &text) {
  enum { NormalState = -1, InsideCStyleComment };

  int state = previousBlockState();
  int start = 0;
  for (int i = 0; i < text.length(); ++i) {
    if (state == InsideCStyleComment) {
      if (text.mid(i, 2) == "*/") {
        state = NormalState;
        setFormat(start, i - start + 2, commentFormat);
      }
    } else {
      if (text.mid(i, 2) == "//") {
        setFormat(i, text.length() - i, commentFormat);
        break;
      } else if (text.mid(i, 2) == "/*") {
        start = i;
        state = InsideCStyleComment;
      } else {
        foreach( struct highlight_rule r, highlightingRules ) {
          int index = text.right(i).indexOf( r.pattern );
          if( index >= 0 )
            while( index >= 0 ) {
              int len = r.pattern.matchedLength();
              setFormat( index, len, r.format );
              index = text.right(i).indexOf( r.pattern, index+len );
            }
        }
      }
    }
  }
  if (state == InsideCStyleComment)
    setFormat(start, text.length() - start, Qt::blue);

  setCurrentBlockState(state);
}



