#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
#include "gobjects.h"
#include "gevents.h"
#include "ginteractors.h"
using namespace std;

const string ORDER_PROMPT = "Enter Sierpinski triangle order range(7-15): ";
const string EDGE_PROMPT = "Enter triangle edge length range(400-700px): ";
const int SIZE = 900;
const int THETA = 60;

void drawTrianglee(GPoint p1, GPoint p2, GPoint p3, int order, GWindow &gw){
	if(order == 0){
		return;
	}
	GPoint midP1P2((p1.getX() + p2.getX()) / 2.0, (p1.getY() + p2.getY())/2.0);
	GPoint midP2P3((p2.getX() + p3.getX()) / 2.0, (p2.getY() + p3.getY())/2.0);
	GPoint midP3P1((p3.getX() + p1.getX()) / 2.0, (p3.getY() + p1.getY())/2.0);
	GPolygon *poly = new GPolygon();
	poly->addVertex(midP1P2.getX(), midP1P2.getY());
	poly->addVertex(midP2P3.getX(), midP2P3.getY());
	poly->addVertex(midP3P1.getX(), midP3P1.getY());
	//poly->setFilled(true);
	/*if(order % 3 == 0){
		poly -> setFillColor("MAGENTA");
	}else if(order % 3 == 1){
		poly -> setFillColor("ORANGE");
	}else{
		poly -> setFillColor("CYAN");		
	}*/
	gw.add(poly);
	drawTrianglee(p1, midP1P2, midP3P1, order - 1, gw);
	drawTrianglee(midP1P2, p2, midP2P3, order - 1, gw);
	drawTrianglee(midP3P1, midP2P3, p3,order - 1, gw);
}

int main0() {
	int order, edge;
	GWindow gw(SIZE, SIZE);
	GSlider *sliderEdge = new GSlider(300, 700, 300);
	GSlider *sliderOrder = new GSlider(5, 13, 5);
	GLabel *label1 = new GLabel("edge");
	GLabel *label2 = new GLabel("order");
	GLabel *welcome = new GLabel("Click mouse on the screen to draw the Triangle");
	double x = (gw.getWidth() - welcome->getWidth()) / 2;
    double y = (gw.getHeight() + welcome->getFontAscent()) / 2;
	gw.add(welcome,x, y);
	gw.addToRegion(label1, "SOUTH");
	gw.addToRegion(sliderEdge, "SOUTH");
	gw.addToRegion(label2, "SOUTH");
	gw.addToRegion(sliderOrder, "SOUTH");
	while(true){
		GMouseEvent e = waitForEvent();
		if (e.getEventType() == MOUSE_CLICKED) {
			gw.remove(welcome);
			edge = sliderEdge->getValue();
			order = sliderOrder->getValue();
			GPoint p1 = gw.drawPolarLine(gw.getWidth() / 2.0, gw.getHeight() / 2.0 - (edge * sqrt(3.0) / 2.0) * (2.0/3.0), edge, THETA * -2);
			GPoint p2 = gw.drawPolarLine(p1.getX(), p1.getY(), edge, 0);
			GPoint p3 = gw.drawPolarLine(p2.getX(), p2.getY(), edge, THETA * 2);
			drawTrianglee(p1, p2, p3, order, gw);       
		}
	}
    return 0;
}
