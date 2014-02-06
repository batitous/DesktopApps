#ifndef WINSTRUMENT_H
#define WINSTRUMENT_H

#include <QGraphicsView>

class WidgetInstrument : public QGraphicsView
{
public:
    WidgetInstrument(QWidget * parent = 0) : QGraphicsView(parent)
    {
        setWindowTitle(tr("Instrument Viewer"));
    }

protected:
    void resizeEvent(QResizeEvent *event)
    {
        if (scene())
            scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        QGraphicsView::resizeEvent(event);
    }
};

#endif // WINSTRUMENT_H
