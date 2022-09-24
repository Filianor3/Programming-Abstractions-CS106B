#include <iostream>
#include "console.h"
#include "simpio.h"
#include "random.h"
#include "vector.h"
#include <string>
#include "gobjects.h"
#include "gwindow.h"
#include <cmath>
#include "strlib.h"
using namespace std;
using namespace std;

const int COIN_SIZE = 40;
const int LOGO_SIZE = 20;
const int COIN_OFFSET = 5;
const int GAP = 5;
const int CANVAS_WIDTH = 920;
// constant which declares on how many consecutive heads the program should stop on
// note: please dont make this value too high or the canvas window will go below the screen
const int COINS_HEAD_AMOUNT = 7;

/*This method randoms the bool with
the chance of true or false (50% each)
returns "heads" if the value is true
else "tails" */
string flipp(){
	if(randomChance(0.5)){
		return "heads";
	}else{
		return "tails";
	} 
}

/* Draws the head side of the coin */
void drawHead(double x, double y, GWindow display){
	GOval *oval = new GOval(x, y, COIN_SIZE, COIN_SIZE);
	oval->setFilled(true);
	oval->setFillColor("ORANGE");
	display.add(oval);
	GOval *logo = new GOval(x + 10, y + 10, LOGO_SIZE, LOGO_SIZE);
	logo -> setFilled(true);
	logo -> setColor("BLACK");
	display.add(logo);
	GLine *line1 = new GLine(x + COIN_SIZE/2, y , x + COIN_SIZE/2, y + COIN_SIZE);
	GLine *line2 = new GLine(x, y + COIN_SIZE / 2, x + COIN_SIZE, y + COIN_SIZE / 2);
	display.add(line1);
	display.add(line2);
}

/* Draws the tails side of the coin */
void drawTails(double x, double y, GWindow display){
	GOval *oval = new GOval(x, y, COIN_SIZE, COIN_SIZE);
	oval->setFilled(true);
	oval->setFillColor("ORANGE");
	display.add(oval);
	GLabel *price = new GLabel("20", x + 10, y + 27);
	price->setFont("BOLD-20");
	display.add(price);
}


/* draws the result gline at the bottom of the window */
void drawResult(Vector<string> vec){
	GWindow gw(300,120);
    GLabel *label = new GLabel("It took " + integerToString(vec.size()) +" attempts to");
	GLabel *label2 = new GLabel("reach " + integerToString(COINS_HEAD_AMOUNT) + " consecutive heads");
	label2->setFont("SansSerif-18");
    label->setFont("SansSerif-18");
    double x1 = (gw.getWidth() - label->getWidth()) / 2;
    double y1 = (gw.getHeight() + label->getFontAscent()) / 2;
	double x2 = (gw.getWidth() - label2->getWidth()) /2;
	double y2 = (gw.getHeight() + label->getFontAscent()) / 2 + 20;
    gw.add(label, x1, y1);
	gw.add(label2, x2,y2);
}

/* Iterates over the vector of the results which were
randomed in the main program and draws the coins*/
void addVisualResults(Vector<string> vec){
	double x = COIN_OFFSET;
	double y = COIN_OFFSET;
	double canv_height = (vec.size() / 20 + 1) * COIN_SIZE + 100;
	GWindow display(CANVAS_WIDTH, canv_height);
	for(int i = 0; i < vec.size(); i++){
		if(i % 20 == 0 && i != 0){
			y += COIN_SIZE + GAP;
			x = COIN_OFFSET;
		}
		if(vec.get(i) == "heads"){
			drawHead(x, y, display);
			x += GAP + COIN_SIZE;
		}else{
			drawTails(x, y, display);
			x += GAP + COIN_SIZE;
		}
		pause(20);
	}
	pause(600);
	drawResult(vec);
}

/* Main program */
int main() {
	Vector<string> vec;
	double sum = 0;
	int counter = 0;
	int attempts = 0;
	while(counter != COINS_HEAD_AMOUNT){
		attempts++;
		if(flipp() == "heads"){
			counter++;
			vec.add("heads");
		}else{
			vec.add("tails");
			counter = 0;
		}
	}
	addVisualResults(vec);
	return 0;
}
