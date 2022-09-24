#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
#include "gobjects.h"
using namespace std;

const string ORDER_PROMPT = "Enter Sierpinski triangle order: ";
const string EDGE_PROMPT = "Enter triangle edge length: ";
const int THETA = 60;

void drawTriangle(GPoint p1, GPoint p2, GPoint p3, int order, GWindow &gw){
	if(order == 0){
		return;
	}
	GPoint midP1P2((p1.getX() + p2.getX()) / 2.0, (p1.getY() + p2.getY())/2.0);
	GPoint midP2P3((p2.getX() + p3.getX()) / 2.0, (p2.getY() + p3.getY())/2.0);
	GPoint midP3P1((p3.getX() + p1.getX()) / 2.0, (p3.getY() + p1.getY())/2.0);
	gw.drawLine(midP1P2, midP2P3);
	gw.drawLine(midP2P3,midP3P1);
	gw.drawLine(midP3P1, midP1P2);
	drawTriangle(p1, midP1P2, midP3P1, order - 1, gw);
	drawTriangle(midP1P2, p2, midP2P3, order - 1, gw);
	drawTriangle(midP3P1, midP2P3, p3,order - 1, gw);
}

/* asks the user to enter triangle edge,
until the right input is given 
*/
int getEdge(){
	int edge;
	while(true){
		edge = getInteger(EDGE_PROMPT);
		if(edge >= 0){
			return edge;
		}else{
			cout << "Wrong input." << endl;
		} 
	}
}

/* asks the user to enter Sierpinski order,
until the right input is given 
*/
int getOrder(){
	int order;
	while(true){
		order = getInteger(ORDER_PROMPT);
		if(order >= 0){
			return order;
		}else{
			cout << "Wrong input." << endl;
		}
	}
}

int main() {
	int edge = getEdge();
	int order = getOrder();
	GWindow gw(900, 900);
	GPoint p1 = gw.drawPolarLine(gw.getWidth() / 2.0, gw.getHeight() / 2.0 - (edge * sqrt(3.0) / 2.0) * (2.0/3.0), edge, THETA * -2);
	GPoint p2 = gw.drawPolarLine(p1.getX(), p1.getY(), edge, 0);
	GPoint p3 = gw.drawPolarLine(p2.getX(), p2.getY(), edge, THETA * 2);
	drawTriangle(p1, p2, p3, order, gw);
    return 0;
}
