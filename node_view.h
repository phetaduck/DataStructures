#ifndef NODE_VIEW_H
#define NODE_VIEW_H

#include <QGraphicsItem>
#include <memory>

class GraphView;
class EdgeView;

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class NodeView :
		public QGraphicsItem,
		public std::enable_shared_from_this<NodeView>
{
public:
	NodeView(GraphView* view);

	void addEdge(EdgeView* edge);
	std::vector<EdgeView* > edges() const;

	enum { Type = UserType + 1 };
	int type() const override { return Type; }

	void calculateForces();
	bool advancePosition();

	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(
			QPainter* painter,
			const QStyleOptionGraphicsItem* option,
			QWidget* widget) override;
private:
	GraphView* graphView;
	std::vector<EdgeView* > edges_;
};

#endif // NODE_VIEW_H
