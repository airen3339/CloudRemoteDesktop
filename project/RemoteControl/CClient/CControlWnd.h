#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QMainWindow>
#include <QRect>
#include <QTcpSocket>
#include <QHostAddress>
#include <QImage>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <memory>

#include "CMsgReader.h"
#include "CMsgWriter.h"
#include "CImgReader.h"
#include "CRenderHelper.h"

using std::shared_ptr;
using std::make_shared;

class CControlWnd : public QWidget
{
    Q_OBJECT

private:
    typedef shared_ptr<CRenderHelper> CRenderHelperPtr;

private:
    QRect m_rect;
    QImage* image;
    CMsgReader* m_pCMsgReader;
    CImgReader* m_pCImgReader;
    CMsgWriter* m_pCMsgWriter;
    int frame_width;
    int frame_height;
    int server_screen_width;
    int server_screen_height;
    CRenderHelperPtr m_CRenderHelper;
    
public:
    CControlWnd(QRect rect, QWidget *parent = 0);
    ~CControlWnd();
    void Init();
    void InitData();
signals:
    void mouseMoveTo(int, int);

public slots:
    void frameChanged(QImage*);
    void changeFrameSize(int, int);
    void gotServerScreenSize(int, int);

    void keyPressSlot(QKeyEvent *);
    void keyReleaseSlot(QKeyEvent *);

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    uchar translateKey(int key);
};

#endif // CONTROLPANEL_H
