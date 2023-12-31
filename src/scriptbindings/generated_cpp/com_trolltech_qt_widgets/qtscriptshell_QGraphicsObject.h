#ifndef QTSCRIPTSHELL_QGRAPHICSOBJECT_H
#define QTSCRIPTSHELL_QGRAPHICSOBJECT_H

#include <qgraphicsitem.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsObject : public QGraphicsObject
{
public:
    QtScriptShell_QGraphicsObject(QGraphicsItem*  parent = 0);
    ~QtScriptShell_QGraphicsObject();

    void advance(int  phase);
    QRectF  boundingRect() const;
    void childEvent(QChildEvent*  event);
    bool  collidesWithItem(const QGraphicsItem*  other, Qt::ItemSelectionMode  mode) const;
    bool  collidesWithPath(const QPainterPath&  path, Qt::ItemSelectionMode  mode) const;
    bool  contains(const QPointF&  point) const;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent*  event);
    void customEvent(QEvent*  event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent*  event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*  event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent*  event);
    void dropEvent(QGraphicsSceneDragDropEvent*  event);
    bool  event(QEvent*  ev);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    QVariant  extension(const QVariant&  variant) const;
    void focusInEvent(QFocusEvent*  event);
    void focusOutEvent(QFocusEvent*  event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent*  event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*  event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent*  event);
    void inputMethodEvent(QInputMethodEvent*  event);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
    bool  isObscuredBy(const QGraphicsItem*  item) const;
    QVariant  itemChange(QGraphicsItem::GraphicsItemChange  change, const QVariant&  value);
    void keyPressEvent(QKeyEvent*  event);
    void keyReleaseEvent(QKeyEvent*  event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*  event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*  event);
    void mousePressEvent(QGraphicsSceneMouseEvent*  event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*  event);
    QPainterPath  opaqueArea() const;
    void paint(QPainter*  painter, const QStyleOptionGraphicsItem*  option, QWidget*  widget);
    bool  sceneEvent(QEvent*  event);
    bool  sceneEventFilter(QGraphicsItem*  watched, QEvent*  event);
    QPainterPath  shape() const;
    void timerEvent(QTimerEvent*  event);
    int  type() const;
    void wheelEvent(QGraphicsSceneWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSOBJECT_H
