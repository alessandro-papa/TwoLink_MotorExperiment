/**
 *  Michael Meindl
 *  11.12.2019
 *  Method definitions for CTargetFileAccess.
 */
#include "CTargetFileAccess.h"

bool CTargetFileAccess::readScalarFromFile(const std::string& file, float& scalar)
{
	std::ifstream stream;
	std::string   data;

	stream.open(file);
	stream >> data;
	scalar = std::stof(data);
	stream.close();
	return true;
}
bool CTargetFileAccess::writeScalarToFile(const std::string& file, float& scalar)
{
	std::ofstream stream;

	stream.open(file, std::ofstream::out);
	stream << scalar << std::endl;
	stream.close();
	return true;
}
int CTargetFileAccess::getSquareMatrixDimensionFromFile(const std::string& file)
{
	std::ifstream stream;
	std::string data;
	stream.open(file);
	stream >> data;

	int n = std::count(data.begin(), data.end(), ',');
	stream.close();
	return n+1;
}
