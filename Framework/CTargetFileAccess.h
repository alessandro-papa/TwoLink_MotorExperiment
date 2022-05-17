/**
 *  Michael Meindl
 *  11.12.2019
 *  Declaration of the class CTargetFileAccess, for reading and writing, matrices, vectors, and scalars from CSV-files.
 */
#ifndef CTARGETFILEACCESS_H
#define CTARGETFILEACCESS_H
#include "EigenDefinition.h"
#include <string>
#include <fstream>
#include <algorithm>

class CTargetFileAccess
{
public:
	int getSquareMatrixDimensionFromFile(const std::string& file);
	template<int cNbrOfRows, int cNbrOfCols>
	bool readMatrixFromFile(const std::string&, TMatrix<cNbrOfRows, cNbrOfCols>&);
	template<int cNbrOfRows, int cNbrOfCols>
	bool writeMatrixToFile(const std::string&, TMatrix<cNbrOfRows, cNbrOfCols>&);
	template<int cNbrOfRows>
	bool readVectorFromFile(const std::string&, TVector<cNbrOfRows>&);
	template<int cNbrOfRows>
	bool writeVectorToFile(const std::string&, TVector<cNbrOfRows>&);
	bool readScalarFromFile(const std::string& file, float& scalar);
	bool writeScalarToFile(const std::string& file,float& scalar);
public:
	CTargetFileAccess()                                    = default;
	CTargetFileAccess& operator=(const CTargetFileAccess&) = delete;
	CTargetFileAccess(const CTargetFileAccess&)            = delete;
	~CTargetFileAccess()                                   = default;
};

template<int cNbrOfRows, int cNbrOfCols>
bool CTargetFileAccess::readMatrixFromFile(const std::string& file, TMatrix<cNbrOfRows, cNbrOfCols>& matrix)
{
	std::ifstream stream;
	std::string   data;

	stream.open(file);
	for(auto rowIndex{0}; rowIndex < matrix.rows(); ++rowIndex)
	{
		std::getline(stream, data);
		for(auto colIndex{0}; colIndex < matrix.cols(); ++colIndex)
		{
			std::string tmp {data.substr(0, data.find(','))};
			matrix(rowIndex, colIndex) = std::stof(tmp);
			data = data.substr(data.find(",")+1);
		}
	}
	stream.close();
	return true;
}
template<int cNbrOfRows, int cNbrOfCols>
bool CTargetFileAccess::writeMatrixToFile(const std::string& file, TMatrix<cNbrOfRows, cNbrOfCols>& matrix)
{
	std::ofstream stream;

	stream.open(file, std::ofstream::out);
	for(auto rowIndex{0}; rowIndex < matrix.rows(); ++rowIndex)
	{
		for(auto colIndex{0}; colIndex < matrix.cols(); ++colIndex)
		{
			stream << matrix(rowIndex, colIndex);
			if(colIndex == (matrix.cols()-1) )
			{
				stream << std::endl;
			}
			else
			{
				stream << ", ";
			}
		}
	}
	stream.close();
	return true;
}
template<int cNbrOfRows>
bool CTargetFileAccess::readVectorFromFile(const std::string& file, TVector<cNbrOfRows>& vector)
{
	std::ifstream stream;
	std::string   data;

	stream.open(file);
	for(auto rowIndex{0}; rowIndex < vector.rows(); ++rowIndex)
	{
		std::getline(stream, data);
		vector(rowIndex, 0) = std::stof(data);
	}
	stream.close();
	return true;
}
template<int cNbrOfRows>
bool CTargetFileAccess::writeVectorToFile(const std::string& file, TVector<cNbrOfRows>& vector)
{
	std::ofstream stream;

	stream.open(file, std::ofstream::out);
	for(auto rowIndex{0}; rowIndex < vector.rows(); ++rowIndex)
	{
		stream << vector(rowIndex, 0) << std::endl;
	}
	stream.close();
	return true;
}

#endif
