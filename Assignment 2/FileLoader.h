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

	void loadOBJFile(std::string fileLocation, std::vector<float> &ertices, std::vector<float> &vertexNormals);

	void loadXYZFloats(std::stringstream &streamLine, std::vector<float> &vectorArray);

	void sortWithIndices(std::stringstream &streamLine, std::vector<float> &loadedVertices,
		std::vector<float> &loadedVertexNormals, std::vector<float> &vertices, std::vector<float> &vertexNormals);
}