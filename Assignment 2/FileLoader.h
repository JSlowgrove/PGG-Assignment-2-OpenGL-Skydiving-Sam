#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 

/**
@brief A namespace that contains functions to load in files.
*/
namespace FileLoader
{
	/**
	Load the contents of a text file in to a std::string.
	@param std::string The file location.
	@return std::string The contents of the file in a single std::string.
	*/
	std::string loadTextFile(std::string fileLocation);

	void loadOBJFile(std::string fileLocation, std::vector<float> &sortedVertices, std::vector<float> &sortedVertexNormals);

	float loadedFloat(std::string currentLine, int &charPosition);
}