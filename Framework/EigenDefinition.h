#ifndef EIGENDEFINITION_H
#define EIGENDEFINITION_H
#include "Eigen"

using CMatrix = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;
using CVector = Eigen::Matrix<float, Eigen::Dynamic, 1>;

template<int cNbrOfRows, int cNbrOfCols>
using TMatrix = Eigen::Matrix<float, cNbrOfRows, cNbrOfCols>;

template<int cNbrOfRows>
using TVector = Eigen::Matrix<float, cNbrOfRows, 1>;

#endif
