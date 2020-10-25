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
		std::map<std::string, Vector2D<int>*> pointObject;

		std::string pointName;			// String to hold the name of the point
		int x;						// Holds the x value
		int y;						// Holds the y value
		float totalDistance = 0.0f;		// Hold the total distance between all points

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
		std::string fileName = "PointData.dat";

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
			else
			{
				// While the file has not failed (failbit is not set) store the contents of the file into
				// our pointObject
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

					auto* temp_point = new Vector2D<int>(x, y);
					pointObject[pointName] = temp_point;
				}
				// Close the file after all data is copied
				infile.close();
			}

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
		for (auto itr = pointObject.begin(); /*check for condition inside the loop to avoid dereferencing end() pointer*/; ++itr)
		{
			auto tempItr = itr;
			++tempItr;
			if (tempItr == pointObject.end())
			{
				break;
			}
			auto distance = Vector2D<int>::Distance(*(itr->second), *(std::next(itr)->second));
			totalDistance += distance;
		}

		std::cout << "The map contains " << pointObject.size() << " and a total distance of " << totalDistance << std::endl << std::endl;

		/******************************************************************************
		 *	Determine the Distance Between the Start Point and a User Selected Point:
		 *	Prompt the user to enter a label or to enter "quit" to end.  If the user
		 *	entered anything other than "quit", attempt to find the label they entered
		 *	in the map. If it was found, report the distance between the point for the
		 *	label they entered and the start point (i.e. the point labeled "AA").
		 *	Otherwise, tell the user that the label they entered is not in the map.
		 *	Repeat these steps until the user enters "quit".
		 ******************************************************************************/
		while (true)
		{
			std::string input;
			std::cout << "Enter the label of the point you wish to go to (\"quit\" to end): ";
			std::cin >> input;
			if (input == "quit")
			{
				break;
			}
			else
			{
				auto itr = pointObject.find(input);
				if (itr == pointObject.end())
				{
					std::cout << "There is no point labeled \"" << input << "\" in the map." << std::endl << std::endl;
				}
				else
				{
					auto distance = Vector2D<int>::Distance(*(pointObject["AA"]), *(itr->second));
					std::cout << "The distance between AA (0, 0) and " << itr->first << *(itr->second) << " is " << distance << std::endl << std::endl;
				}
			}
		}
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