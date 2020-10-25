/*
 * Author: Domenic Catalano (100556614) & Duy Tan Vu (100750366)
 * Date: Sunday, October 25, 2020
 * Program Description: Lab 5 - Standard Template Library
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>

#include "Vector2D.h"

int main()
{
	try
	{
		/************************
		 *	DECLARATIONS
		 ************************/

		 // Declaring a map with a key type of string and a value type of Vector2D
		std::map<std::string, Vector2D<double>*> pointObject;

		std::string pointName;			// String to hold the name of the point
		double x;						// Holds the x value
		double y;						// Holds the y value
		double totalDistance = 0.0;		// Hold the total distance between all points


		// Using Vector2D to create two new points for comparison
		auto* firstPoint = new Vector2D<double>(x = 0, y = 0);
		auto* secondPoint = new Vector2D<double>(x = 0, y = 0);

		/******************************************************************************
		 *	Reading Labels/Points into the Map:
		 *	Attempt to open the data file.  If the data file opens, read a label,
		 *	followed by a point and insert them into the map using the label as the key.
		 *	Repeat until all the data is read and close the file. If the data file did
		 *	not open, tell the user and remind them to check that the file exists. If
		 *	the file opened but the map is empty after the input loop, report that to
		 *	the user and remind them to check that the file contains valid data in
		 *	the correct format. Only continue processing if the file was opened and the
		 *	map is not empty.
		 ******************************************************************************/

		 // Declaration of an ifstream called infile with a fileName of the file we will be opening
		std::ifstream infile;
		std::string fileName = "MockDataForTesting.txt";

		// Opens the file
		infile.open(fileName.c_str());

		// Checks whether the file is open or not
		if (infile.is_open())
		{
			// Check if file is empty or not
			if (infile.peek() == std::ifstream::traits_type::eof())
			{
				std::cout << "The map is empty. Check that file contains valid data in the correct format.\n";
			}

			// While the file has not failed (failbit is not set) store the contents of the file into
			// our pointObject
			//int counter = 0;	// Holds value of how many points have read from the file
			while (!infile.fail())
			{
				infile >> pointName;
				infile.ignore(1, ' ');	
				infile.ignore(1, '(');
				infile >> x;
				infile.ignore(1, ',');
				infile.ignore(1, ' ');
				infile >> y;
				infile.ignore(1, ')');

				auto* temp_point = new Vector2D<double>(x, y);
				pointObject[pointName, x, y] = temp_point;
				//++counter;
			}
			// Close the file after all data is copied
			infile.close();
		}
		// If the file does not exist, display error message to the user
		else
		{
			std::cout << fileName << " could not be opened for input. Check that the file exists.\n";
		}

		/******************************************************************************
		 *	Determine the Total Distance Between All Points in Order:
		 *	Use an iterator and a loop to traverse each label/point in the map. For
		 *	each label/point, determine the distance from that point to the previous
		 *	point (or next point depending on how you implement this) and add that
		 *	distance to a total.  Note that the Vector2D class includes a static
		 *	distance function to determine the distance between two Vector2D
		 *	objects, so you should not need to use any complicated math here.  Report
		 *	to the user how many points the map contains and what the total distance is.
		 ******************************************************************************/

		// For loop will iterate through all points and calculate the total distance between them all
		for (auto i = pointObject.begin(); i != pointObject.end(); ++i)
		{
			// Calculate distance
			//auto distance = Vector2D<double>::Distance(i->second.GetPosition(), (i++)->second.GetPosition());
			std::cout << i->first << " | " << (i->second << std::endl;
			//totalDistance += distance;
		}

		 /******************************************************************************
		  *	Determine the Distance Between the Start Point and a User Selected Point:
		  *	Prompt the user to enter a label or to enter "quit" to end.  If the user
		  *	entered anything other than "quit", attempt to find the label they entered
		  *	in the map. If it was found, report the distance between the point for the
		  *	label they entered and the start point (i.e. the point labeled "AA").
		  *	Otherwise, tell the user that the label they entered is not in the map.
		  *	Repeat these steps until the user enters "quit".
		  ******************************************************************************/

	}
	/******************************************************************************
	 *	Exception Handling:
	 *	Catch any std::exception thrown. Report to the user that a run-time error
	 *	occurred and show what exception was thrown.
	 ******************************************************************************/
	catch (std::exception& e)  // an exception was thrown
	{
		std::cerr << "An error occurred at run time: " << e.what() << std::endl;
	}
	return 0;
}

