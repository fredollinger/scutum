MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QToolBar * tb = addToolBar(tr("Open"));

    /* Open rss feed combo. */
    combo = new QComboBox;
    ListView * lv = new ListView;
    combo->setView(lv);
    combo->setEditable(true);
    combo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(combo, SIGNAL(activated(int)), this, SLOT(openRssFeed()));
    tb->addWidget(combo);

    /* Open RSS Feed button. */
    QAction * act = new QAction(tr("Open RSS Feed"), this);
    act->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    connect(act, SIGNAL(triggered()), this, SLOT(openRssFeed()));
    tb->addAction(act);

    /* List-view to display list of stories. */
    tv = new QListView;
    connect(tv, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(listViewDoubleClicked(QModelIndex)));
    model = new QStandardItemModel(0, 1, this);
    tv->setModel(model);

    /* Progress bar to signal progress of RSS feed download and web page load. */
    progress = new QProgressBar;
    statusBar()->addPermanentWidget(progress);

    /* Web-view to display articles. */
    wv = new QWebView;
    wv->load(QUrl("about:blank"));
    connect(wv, SIGNAL(loadProgress(int)), progress, SLOT(setValue(int)));

    QSplitter * splitter = new QSplitter;
    splitter->addWidget(tv);
    splitter->addWidget(wv);
    this->setCentralWidget(splitter);

    /* Load saved rss feeds. */
    QSettings settings;
    int size = settings.beginReadArray("rssFeeds");
    for (int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        QString url = settings.value("url").toString();
        combo->addItem(url);
    }
    settings.endArray();

    if (size == 0)
    {
        /* Bonus RSS feed if the list is empty. */
        combo->addItem("http://www.qtcentre.org/forum/external.php?type=RSS2");
    }

    /* Set up the network manager. */
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    /* Save our list of RSS feeds. */
    QSettings settings;
    settings.beginWriteArray("rssFeeds");
    settings.remove("");
    for (int i = 0; i < combo->count(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("url", combo->itemText(i));
    }
    settings.endArray();
}

void MainWindow::listViewDoubleClicked(const QModelIndex &index)
{
    /* Load article in the web-view. */
    QString strLink = index.data(Qt::UserRole).toString();
    wv->load(QUrl(strLink));
}

void MainWindow::openRssFeed()
{
    /* Search the combo box for duplicates before adding this item. */
    int i = combo->findText(combo->currentText());

    if (i != -1)
    {
        combo->setCurrentIndex(i);
    }
    else
    {
        combo->addItem(combo->currentText());
        combo->setCurrentIndex(combo->count() - 1);
    }

    reply = manager->get(QNetworkRequest(QUrl(combo->currentText())));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
}

void MainWindow::downloadProgress(qint64 bytes, qint64 bytesTotal)
{
    if (bytesTotal == -1)
    {
        /* No total bytes available, just set the progress bar to show a busy indicator. */
        progress->setMinimum(0);
        progress->setMaximum(0);
    }
    else
    {
        progress->setMaximum(100);
        int percent = bytes * 100 / bytesTotal;
        progress->setValue(percent);
    }
}

void MainWindow::replyFinished(QNetworkReply * netReply)
{
    QString str (netReply->readAll());

    /* If we are redirected, try again. TODO: Limit redirection count. */
    QVariant vt = netReply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    delete reply;

    if (!vt.isNull())
    {
        qDebug() << "Redirected to:" << vt.toUrl().toString();
        reply = manager->get(QNetworkRequest(vt.toUrl()));
        connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
    }
    else
    {
        /* We have something. */
        QDomDocument doc;
        QString error;
        if (!doc.setContent(str, false, &error))
        {
            wv->setHtml(QString("<h1>Error</h1>") + error);
        }
        else
        {
            QDomElement docElem = doc.documentElement();
            QDomNodeList nodeList = docElem.elementsByTagName("item");

            model->clear();
            model->insertColumn(0);

            for (uint i = 0; i < nodeList.length(); i++)
            {
                QDomNode node = nodeList.item(i);
                QDomElement e = node.toElement();
                QString strTitle =  e.elementsByTagName("title").item(0).firstChild().nodeValue();
                QString strLink = e.elementsByTagName("link").item(0).firstChild().nodeValue();
                QString strDescription = e.elementsByTagName("description").item(0).firstChild().nodeValue();
                QString strToolTip = "<b>" + strTitle + "</b>" + "<br /><br />" + strDescription  +  "<br /><br />" + strLink;

                model->insertRows(model->rowCount(), 1);
                QModelIndex index = model->index(model->rowCount() - 1, 0);
                model->setData(index, strTitle, Qt::DisplayRole);
                model->setData(index, style()->standardIcon(QStyle::SP_FileIcon), Qt::DecorationRole);
                model->setData(index, strToolTip, Qt::ToolTipRole);
                model->setData(index, strLink, Qt::UserRole);
                model->itemFromIndex(index)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            }
        }
    }
}


/* Implements a list-view which supports the delete key. */
void ListView::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Delete)
    {
        event->accept();
        QModelIndexList l = selectedIndexes();
        if (l.length() > 0)
        {
            model()->removeRow(l.at(0).row(), l.at(0).parent());
        }
    }
    else
    {
        QListView::keyPressEvent(event);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
