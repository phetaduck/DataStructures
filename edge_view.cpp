#include "edge_view.h"

EdgeView::EdgeView(GraphView* view)
	: graphView(view)
{
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}

QRectF EdgeView::boundingRect() const
{
	return QRectF();
}

void EdgeView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}
