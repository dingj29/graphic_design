#include <iostream>
#include "mathLib2D.h"
#include <cassert>
#include <cmath>
#include <random>
#include <vector>
using namespace std;

// to set to lower bound and higher bound of the random generated float
constexpr int FLOAT_MIN = -1000;
constexpr int FLOAT_MAX = 1000;

int main(int argc, char** argv[])
{
	int counter;
	float e = pow(10, -4);
	Point2D point1(2.0, 3.0);
	Point2D point2(3.0, 5.0);
	Point2D point3(0, 0);
	Vec2D vec1(3.0, 4.0);
	Vec2D vec2(4.3, 2.6);
	Vec2D vec3(0.0, 0.0);
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distr(FLOAT_MIN, FLOAT_MAX);
	
	// Some basic testing of the functions
	assert(point1.mX==2 && point1.mY==3);
	std::cout << "basic Point2D corrdinate test passed!"<<endl;

	assert(point3.mX == 0 && point3.mY == 0);
	std::cout << "basic Point2D corrdinate test2 passed!" << endl;
	
	assert(abs(point1.distanceTo(point2) - 2.23607)<e);
	std::cout << "basic distanceTo() function test passed!" << endl;

	assert(abs(point1.distanceTo(point3) - 3.60555) < e);
	std::cout << "basic distanceTo() function test2 passed!" << endl;
	
	assert(vec1.length() == 5.0);
	std::cout << "basic length() function test passed!" << endl;

	assert(vec3.length() == 0.0);
	std::cout << "basic length() function test2 passed!" << endl;

	assert(abs(vec1.normalize().mX - 0.6)<e);
	std::cout << "basic normalize() function test passed!" << endl;

	// check for division by zero error
	try {
		vec3.normalize();
		std::cout << "basic normalize() function test2 failed!"  <<endl;
	}
	catch (const char* msg) {

		std::cout << "basic normalize() function test2 passed! Encountered: " <<msg<< endl;
	}
	
	assert(abs(vec1.multiply(2.0).mX - 6)<e && abs(vec1.multiply(2.0).mY - 8) < e);
	std::cout << "basic multiply() function test passed!" << endl;

	assert(abs(vec3.multiply(4.0).mX - 0) < e && abs(vec3.multiply(7.0).mY - 0) < e);
	std::cout << "basic multiply() function test2 passed!" << endl;

	assert(abs(vec1.createVector(point1, point2).mX - 1.0) < e && abs(vec1.createVector(point1, point2).mY - 2.0) < e);
	std::cout << "basic createVector() function test passed!"<<endl;

	assert(abs(vec1.createVector(point1, point3).mX + 2.0) < e && abs(vec1.createVector(point1, point3).mY + 3.0) < e);
	std::cout << "basic createVector() function test2 passed!" << endl;
	
	assert(abs(vec1.movePoint(point1).mX - 5.0) < e && abs(vec1.movePoint(point1).mY - 7.0) < e);
	std::cout << "basic movePoint() function test passed!" << endl;

	assert(abs(vec3.movePoint(point1).mX - 2.0) < e && abs(vec3.movePoint(point1).mY - 3.0) < e);
	std::cout << "basic movePoint() function test2 passed!" << endl;

	std::cout << "all tests passed!!!" << endl;
	std::cout << " " << endl;

	// Ask for user input
	std::cout << "Please enter the size of the 2D points array"<<endl;
	int length{};
	std::cin >> length;
	std::cout << "generated 2D points:" << endl;

	// use pointer to create a dynamica allocated array with the length user has typed
	Point2D* array{ new Point2D[length] {} };
	for (counter = 0; counter < length; counter++) {
		array[counter] = Point2D((float)distr(eng), (float)distr(eng));
		std::cout << "(" << array[counter].mX << "," << array[counter].mY << ")" << endl;
	}
	std::cout << " " << endl;

	// use std::vector to generate Point2D with the given number entered by user 
	std::cout << "Please enter the size of the vector" << endl;
	int length2;
	std::cin >> length2;
	std::cout << "generted 2D points:" << endl;
	vector<Point2D> v;
	for (counter = 0; counter < length2; counter++) {
		v.push_back(Point2D((float)distr(eng), (float)distr(eng)));
		std::cout << "(" << v[counter].mX << "," << v[counter].mY << ")" << endl;
	}
	return 0;
}
