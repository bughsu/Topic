QT += core gui widgets multimedia multimediawidgets network

CONFIG += c++17

# FFmpeg 8.0.1 路徑配置
FFMPEG_PATH = "C:/Users/ccsto/Downloads/ffmpeg-8.0.1-full_build-shared"

INCLUDEPATH += $${FFMPEG_PATH}/include
LIBS += -L$${FFMPEG_PATH}/lib \
        -lavformat \
        -lavcodec \
        -lavutil \
        -lswscale \
        -lswresample

SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h
