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
void FileLoader::loadOBJFile(std::string fileLocation, std::vector<float> &sortedVertices, 
	std::vector<float> &sortedVertexNormals)
{
	/*file loading message*/
	std::cout << "Loading " << fileLocation << std::endl;

	/*Open the file using a ifstream*/
	std::ifstream file(fileLocation);

	/*local versions of the unsorted vertices and vertex normals*/
	std::vector<float> vertices;
	std::vector<float> vertexNormals;

	/*If the file successfully opens*/
	if (file.is_open())
	{
		/*File loading variables*/
		std::string currentLine;
		std::string type;
		int charPosition;

		/*While there are still lines to be read in from the file*/
		while (getline(file, currentLine))
		{
			/*set the current char position to 0*/
			charPosition = 0;
			/*set to type to nothing*/
			type = "";

			/*loop to get the type of the data in the current line*/
			while (charPosition < (int)currentLine.size() && currentLine.at(charPosition) != ' ')
			{
				/*set the current type*/
				type += currentLine.at(charPosition);

				/*increase the char position*/
				charPosition++;
			}

			/*increase the char position*/
			charPosition++;
			
			/*if the data in the data in the current line is a vertex*/
			if (type == "v")
			{
				/*loop though the coordinates for the vertex*/
				for (int i = 0; i < 3; i++)
				{
					/*test if the end of the string has been reached*/
					if (charPosition < (int)currentLine.size())
					{
						/*store the contents of the number as a coordinate of the vertex*/
						vertices.push_back(loadedFloat(currentLine, charPosition));
					}
					else
					{
						/*set the coordinate to 0.0f*/
						vertices.push_back(0.0f);
					}
				}
			}

			/*if the data in the data in the current line is a vertex normal*/
			if (type == "vn")
			{				
				/*store the contents of the x number to the x position of the vertex normal*/
				vertexNormals.push_back(loadedFloat(currentLine, charPosition));

				/*store the contents of the y number to the y position of the vertex normal*/
				vertexNormals.push_back(loadedFloat(currentLine, charPosition));

				/*store the contents of the z number to the z position of the vertex normal*/
				vertexNormals.push_back(loadedFloat(currentLine, charPosition));
			}

			/*if the data in the data in the current line is a face*/
			if (type == "f")
			{
				/*initialise the value of number*/
				std::stringstream streamLine;

				streamLine.str(currentLine);
				streamLine.get();

				for (int i = 0; i < 3; i++)
				{
					float number;

					streamLine >> number;

					sortedVertices.push_back(vertices[(unsigned int)(number - 1) * 3]);
					sortedVertices.push_back(vertices[(unsigned int)((number - 1) * 3) + 1]);
					sortedVertices.push_back(vertices[(unsigned int)((number - 1) * 3) + 2]);

					streamLine.get();

					streamLine >> number;

					streamLine.get();

					streamLine >> number;

					sortedVertexNormals.push_back(vertexNormals[(unsigned int)(number - 1) * 3]);
					sortedVertexNormals.push_back(vertexNormals[(unsigned int)((number - 1) * 3) + 1]);
					sortedVertexNormals.push_back(vertexNormals[(unsigned int)((number - 1) * 3) + 2]);

					/*look without kill = .peek()*/
				}
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

/*Get the value of the next float in the string.*/
float FileLoader::loadedFloat(std::string currentLine, int &charPosition)
{
	/*initialise the value of number*/
	std::string number = "";

	/*loop until the next space or the end of the string*/
	while (currentLine.at(charPosition) != ' ')
	{
		/*set the number*/
		number += currentLine.at(charPosition);

		/*increase the char position*/
		charPosition++;

		/*check if the end of the line has been reached*/
		if (charPosition >= (int)currentLine.size())
		{
			/*escape the loop*/
			break;
		}
	}

	/*increase the char position*/
	charPosition++;

	/*store the contents of number to the x position of the vertex*/
	return (float)std::atof(number.c_str());
}