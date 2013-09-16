#include <QtGui>
#include <cstdio>
#include "include/mainwindow.h"

MainWindow::MainWindow()
{
  editor = new TextEdit;
  editor->setAcceptRichText(true);
  editor->setLineWrapMode(QTextEdit::WidgetWidth);
  editor->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
  setCentralWidget(editor);
  highlighter = new WolfTechEdit( editor->document() );

  findBox = new FindDialog(this);
  aboutBox = new aboutDialog(this);
  findBox->hide();
  aboutBox->hide();

  createActions();
  createMenus();
  createToolBars();
  createStatusBar();

  connect( editor->document(), SIGNAL(contentsChanged()),
	   this, SLOT(documentWasModified()) );
  connect( findBox, SIGNAL(accepted()), this, SLOT(find()) );
  readSettings();
  setCurrentFile( "" );
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (maybeSave()) {
    writeSettings();
    event->accept();
  } else {
    event->ignore();
  }
}

void MainWindow::newFile()
{
  if (maybeSave()) {
    editor->clear();
    setCurrentFile("");
  }
}

void MainWindow::load() {
  open();
}

void MainWindow::find()
{
  editor->find( findBox->terms(), findBox->flags() );
}

void MainWindow::open()
{
  if (maybeSave()) {
    QString filename = QFileDialog::getOpenFileName(this);
    if (!filename.isEmpty())
      loadFile(filename);
  }
}

bool MainWindow::save()
{
  if (curFile.isEmpty()) {
    return saveAs();
  } else {
    return saveFile(curFile);
  }
}

bool MainWindow::saveAs()
{
  QString filename = QFileDialog::getSaveFileName(this);
  if (filename.isEmpty())
    return false;

  return saveFile(filename);
}

void MainWindow::about()
{
  aboutBox->exec();
}

void MainWindow::doFind()
{
  findBox->show();
}

void MainWindow::repeatFind()
{
  editor->find( findBox->terms(), findBox->flags() );
}

void MainWindow::documentWasModified()
{
  setWindowModified(editor->document()->isModified());
  findAct->setEnabled(true);
}


