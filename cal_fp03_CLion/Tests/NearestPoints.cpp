/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {

	double min = MAX_DOUBLE;
	Point p1, p2;

	for (int i = 0; i < vp.size(); i++){
	    for (int j = i + 1; j < vp.size(); j++){
            if (vp[i].distance(vp[j]) < min) {
                min = vp[i].distance(vp[j]);
                p1 = vp[i];
                p2 = vp[j];

            }
	    }
	}

	Result res(min, p2, p1);

	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);
	return nearestPoints_BF(vp);
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{
    for (int i = left; i < right; i++){
        for (int j = i + 1; j < right; j++){
            double distance = vp[i].distance(vp[j]);

            if (distance < res.dmin) {
                res.dmin = distance;
                res.p1 = vp[i];
                res.p2 = vp[j];
            }
        }
    }
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
	// Base case of two points
	if (vector<Point>(vp.begin() + left, vp.begin() + right + 1).size() <= 3)
	    return nearestPoints_BF(vp);

	Result r, l;
	int mid = (left + right) / 2;

	// Side recursive calls using threads
    if (numThreads > 1) {
        thread t([&](){l = np_DC(vp,left,mid, numThreads/2);});
        r = np_DC(vp, mid+1, right, numThreads /2);
        t.join();
    }
    else{
        l = np_DC(vp,left,mid, 1);
        r = np_DC(vp, mid+1, right, 1);
    }

    Result min;
    if (r.dmin < l.dmin){
        min.dmin = r.dmin;
        min.p1 = r.p1;
        min.p2 = r.p2;
    }
    else{
        min.dmin = l.dmin;
        min.p1 = l.p1;
        min.p2 = l.p2;
    }

    // Defining strip middle area
    float stripMid = (vp[mid].x + vp[mid+1].x) / 2.0;

    int first = -1, last = -1;
    for (int i = 0; i < vp.size(); i++){
        if ((stripMid - vp[i].x) <= min.dmin && first == -1) {
            first = i;
            continue;
        }
        if (first != -1 && (vp[i].x - stripMid) > min.dmin){
            last = i;
            break;
        }
        else last = i;
    }

    sortByY(vp, first, last); //order y
    npByY(vp, first, last, min); //calculate nearest points
    sortByX(vp, left, right); //resets order

    return min;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
