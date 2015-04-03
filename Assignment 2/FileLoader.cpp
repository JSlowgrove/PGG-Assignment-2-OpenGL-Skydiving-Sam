#include "FileLoader.h"

/**************************************************************************************************************/

/*Load the contents of a text file in to a std::string.*/
std::string FileLoader::loadTextFile(std::string fileLocation)
{
	/*The loaded file as a string*/
	std::string loadedFile;

	/*Open the file using a ifstream*/
	std::ifstream file(fileLocation);

	/*If the file successfully opens*/
	if (file.is_open())
	{
		/*File loading variables*/
		std::string currentLine;

		/*While there are still lines to be read in from the file*/
		while (getline(file, currentLine))
		{
			/*Add the current line to the loaded file*/
			loadedFile.append(currentLine);

			/*Add a new line symbol to the end of the line*/
			loadedFile.append("\n");
		}
		/*Close the file*/
		file.close();
	}
	/*If the file could not be opened then output error message*/
	else
	{
		std::cout << "Unable to open file";
	}

	/*Return the loaded file as a std::string*/
	return loadedFile;
}


/**************************************************************************************************************/

/*Load the contents of an obj file.*/
void FileLoader::loadOBJFile(std::string fileLocation, std::vector<float> &vertices,
	std::vector<float> &vertexNormals, std::vector<float> &vertexTextures)
{
	/*file loading message*/
	std::cout << "Loading " << fileLocation << std::endl;

	/*Open the file using a ifstream*/
	std::ifstream file(fileLocation);

	/*local versions of the unsorted vertices and vertex normals*/
	std::vector<float> loadedVertices;
	std::vector<float> loadedVertexNormals;
	std::vector<float> loadedVertexTextures;

	/*If the file successfully opens*/
	if (file.is_open())
	{
		/*File loading variables*/
		std::string currentLine;

		/*While there are still lines to be read in from the file*/
		while (getline(file, currentLine))
		{
			/*load the current line in to a stringstream*/
			std::stringstream streamLine;
			streamLine.str(currentLine);

			/*Create a string for the file type*/
			std::string lineType;
			/*load in the first part of the line into the line type*/
			streamLine >> lineType;
			
			/*if the data in the data in the current line is a vertex*/
			if (lineType == "v")
			{
				/*load in the X Y Z coordinates for the vertex*/
				loadXYZFloats(streamLine, loadedVertices);
			}

			/*if the data in the data in the current line is a vertex normal*/
			if (lineType == "vn")
			{			
				/*load in the XYZ coordinates for the vertex normal*/
				loadXYZFloats(streamLine, loadedVertexNormals);
			}

			/*if the data in the data in the current line is a vertex texture*/
			if (lineType == "vt")
			{
				/*load in the UV coordinates for the vertex texture*/
				loadXYZFloats(streamLine, loadedVertexTextures);
			}

			/*if the data in the data in the current line is a face*/
			if (lineType == "f")
			{
				/*sort the loaded data using the faces (indices)*/
				sortWithIndices(streamLine, loadedVertices, loadedVertexNormals, loadedVertexTextures, vertices, vertexNormals,vertexTextures);
			}
		}
		/*Close the file*/
		file.close();
	}
	/*If the file could not be opened then output error message*/
	else
	{
		std::cout << "Unable to open file";
	}

	/*file loaded message*/
	std::cout << "File loaded" << std::endl;
}

/**************************************************************************************************************/

/*Load in the XYZ coordinate from the line.*/
void FileLoader::loadXYZFloats(std::stringstream &streamLine, std::vector<float> &vectorArray)
{
	/*loop for the 3 parts of the coordinate*/
	for (int i = 0; i < 3; i++)
	{
		/*load the next part of the stringstream into a float*/
		float coordinate;
		streamLine >> coordinate;

		/*push the float to the array*/
		vectorArray.push_back(coordinate);
	}
}

/**************************************************************************************************************/

/*Load in the UV coordinate from the line.*/
void FileLoader::loadUVFloats(std::stringstream &streamLine, std::vector<float> &vectorArray)
{
	/*loop for the 2 parts of the coordinate*/
	for (int i = 0; i < 2; i++)
	{
		/*load the next part of the stringstream into a float*/
		float coordinate;
		streamLine >> coordinate;

		/*push the float to the array*/
		vectorArray.push_back(coordinate);
	}
}

/**************************************************************************************************************/

/*Sort the data using the indices of the faces to order the data.*/
void FileLoader::sortWithIndices(std::stringstream &streamLine, 
		std::vector<float> &loadedVertices,	std::vector<float> &loadedVertexNormals, 
		std::vector<float> &loadedVertexTextures, std::vector<float> &vertices, 
		std::vector<float> &vertexNormals, std::vector<float> &vertexTextures)
{
	/*loop through each indices of the face*/
	for (int i = 0; i < 3; i++)
	{
		/*load the next part of the stringstream into a float for the indices of the face*/
		float indices;
		streamLine >> indices;

		/*push back the XYZ coordinates for the vertex at the indices position*/
		vertices.push_back(loadedVertices[(unsigned int)(indices - 1) * 3]);
		vertices.push_back(loadedVertices[(unsigned int)((indices - 1) * 3) + 1]);
		vertices.push_back(loadedVertices[(unsigned int)((indices - 1) * 3) + 2]);
			
		/*remove the slash from the stream*/
		streamLine.get();

		/*load the next part of the stringstream into a float for the indices of the face*/
		streamLine >> indices;

		/*push back the XYZ coordinates for the vertex texture at the indices position*/
		vertexTextures.push_back(loadedVertexTextures[(unsigned int)(indices - 1) * 3]);
		vertexTextures.push_back(loadedVertexTextures[(unsigned int)((indices - 1) * 3) + 1]);
		vertexTextures.push_back(loadedVertexTextures[(unsigned int)((indices - 1) * 3) + 2]);

		/*remove the slash from the stream*/
		streamLine.get();

		/*load the next part of the stringstream into a float for the indices of the face*/
		streamLine >> indices;

		/*push back the XYZ coordinates for the vertex normal at the indices position*/
		vertexNormals.push_back(loadedVertexNormals[(unsigned int)(indices - 1) * 3]);
		vertexNormals.push_back(loadedVertexNormals[(unsigned int)((indices - 1) * 3) + 1]);
		vertexNormals.push_back(loadedVertexNormals[(unsigned int)((indices - 1) * 3) + 2]);

		/*look without kill = .peek()*/
	}
}