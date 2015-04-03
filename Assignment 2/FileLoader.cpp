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

/*Load the contents of a obj file.*/
void FileLoader::loadOBJFile(std::string fileLocation, std::vector<float> &vertices, 
	std::vector<float> &vertexNormals)
{
	/*file loading message*/
	std::cout << "Loading " << fileLocation << std::endl;

	/*Open the file using a ifstream*/
	std::ifstream file(fileLocation);

	/*local versions of the unsorted vertices and vertex normals*/
	std::vector<float> loadedVertices;
	std::vector<float> loadedVertexNormals;

	/*If the file successfully opens*/
	if (file.is_open())
	{
		/*File loading variables*/
		std::string currentLine;

		/*While there are still lines to be read in from the file*/
		while (getline(file, currentLine))
		{
			std::string lineType;
			std::stringstream streamLine;
			streamLine.str(currentLine);

			streamLine >> lineType;
			
			/*if the data in the data in the current line is a vertex*/
			if (lineType == "v")
			{
				loadXYZFloats(streamLine, loadedVertices);
			}

			/*if the data in the data in the current line is a vertex normal*/
			if (lineType == "vn")
			{				
				loadXYZFloats(streamLine, loadedVertexNormals);
			}

			/*if the data in the data in the current line is a face*/
			if (lineType == "f")
			{
				sortWithIndices(streamLine, loadedVertices, loadedVertexNormals, vertices, vertexNormals);
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

void FileLoader::loadXYZFloats(std::stringstream &streamLine, std::vector<float> &vectorArray)
{
	for (int i = 0; i < 3; i++)
	{
		float number;

		streamLine >> number;

		vectorArray.push_back(number);
	}
}

/**************************************************************************************************************/

void FileLoader::sortWithIndices(std::stringstream &streamLine, std::vector<float> &loadedVertices,
	std::vector<float> &loadedVertexNormals, std::vector<float> &vertices, std::vector<float> &vertexNormals)
{
	for (int i = 0; i < 3; i++)
	{
		float number;

		streamLine >> number;

		vertices.push_back(loadedVertices[(unsigned int)(number - 1) * 3]);
		vertices.push_back(loadedVertices[(unsigned int)((number - 1) * 3) + 1]);
		vertices.push_back(loadedVertices[(unsigned int)((number - 1) * 3) + 2]);

		streamLine.get();

		streamLine >> number;

		streamLine.get();

		streamLine >> number;

		vertexNormals.push_back(loadedVertexNormals[(unsigned int)(number - 1) * 3]);
		vertexNormals.push_back(loadedVertexNormals[(unsigned int)((number - 1) * 3) + 1]);
		vertexNormals.push_back(loadedVertexNormals[(unsigned int)((number - 1) * 3) + 2]);

		/*look without kill = .peek()*/
	}
}