void MainWindow::createActions()
{
  newAct = new QAction( QIcon( ":icons/new.png"), tr("&New"), this );
  newAct->setShortcut(tr("Ctrl+N"));
  newAct->setStatusTip(tr("Create a new file"));
  connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

  openAct = new QAction( QIcon( ":icons/open.png" ), tr("&Open"), this );
  openAct->setShortcut(tr("Ctrl+O"));
  openAct->setStatusTip(tr("Open an existing file"));
  connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

  saveAct = new QAction( QIcon( ":icons/save.png" ), tr("&Save"), this );
  saveAct->setShortcut(tr("Ctrl+S"));
  saveAct->setStatusTip(tr("Save the document to disk"));
  connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

  saveAsAct = new QAction( tr("Save &As"), this );
  saveAsAct->setShortcut(tr("Ctrl+A"));
  saveAsAct->setStatusTip(tr("Save the document under a new name"));
  connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

  exitAct = new QAction( tr("E&xit"), this );
  exitAct->setShortcut(tr("Ctrl+Q"));
  exitAct->setStatusTip(tr("Save the document under a new name"));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

  cutAct = new QAction( QIcon( ":icons/cut.png" ), tr("Cu&t"), this );
  cutAct->setShortcut(tr("Ctrl+X"));
  cutAct->setStatusTip(tr("Cut the current selection's contents to the "
			  "clipboard"));
  connect(cutAct, SIGNAL(triggered()), editor, SLOT(cut()));

  copyAct = new QAction( QIcon( ":icons/copy.png" ), tr("&Copy"), this );
  copyAct->setShortcut(tr("Ctrl+C"));
  copyAct->setStatusTip(tr("Copy the current selection's contents to the "
			   "clipboard"));
  connect(copyAct, SIGNAL(triggered()), editor, SLOT(copy()));

  pasteAct = new QAction( QIcon( ":icons/paste.png"), tr("&Paste"), this );
  pasteAct->setShortcut(tr("Ctrl+V"));
  pasteAct->setStatusTip(tr("Paste the clipboar's contents into the current "
			    "selection"));
  connect(pasteAct, SIGNAL(triggered()), editor, SLOT(paste()));

  undoAct = new QAction( QIcon( ":icons/undo.png"), tr("&Undo"), this );
  undoAct->setShortcut(tr("Ctrl+Z"));
  undoAct->setStatusTip(tr("Undo the previous action"));
  connect(undoAct, SIGNAL(triggered()), editor, SLOT(undo()));

  redoAct = new QAction( QIcon( ":icons/search.png" ), tr("&Redo"), this );
  redoAct->setShortcut(tr("Shift+Ctrl+Z"));
  redoAct->setStatusTip(tr("Undo the last undo"));
  connect(redoAct, SIGNAL(triggered()), editor, SLOT(redo()));

  findAct = new QAction( QIcon( ":icons/find.png" ), tr("&Find"), this );
  findAct->setShortcut(tr("Ctrl+F"));
  findAct->setStatusTip(tr("Search for text in the document"));
  connect(findAct, SIGNAL(triggered()), this, SLOT(doFind()));

  rFindAct = new QAction( QIcon( ":icons/replace.png" ),
			  tr("Find &Again"), this );
  rFindAct->setShortcut(tr("F3"));
  rFindAct->setStatusTip(tr("Repeat last search"));
  connect(rFindAct, SIGNAL(triggered()), this, SLOT(repeatFind()));

  boldAct = new QAction( QIcon( ":icons/bold.gif" ), tr("&Bold"), this );
  boldAct->setShortcut(tr("Ctrl+B"));
  boldAct->setStatusTip(tr("Boldface"));
  connect(boldAct, SIGNAL(triggered()), editor, SLOT(Bold()));

  underlineAct = new QAction( QIcon( ":icons/underline.gif" ),
			      tr("&Underline"), this );
  underlineAct->setShortcut(tr("Ctrl+U"));
  underlineAct->setStatusTip(tr("Underline"));
  connect(underlineAct, SIGNAL(triggered()), editor, SLOT(Underline()));

  italicAct = new QAction( QIcon( ":icons/italic.gif" ),
			   tr("&Italic"), this );
  italicAct->setShortcut(tr("Ctrl+I"));
  italicAct->setStatusTip(tr("Italics"));
  connect(italicAct, SIGNAL(triggered()), editor, SLOT(Italic()));

  superAct = new QAction( QIcon( ":icons/super.gif" ),
			  tr("&Italic"), this );
  superAct->setStatusTip(tr("Superscript"));
  connect(superAct, SIGNAL(triggered()), editor, SLOT(Super()));

  subAct = new QAction( QIcon( ":icons/sub.gif" ),
			  tr("&Italic"), this );
  subAct->setStatusTip(tr("Subscript"));
  connect(subAct, SIGNAL(triggered()), editor, SLOT(Sub()));

  leftAct = new QAction( QIcon( ":icons/align_left.gif" ), tr("Left Align"),
			 this );
  leftAct->setStatusTip(tr("Set the current block to left alignment"));
  connect(leftAct, SIGNAL(triggered()), editor, SLOT(align_left()));

  rightAct = new QAction( QIcon( ":icons/align_right.gif" ), tr("Right Align"),
			 this );
  rightAct->setStatusTip(tr("Set the current block to right alignment"));
  connect(rightAct, SIGNAL(triggered()), editor, SLOT(align_right()));

  centerAct = new QAction( QIcon( ":icons/align_center.gif" ),
			   tr("Center"), this );
  centerAct->setStatusTip(tr("Centered text"));
  connect(centerAct, SIGNAL(triggered()), editor, SLOT(align_center()));

  justAct = new QAction( QIcon( ":icons/align_just.gif" ),
			 tr("Full Justification"), this );
  justAct->setStatusTip(tr("Apply full justification"));
  connect(justAct, SIGNAL(triggered()), editor, SLOT(align_just()));

  aboutAct = new QAction( tr("&About"), this );
  aboutAct->setShortcut(tr("F1"));
  aboutAct->setStatusTip(tr("About this program"));
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

  aboutQtAct = new QAction( tr("About &Qt"), this );
  aboutQtAct->setShortcut(tr("Shift+F1"));
  aboutQtAct->setStatusTip(tr("About the Qt Toolkit"));
  connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  cutAct->setEnabled(false);
  copyAct->setEnabled(false);
  connect(editor, SIGNAL(copyAvailable(bool)), cutAct, SLOT(setEnabled(bool)));
  connect(editor, SIGNAL(copyAvailable(bool)), copyAct,SLOT(setEnabled(bool)));
}

