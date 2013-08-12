#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QObject>
#include <highlightsettings.h>
#include <audioplayer.h>
#include <mainwindow.h>
#include <QSettings>

class HighlightSettings;
class MainWindow;
class HighlightSettingsEntry;

class Highlighter : public QObject {
    Q_OBJECT

public:
    explicit Highlighter(QObject *parent = 0);
    ~Highlighter();

    QString highlight(QString);
    void alert(QString eventName, int value = 99);
    void reloadSettings();

private:
    HighlightSettings* highlightSettings;
    AudioPlayer* audioPlayer;
    MainWindow* mainWindow;
    QRegExp rx;
    QList<HighlightSettingsEntry>* highlightList;

    bool healthAlert;    

    //QString& highlightText(int, QString&, HighlightSettingsEntry);
    void highlightText(HighlightSettingsEntry, QString&, int);
    void highlightAlert(HighlightSettingsEntry);
    void highlightTimer(HighlightSettingsEntry);

    Qt::CaseSensitivity matchCase(bool);

    QList<HighlightSettingsEntry> getHighlightSettings();

signals:
    void playAudio(QString);
    void setTimer(int);
    
public slots:

};

#endif // HIGHLIGHTER_H