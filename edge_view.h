#ifndef EDGE_VIEW_H
#define EDGE_VIEW_H

#include <QGraphicsItem>
#include <memory>

class GraphView;

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class EdgeView :
		public QGraphicsItem,
		public std::enable_shared_from_this<EdgeView>
{
public:
	EdgeView(GraphView* view);
	QRectF boundingRect() const override;
	void paint(
			QPainter* painter,
			const QStyleOptionGraphicsItem* option,
			QWidget* widget) override;
private:
	GraphView* graphView;
};

#endif // EDGE_VIEW_H
