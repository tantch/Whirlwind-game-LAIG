/*
 * Piece.cpp
 *
 *  Created on: Dec 29, 2014
 *      Author: pim
 */

#include "Piece.h"
using namespace std;
void Piece::moveTo(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
void Piece::draw() {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(-90, 1, 0, 0);
	this->material->apply();
	int slices = 30;
	int stacks = 30;
	GLUquadric * quad, *botD, *topD;
	botD = gluNewQuadric();
	topD = gluNewQuadric();
	gluQuadricNormals(botD, GL_SMOOTH);
	gluQuadricNormals(topD, GL_SMOOTH);
	gluQuadricTexture(botD, GL_TRUE);
	gluQuadricTexture(topD, GL_TRUE);

	glPushMatrix();
	glTranslated(0, 0, 0.3);
	gluDisk(topD, 0, 0.5, slices, stacks);
	glPopMatrix();

	glPushMatrix();
	glRotated(180, 0, 1, 0);
	gluDisk(botD, 0, 0.5, slices, stacks);
	glPopMatrix();

	quad = gluNewQuadric();
	gluQuadricNormals(quad, GL_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);
	gluCylinder(quad, 0.5, 0.5, 0.3, slices, stacks);

	gluDeleteQuadric(quad);
	gluDeleteQuadric(botD);
	gluDeleteQuadric(topD);
	glPopMatrix();
}
void Piece::print(){
	cout<<"x: "<<this->x<<" y: "<<this->y<<" z: "<<this->z<<"\n";
}
Piece::Piece(bool inBoard,int color, float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->color = color;
	this->picked = false;
	this->inBoard = inBoard;
	this->blocked=0;
	float cor;
	if (color == 1) {
		cor = 0.3;
	} else {
		cor = 1;
	}
	float dif[4] = { cor, cor, cor, 1 };
	float spec[4] = { 0.3, 0.3, 0.3, 1 };
	float amb[4] = { cor, cor, cor, 1 };

	this->material = new CGFappearance(amb, dif, spec, 60);

}

Piece::~Piece() {
	// TODO Auto-generated destructor stub
}

void Piece::pick() {
	picked = true;
	float cor;
	if (color == 1) {
		cor = 0.45;
	} else {
		cor = 1;
	}
	float dif[4] = { cor, cor, 0, 1 };
	material->setDiffuse(dif);
}
void Piece::unpick() {
	picked = false;
	float cor;
	if (color == 1) {
		cor = 0.3;
	} else {
		cor = 1;
	}
	float dif[4] = { cor, cor, cor, 1 };
	material->setDiffuse(dif);
}
void Piece::placeInBoard() {
	inBoard = true;
}
void Piece::removeFromBoard() {
	inBoard = false;
}
bool Piece::isInBoard() {
	return inBoard;
}
void Piece::block() {
	blocked=320;
	float cor;
	if (color == 1) {
		cor = 0.7;
	} else {
		cor = 1;
	}
	float dif[4] = { cor, 0, 0, 1 };
	material->setDiffuse(dif);
}
void Piece::unblock() {
	blocked=0;
	float cor;
	if (color == 1) {
		cor = 0.3;
	} else {
		cor = 1;
	}
	float dif[4] = { cor, cor, cor, 1 };
	material->setDiffuse(dif);
}
void Piece::update(unsigned long millis){
	if(blocked <= 0){
		return;
	}
	else{
		blocked-=millis;
		if(blocked < 0){
			unblock();
		}
	}
}