void MainWindow::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(newAct);
  fileMenu->addAction(openAct);
  fileMenu->addAction(saveAct);
  fileMenu->addAction(saveAsAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  editMenu = menuBar()->addMenu(tr("&Edit"));
  editMenu->addAction(copyAct);
  editMenu->addAction(cutAct);
  editMenu->addAction(pasteAct);
  editMenu->addSeparator();
  editMenu->addAction(undoAct);
  editMenu->addAction(redoAct);
  editMenu->addSeparator();
  editMenu->addAction(findAct);
  editMenu->addAction(rFindAct);

  formatMenu = menuBar()->addMenu(tr("&Format"));
  formatMenu->addAction(boldAct);
  formatMenu->addAction(italicAct);
  formatMenu->addAction(underlineAct);
  formatMenu->addAction(superAct);
  formatMenu->addAction(subAct);
  formatMenu->addSeparator();
  formatMenu->addAction(leftAct);
  formatMenu->addAction(rightAct);
  formatMenu->addAction(centerAct);
  formatMenu->addAction(justAct);

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
  fileToolBar = addToolBar(tr("File"));
  fileToolBar->addAction(newAct);
  fileToolBar->addAction(openAct);
  fileToolBar->addAction(saveAct);
  fileToolBar->setObjectName(tr("File ToolBar"));

  editToolBar = addToolBar(tr("Edit"));
  editToolBar->addAction(cutAct);
  editToolBar->addAction(copyAct);
  editToolBar->addAction(pasteAct);
  editToolBar->addSeparator();
  editToolBar->addAction(undoAct);
  editToolBar->addAction(redoAct);
  editToolBar->setObjectName(tr("Edit ToolBar"));

  formatButtons = addToolBar(tr("Formatting"));
  formatButtons->addAction(boldAct);
  formatButtons->addAction(underlineAct);
  formatButtons->addAction(italicAct);
  formatButtons->addAction(superAct);
  formatButtons->addAction(subAct);
  formatButtons->addSeparator();
  formatButtons->addAction(leftAct);
  formatButtons->addAction(rightAct);
  formatButtons->addAction(centerAct);
  formatButtons->addAction(justAct);
  formatButtons->setObjectName(tr("Format ToolBar"));

  fontStuff = addToolBar(tr("Font Selection"));
  fonts = new QFontComboBox(fontStuff);
  fonts->setCurrentFont(editor->currentFont());
  fonts->setFontFilters(QFontComboBox::AllFonts);
  fonts->setEditable(false);
  fontSizes = new FontSizeCombo(fontStuff);

  connect( fonts, SIGNAL(currentFontChanged(QFont)),
	   this, SLOT(fontSelect(QFont)) );
  connect( fontSizes, SIGNAL(currentIndexChanged(int)),
	   this, SLOT(fontSize(int)) );

  fontStuff->addWidget( fonts );
  fontStuff->addWidget( fontSizes );
  fontStuff->setObjectName(tr("Font Controls ToolBar"));
}

