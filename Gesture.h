#ifndef GESTURE_H_INCLUDED
#define GESTURE_H_INCLUDED

#include <vector>

class Gesture
{

public:
	struct Point
	{
		int x;
		int y;
	};

	Gesture(int cutoff, int width, int height);
	~Gesture();

	void Recreate(int cutoff, int width, int height);	// Redefine the attributes.

	// ACCESSORS
	int GetWidth();
	int GetHeight();
	int GetCutoff();
	std::vector<Point*>& GetPoints();	// Return a reference to the point container.
	Gesture::Point* GetPoint(int pointNumber);	// Return specific point.
	Gesture::Point* GetPoint();					// Return last point.
	int GetEnabled();							// Returns whether gesture is enabled.

	// MUTATORS
	void SetWidth(int value);
	void SetHeight(int value);
	void SetCutoff(int value);
	void SetEnabled(int enable);


private:
	std::vector<Point*> m_points;

	// Attributes.
	int m_width, m_height;
	int m_cutoff;
	int m_percent;
	int m_enabled;


};

#endif