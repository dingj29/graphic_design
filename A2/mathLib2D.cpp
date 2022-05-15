#include "mathLib2D.h"
#include <math.h>

Point2D::Point2D() {
	this->mX = 0;
	this->mY = 0;
	this->size = 0;
}

Point2D::Point2D(float inX, float inY, float size) {
	this->mX = inX;
	this->mY = inY;
	this->size = size;
}

float Point2D::distanceTo(Point2D other) {
	return sqrt(pow((this -> mX - other.mX), 2) + pow((this -> mY - other.mY), 2));
}

float Point2D::fastDistanceTo(Point2D other) {
	return pow((this -> mX - other.mX), 2) + pow((this -> mY - other.mY), 2);
}

Vec2D::Vec2D() {
	this->mX = 0;
	this->mY = 0;
}

Vec2D::Vec2D(float inX, float inY) {
	this->mX = inX;
	this->mY = inY;
}

float Vec2D::length() {
	return sqrt(pow((this->mX), 2) + pow((this->mY), 2));
}

Vec2D Vec2D::normalize() {
	float mX = (this->mX) / (this->length());
	float mY = (this->mY) / (this->length());
	return Vec2D(mX, mY);
}

Vec2D Vec2D::multiply(float scalar) {
	float mX = (this->mX) * scalar;
	float mY = (this->mY) * scalar;
	return Vec2D(mX, mY);
}

Vec2D Vec2D::createVector(Point2D p1, Point2D p2) {
	float mX = p2.mX - p1.mX;
	float mY = p2.mY - p1.mY;
	return Vec2D(mX, mY);
}

Vec2D Vec2D::addVector(Vec2D other) {
	float mX = this->mX + other.mX;
	float mY = this->mY + other.mY;
	return Vec2D(mX, mY);
}
Point2D Vec2D::movePoint(Point2D source) {
	float mX = this->mX + source.mX;
	float mY = this->mY + source.mY;
	float size = source.size;
	return Point2D(mX, mY, size);
}

Color::Color() {
	this->myRed = 1;
	this->myGreen = 1;
	this->myBlue = 1;
}

Color::Color(float red, float green, float blue) {
	this->myRed = red;
	this->myGreen = green;
	this->myBlue = blue;
}