#include "mathLib2D.h"
#include <math.h>

// Point2D Class

/**
*  \brief Default constructor
*  \return Point2D object
*/
Point2D::Point2D() {
	this->mX = 0;
	this->mY = 0;
}

/**
 *  \brief Constructor takes two arguments
 *  \param inX, x coordinate of Point2D
 *  \param inY, y coordinate of Point2D
 *  \return Poing2D
 */
Point2D::Point2D(float inX, float inY) {
	this->mX = inX;
	this->mY = inY;
}

/**
 *  \brief Distance between two vectors
 *  \param other, the second Point2D object
 *  \return float, the distance
 */
float Point2D::distanceTo(Point2D other) {
	return sqrt(pow((this->mX - other.mX), 2) + pow((this->mY - other.mY), 2));
}

/**
 *  \brief Distance without square root
 *  \param other, the second Point2D object
 *  \return float, the distance
 */
float Point2D::fastDistanceTo(Point2D other) {
	return pow((this->mX - other.mX), 2) + pow((this->mY - other.mY), 2);
}

// Vec2D Class

/**
 *  \brief default constructor
 *  \return Vec2D object
 */
Vec2D::Vec2D() {
	this->mX = 0;
	this->mY = 0;
}

/**
 *  \brief Constructor takes two arguments
 *  \param inX, mX of Vec2D
 *  \param inY, mY of Vec2D
 *  \return Vec2D
 */
Vec2D::Vec2D(float inX, float inY) {
	this->mX = inX;
	this->mY = inY;
}

/**
 *  \brief calculates the length of the vector
 *  \return float, the distance
 */
float Vec2D::length() {
	return sqrt(pow((this->mX), 2) + pow((this->mY), 2));
}

/**
 *  \brief Calculates normalized vector
 *  \return vec2D, the normalized vector
 */
Vec2D Vec2D::normalize() {
	if (this->mX == 0 && this->mY == 0) {
		throw "Zero Division";
	}
	float mX = (this->mX) / (this->length());
	float mY = (this->mY) / (this->length());
	return Vec2D(mX, mY);
}

/**
 *  \brief multiplies vector by scalar
 *  \param scalar, the float scalar given
 *  \return Vec2D, the multiplied vector
 */
Vec2D Vec2D::multiply(float scalar) {
	float mX = (this->mX) * scalar;
	float mY = (this->mY) * scalar;
	return Vec2D(mX, mY);
}

/**
 *  \brief Vec2D Creates a vector with two points
 *  \param p1, first Point2D object
 *  \param p2, second Point2D object
 *  \return Vec2D, the created vector from two points
 */

Vec2D Vec2D::createVector(Point2D p1, Point2D p2) {
	float mX = p2.mX - p1.mX;
	float mY = p2.mY - p1.mY;
	return Vec2D(mX, mY);
}

/**
 *  \brief Point2D moved by a vector
 *  \param source, the Point2D object to be moved
 *  \return Point2D, the moved Point2D object
 */
Point2D Vec2D::movePoint(Point2D source) {
	float mX = this->mX + source.mX;
	float mY = this->mY + source.mY;
	return Point2D(mX, mY);
}