void MainWindow::createStatusBar()
{
  statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
  QSettings settings(QSettings::NativeFormat,
		     QSettings::UserScope,
		     "ShadowWolf Tech",
		     "ShadowWolf Tech Editor",
		     this);
  settings.beginGroup("MainWindow");
    resize( settings.value( "size", QSize( 640, 480 ) ).toSize() );
    move( QPoint( settings.value( "posX", 0 ).toInt(),
			settings.value( "posY", 0 ).toInt() ) );

    bool iF = settings.value( "fullscreen", false ).toBool();
    Qt::WindowState wSF( Qt::WindowFullScreen );
    Qt::WindowState wSN( Qt::WindowActive );

    setWindowState( iF?wSF:wSN );

    QByteArray cState( saveState(1).toBase64() );
    QByteArray sState( settings.value( "data", cState ).toByteArray() );
    QByteArray fState = QByteArray().fromBase64( sState );
    restoreState( fState, 1 );
  settings.endGroup();
}

void MainWindow::writeSettings()
{
  QSettings settings(QSettings::NativeFormat,
		     QSettings::UserScope,
		     "WolfTech",
		     "WolfTech Editor",
		     this);

  // start the main group
  settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("fullscreen", isFullScreen());
    settings.setValue("posX", pos().x());
    settings.setValue("posY", pos().y());
    settings.setValue("data", saveState(1).toBase64());
  settings.endGroup();
  settings.sync();
}

bool MainWindow::maybeSave()
{
  if( editor->document()->isModified() ) {
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning( this, tr("WolfTech Editor"),
				tr("The document has been modified\n"
				   "Do you want to save your changes?"),
				QMessageBox::Save | QMessageBox::Discard |
				QMessageBox::Cancel );

    if ( ret == QMessageBox::Save )
      return save();
    else if ( ret == QMessageBox::Discard )
      return true;
    else if ( ret == QMessageBox::Cancel )
      return false;
  }
  return true;
}

void MainWindow::loadFile( const QString &fileName )
{
  QFile file(fileName);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning( this, tr("WolfTech Editor"),
			  tr( "Cannot read file %1:\n%2.")
			  .arg(fileName)
			  .arg(file.errorString()));
    return;
  }

  QTextStream in(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);
  editor->setText(in.readAll());
  QApplication::restoreOverrideCursor();

  setCurrentFile(fileName);
  statusBar()->showMessage(tr("Loaded file %1").arg(fileName), 2000 );
}

bool MainWindow::saveFile( const QString &fileName )
{
  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning( this, tr("WolfTech Editor"),
			  tr( "Cannot write file %1:\n%2" )
			  .arg(fileName)
			  .arg(file.errorString()));
    return false;
  }

  QString ext = QFileInfo(fileName).suffix();
  QTextStream out(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);
  if (ext == "html" || ext == "htm" ) {
    out << editor->toHtml();
  } else {
    out << editor->toPlainText();
  }
  QApplication::restoreOverrideCursor();

  setCurrentFile(fileName);
  statusBar()->showMessage(tr("File Saved"), 2000);
  return true;
}

void MainWindow::setCurrentFile( const QString &fileName )
{
  curFile = fileName;
  editor->document()->setModified(false);
  setWindowModified(false);

  QString shownName;
  if (curFile.isEmpty())
    shownName = "untitled.txt";
  else
    shownName = strippedName(curFile);

  setWindowTitle( tr("%1[*] - %2").arg(shownName).arg(tr("WolfTech Editor")));
}

QString MainWindow::strippedName( const QString &fullFileName )
{
  return QFileInfo(fullFileName).fileName();
}

void MainWindow::fontSize( int ind )
{
  editor->setFocus(Qt::ActiveWindowFocusReason);
  QTextCursor curs;
  curs = editor->textCursor();

  QTextCharFormat form(curs.charFormat());
  form.setFontPointSize( fontSizes->sizeAt( ind ) );
  curs.setCharFormat( form );
  editor->setTextCursor( curs );
}

void MainWindow::fontSelect(const QFont &font)
{
  qreal sz = editor->textCursor().charFormat().fontPointSize();
  editor->setFocus(Qt::ActiveWindowFocusReason);
  QTextCursor curs;
  QFont fc(font);
  curs = editor->textCursor();
  fc.setPointSize( sz );
  QTextCharFormat form(curs.charFormat());
  form.setFont( fc );
  curs.setCharFormat( form );
  editor->setTextCursor( curs );
  fontSizes->update( font );
  fontSizes->Select( sz );
}
