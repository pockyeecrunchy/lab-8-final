#include "Standard.h"

int ReturnRandomNumber(int min, int max)
{
	/*
	* NOTE: Call srand(static_cast<unsigned int>(time(0));
	*       from the top of your main function
	*/


	// Return a random number between min and max
	return (rand() % (max + 1 - min)) + min;
}

void CenterString(ostream& out, string stringData, int widthToCennerAccross)
{
	// Calculate the width to center the string
	int width = (static_cast<int>(stringData.length()) + widthToCennerAccross) / 2;

	// Print the string centered to the desired output stream
	out << setw(width) << stringData << endl;
}

void PrintDivider(ostream& out, char character, int width)
{
	// Print divider
	out << setfill(character) << setw(width) << character << setfill(SPACE) << endl;
}

void PrintHeader(ostream& out, char dividerCharacter)
{
	PrintDivider(out, dividerCharacter, SCREEN_WIDTH);
	CenterString(out, SCHOOL, SCREEN_WIDTH);
	CenterString(out, LAB, SCREEN_WIDTH);
	CenterString(out, NAME, SCREEN_WIDTH);
	PrintDivider(out, dividerCharacter, SCREEN_WIDTH);
}

