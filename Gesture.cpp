#include "Gesture.h"

Gesture::Gesture(int cutoff, int width, int height)
{
	// Setup the first point.
	Point* firstPoint = new Point;
	firstPoint->x = 0;
	firstPoint->y = 0;
	m_points.push_back(firstPoint); // save first point into container.

	// Initialize attributes of the gesture shape.
	m_cutoff = cutoff;
	m_width = width;
	m_height = height;
	m_percent = 0;
	m_enabled = true;
}


Gesture::~Gesture()
{
	// Remove all points.
	//for (std::vector<Point>::iterator i = m_points.
}


void Gesture::Recreate(int cutoff, int width, int height)
{
	// Remove all the current points.
	for (std::vector<Point*>::iterator i = m_points.begin(); i != m_points.end();)
	{
		delete (*i);
		m_points.erase(i++);
	}
	Gesture(cutoff, width, height);
}


// ACCESSORS
int Gesture::GetWidth()
{
	return m_width;
}


int Gesture::GetHeight()
{
	return m_height;
}


int Gesture::GetCutoff()
{
	return m_cutoff;
}


Gesture::Point* Gesture::GetPoint(int pointNumber)
{
	return m_points[pointNumber];
}


Gesture::Point* Gesture::GetPoint()
{
	return m_points.back();
}


std::vector<Gesture::Point*>& Gesture::GetPoints()
{
	return m_points;
}


int Gesture::GetEnabled()
{
	return m_enabled;
}


// MUTATORS
void Gesture::SetWidth(int value)
{
	m_width = value;
}


void Gesture::SetHeight(int value)
{
	m_height = value;
}


void Gesture::SetCutoff(int value)
{
	m_cutoff = value;
}


void Gesture::SetEnabled(int enable)
{
	m_enabled = enable;
}