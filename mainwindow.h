#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaRecorder>
#include <QMediaCaptureSession>
#include <QVideoWidget>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QGridLayout>
#include <QProgressBar>
#include <QScrollArea>
#include <QLabel>
#include <QProcess>
#include <QSlider>

// 自訂可點擊的 VideoWidget
class ClickableVideoWidget : public QVideoWidget {
    Q_OBJECT
public:
    explicit ClickableVideoWidget(QWidget *parent = nullptr) : QVideoWidget(parent) {}
signals:
    void clicked();
protected:
    void mouseReleaseEvent(QMouseEvent *) override { emit clicked(); }
};

// 播放器單元結構
struct PlayerUnit {
    QString streamUrl;
    QString recordingFilePath;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    ClickableVideoWidget *videoWidget;
    QProcess *ffmpegProcess;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddStream();
    void onPlaySelectedLive();
    void onDeleteCamera();
    void onToggleGlobalRecording(bool checked);
    void switchToManagerPage();
    void toggleFocus(PlayerUnit* unit);
    void onPlayRecordedVideo();
    void onOpenInExternalPlayer();      // 新增
    void onDeleteRecordedVideo();
    void updateTimeLabel();             // 新增

private:
    void setupUi();
    QString getRecordingsPath();
    QString formatTime(qint64 milliseconds);  // 新增

    // 監控相關
    QListWidget *m_streamList;
    QStackedWidget *m_stackedWidget;
    QWidget *m_gridPage;
    QGridLayout *m_gridLayout;
    ClickableVideoWidget *m_focusVideoWidget;
    QPushButton *m_recordBtn;
    QProgressBar *m_globalProgressBar;
    QList<PlayerUnit*> m_playerUnits;
    PlayerUnit *m_currentFocusedUnit = nullptr;

    // 檔案管理相關
    QWidget *m_managerPage;
    QListWidget *m_fileListWidget;

    // 內建播放器相關 (新增)
    QMediaPlayer *m_playbackPlayer;
    QAudioOutput *m_playbackAudioOutput;
    QVideoWidget *m_playbackVideoWidget;
    QPushButton *m_playBtn;
    QPushButton *m_stopBtn;
    QSlider *m_positionSlider;
    QSlider *m_volumeSlider;
    QLabel *m_timeLabel;
};

#endif // MAINWINDOW_H
