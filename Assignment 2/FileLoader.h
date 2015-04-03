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

	/**
	Load the contents of an obj file.
	@param std::string The location of the obj file.
	@param std::vector<float> The verticies vector array to push to.
	@param std::vector<float> The vertex normals vector array to push to.
	@param std::vector<float> The vertex texture vector array to push to.*/
	void loadOBJFile(std::string fileLocation, std::vector<float> &vertices, 
		std::vector<float> &vertexNormals, std::vector<float> &vertexTextures);

	/**
	Load in the XYZ coordinate from the line.
	@param std::stringstream The current stringstream.
	@param std::vector<float> The vector array to push to.
	*/
	void loadXYZFloats(std::stringstream &streamLine, std::vector<float> &vectorArray);

	/**
	Load in the UV coordinate from the line.
	@param std::stringstream The current stringstream.
	@param std::vector<float> The vector array to push to.
	*/
	void loadUVFloats(std::stringstream &streamLine, std::vector<float> &vectorArray);

	/**
	Sort the data using the indices of the faces to order the data.
	@param std::stringstream The current stringstream.
	@param std::vector<float> The vector array of the loaded verticies.
	@param std::vector<float> The vector array of the loaded vertex normals.
	@param std::vector<float> The vector array of the loaded vertex textures.
	@param std::vector<float> The verticies vector array to push to.
	@param std::vector<float> The vertex normals vector array to push to.
	@param std::vector<float> The vertex textures vector array to push to.
	*/
	void sortWithIndices(std::stringstream &streamLine, 
		std::vector<float> &loadedVertices,	std::vector<float> &loadedVertexNormals, 
		std::vector<float> &loadedVertexTextures, std::vector<float> &vertices, 
		std::vector<float> &vertexNormals, std::vector<float> &vertexTextures);
}