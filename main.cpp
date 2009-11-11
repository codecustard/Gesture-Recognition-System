#include <vector>
#include <cmath>

#include "Gesture.h"

#define EXPORT extern "C" __declspec(dllexport)

std::vector<Gesture*> gestureList;

double point_distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

// POINTS FUNCTIONS****************
EXPORT double gesture_point_number(double id)
{
	return gestureList[static_cast<int>(id)]->GetPoints().size();
}


EXPORT double gesture_point_x(double id, double index)
{
	int ind = static_cast<int>(index) - 1;
	if (ind < 0)
		ind = 0;

	return gestureList[static_cast<int>(id)]->GetPoints().at(ind)->x;
}


EXPORT double gesture_point_y(double id, double index)
{
	int ind = static_cast<int>(index) - 1;
	if (ind < 0)
		ind = 0;

	return gestureList[static_cast<int>(id)]->GetPoints().at(ind)->y;
}

//END OF POINTS FUNCTIONS**********



EXPORT double gesture_shape_create(double cutoff, double width, double height)
{
	Gesture* newGesture = new Gesture((int)cutoff, (int)width, (int)height);
	gestureList.push_back(newGesture);

	// Return the element that references the new gesture.
	return gestureList.size()-1;
}


EXPORT double gesture_shape_recreate(double id, double cutoff, double width, double height)
{
	// Exit and return error if id is out of range.
	if (id < 0 || id >= gestureList.size())
		return -1;

	// Get the reference to the gesture object we wish to recreate.
	Gesture* gestureToRecreate = gestureList[(int)id];

	gestureToRecreate->Recreate((int)cutoff, (int)width, (int)height);

	return id;
}


EXPORT double gesture_shape_setup(double id, double cutoff, double width, double height)
{
	// Check that the id passed is out of bounds (returning an error value: -1)
	if (id < 0 || id >= gestureList.size())
		return -1;

	// Get the reference to the gesture object we wish to modify.
	Gesture* gestureToModify = gestureList[(int)id];

	// Change gesture's attributes.
	gestureToModify->SetCutoff((int)cutoff);
	gestureToModify->SetWidth((int)width);
	gestureToModify->SetHeight((int)height);

	return 1;
}

EXPORT double gesture_shape_subdivide(double id)
{
	// Check that the id passed is out of bounds (returning an error value: -1)
	if (id < 0 || id >= gestureList.size())
		return -1;

	Gesture* g = gestureList[(int)id];

	int lastX = g->GetPoint()->x;
	int lastY = g->GetPoint()->y;

	std::vector<Gesture::Point> tempPoints;
	for (std::vector<Gesture::Point*>::iterator itr = g->GetPoints().begin(); itr != g->GetPoints().end()-1; ++itr)
	{
		Gesture::Point temp;
		
		tempPoints.push_back((**itr));
		tempPoints.push_back(temp);
		tempPoints.back().x = 0;
		int px = (int)((**(itr+1)).x * 0.5);
		int py = (int)((**(itr+1)).y * 0.5);
		tempPoints.back().x = px;
		tempPoints.back().y = py;
	}

	// Clear the current points list of this object.
	while (g->GetPoints().size() > 0)
	{
		delete g->GetPoints().back();
		g->GetPoints().erase(g->GetPoints().end());
	}

	// Copy values tempPoints to the points list of this object.
	while (g->GetPoints().size() < tempPoints.size())
	{
		g->GetPoints().push_back(new Gesture::Point);
		g->GetPoints().back()->x = tempPoints[g->GetPoints().size()-1].x;
		g->GetPoints().back()->y = tempPoints[g->GetPoints().size()-1].y;
	}

	// Copy the last point.
	g->GetPoints().push_back(new Gesture::Point);
	g->GetPoints().back()->x = lastX;
	g->GetPoints().back()->y = lastY;

	return 1;
}



EXPORT double gesture_shape_addpoint(double id, double x, double y)
{
	// Check if the id is out of range and return an error (-1)
	if (id < 0 || id >= gestureList.size())
		return -1;

	// Allocate memory for the new point object.
	Gesture::Point* newPoint = NULL;
	newPoint = new Gesture::Point;

	// If memory was not allocated, return an error (-1)
	if (newPoint == NULL)
		return -1;

	// Retrieve a reference to the gesture and add a point.
	Gesture* g = gestureList[(int)id];
	g->GetPoints().push_back(newPoint);
	g->GetPoints().back()->x = (int)x;
	g->GetPoints().back()->y = (int)y;

	return 1;

}


