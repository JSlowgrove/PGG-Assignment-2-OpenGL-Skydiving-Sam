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
		int i = -1, count = 0;
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