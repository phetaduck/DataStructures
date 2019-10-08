#include "graph_view.h"
#include "node_view.h"
#include "edge_view.h"

GraphView::GraphView(QWidget* parent)
	: QGraphicsView (parent)
{
	QGraphicsScene* scene = new QGraphicsScene(this);
	setScene(scene);
}

void GraphView::addItem(NodeView* nodeView)
{
	this->scene()->addItem(nodeView);
}

void GraphView::clear()
{
	this->scene()->clear();
}
