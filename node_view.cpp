#include "node_view.h"
#include "graph_view.h"
#include "edge_view.h"

NodeView::NodeView(GraphView* view)
	: graphView(view)
{
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}

QRectF NodeView::boundingRect() const
{
	return QRectF{};
}

QPainterPath NodeView::shape() const
{
	return QPainterPath{};
}

void NodeView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}
