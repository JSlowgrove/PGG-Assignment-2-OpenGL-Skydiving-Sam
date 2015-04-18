#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 

/**
@brief A namespace that contains functions to load in files.
@author Jamie Slowgrove
*/
namespace FileLoader
{
	/**
	Load the contents of a text file in to a std::string.
	@param fileName The file name.
	@return The contents of the file in a single std::string.
	*/
	std::string loadShaderFile(std::string fileName);

	/**
	Load the contents of an obj file.
	@param objFileName The name of the obj file.
	@param vertices The vertices vector array to push to.
	@param vertexNormals The vertex normals vector array to push to.
	@param vertexTextures The vertex texture vector array to push to.*/
	void loadOBJFile(std::string objFileName, std::vector<float> &vertices,
		std::vector<float> &vertexNormals, std::vector<float> &vertexTextures);

	/**
	Load in the XYZ coordinate from the line.
	@param streamLine The current stringstream.
	@param vectorArray The vector array to push to.
	*/
	void loadXYZFloats(std::stringstream &streamLine, std::vector<float> &vectorArray);

	/**
	Load in the UV coordinate from the line.
	@param streamLine The current stringstream.
	@param vectorArray The vector array to push to.
	*/
	void loadUVFloats(std::stringstream &streamLine, std::vector<float> &vectorArray);

	/**
	Sort the data using the indices of the faces to order the data.
	@param streamLine The current stringstream.
	@param loadedVertices The vector array of the loaded vertices.
	@param loadedVertexNormals The vector array of the loaded vertex normals.
	@param loadedVertexTextures The vector array of the loaded vertex textures.
	@param vertices The vertices vector array to push to.
	@param vertexNormals The vertex normals vector array to push to.
	@param vertexTextures The vertex textures vector array to push to.
	*/
	void sortWithIndices(std::stringstream &streamLine, 
		std::vector<float> &loadedVertices,	std::vector<float> &loadedVertexNormals, 
		std::vector<float> &loadedVertexTextures, std::vector<float> &vertices, 
		std::vector<float> &vertexNormals, std::vector<float> &vertexTextures);
}