EXPORT double gesture_shape_mirror(double id, double replace)
{
	// Exit and return error if id is out of bounds
	if (id < 0 || id >= gestureList.size())
		return -1;

	//Cast id to type: int
	int ID = static_cast<int>(id);

	Gesture* g = gestureList[ID]; // Retrieve a reference to the id object.
	int gestureID;

	// To replace or not to replace.
	if (replace == 0)
		gestureID = static_cast<int>(gesture_shape_create(g->GetCutoff(), g->GetWidth(), g->GetHeight()));
	else
		gestureID = ID;

	for (std::vector<Gesture::Point*>::iterator it = g->GetPoints().begin(); it != g->GetPoints().end(); ++it)
	{
		(*it)->x *= -1;
	}

	return gestureID;
}


EXPORT double gesture_shape_rotate(double id, double angle, double replace)
{
	if (id < 0 || id >= gestureList.size())
		return -1;

	// Cast id to type: int
	int ID = static_cast<int>(id);

	Gesture* g = gestureList[ID]; // Retrieve a reference to the id object.
	int gestureID;

	// To replace or not to replace.
	if (replace == 0)
		gestureID = static_cast<int>(gesture_shape_create(g->GetCutoff(), g->GetWidth(), g->GetHeight()));
	else
		gestureID = ID;

	for (std::vector<Gesture::Point*>::iterator it = g->GetPoints().begin(); it != g->GetPoints().end(); ++it)
	{
		//Rotate
//		(*it)->x = 
//		(*it)->y
	}

	return gestureID;
}


EXPORT double gesture_shape_flip(double id, double replace)
{
	double ID;
	if (replace == 0)
	{
		Gesture* g = gestureList[static_cast<int>(id)];
		ID = gesture_shape_create(g->GetCutoff(), g->GetWidth(), g->GetHeight());
	}
	else
		ID = id;

	// Loop through all the points and invert the Y value of each point.
	for (int i = 0; i < static_cast<int>(gestureList[static_cast<int>(ID)]->GetPoints().size()); ++i)
	{
		gestureList[static_cast<int>(ID)]->GetPoints().at(i)->y *= -1;
	}

	return ID;
}


EXPORT double gesture_shape_reverse(double id, double replace)
{
	double ID;
	std::vector<Gesture::Point*> tempPoints; // Temp to store points so we can do switch-a-roo (t=a, a=b, b=t)

	int tempxo, tempyo; // Don't know what these shits are for.

	if (replace == 0)
	{
		Gesture* g = gestureList[static_cast<int>(id)];
		ID = gesture_shape_create(g->GetCutoff(), g->GetWidth(), g->GetHeight());
	}
	else
		ID = id;

	for (int i = 0; i < static_cast<int>(gesture_point_number(ID)); ++i)
	{
		tempPoints.push_back(new Gesture::Point);
		tempPoints.back()->x = gestureList[static_cast<int>(ID)]->GetPoints().at(i)->x;
		tempPoints.back()->y = gestureList[static_cast<int>(ID)]->GetPoints().at(i)->y;
	}

	//Don't know what these shits are for.
	tempxo = static_cast<int>(gesture_point_x(ID, gesture_point_number(ID)));
	tempyo = static_cast<int>(gesture_point_y(ID, gesture_point_number(ID)));

	for (int i = 0; i < gesture_point_number(ID); ++i)
	{
		gestureList[static_cast<int>(ID)]->GetPoints().at(i)->x = tempPoints.at(static_cast<int>(gesture_point_number(ID))-1-i)->x - tempxo;
		gestureList[static_cast<int>(ID)]->GetPoints().at(i)->y = tempPoints.at(static_cast<int>(gesture_point_number(ID))-1-i)->y - tempyo;

		delete tempPoints[i];
	}

	return ID;
}


EXPORT double gesture_shape_enable(double id, double enable)
{
	gestureList[static_cast<int>(id)]->SetEnabled(static_cast<int>(enable));

	return id;
}


EXPORT double gesture_shape_enable_all(double enable)
{
	for (int i=0; i <static_cast<int>(gestureList.size()); ++i)
		gestureList[i]->SetEnabled(static_cast<int>(enable));

	return enable;
}

int main()
{
	return 0;
}