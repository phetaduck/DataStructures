#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include <QGraphicsView>

class NodeView;

class GraphView
		: public QGraphicsView
{
	Q_OBJECT
public:
	GraphView(QWidget* parent = nullptr);
	void addItem(NodeView* nodeView);
	void clear();
};

#endif // GRAPH_VIEW_H
