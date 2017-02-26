/*=============================================================================

  MyProject: A software package for whatever.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include <mpMyFunctions.h>
#include <iostream>
#include <Eigen/Dense>

int main(int argc, char** argv)
{
  std::cout << "Calculating ... " << mp::MyFirstFunction(1) << std::endl;

  int number = 734;
  auto is_prime = mp::MyPrimeChecker(number);

  std::cout << "Is the number " << number << " prime? " << is_prime << std::endl;

  Eigen::MatrixXd m(2,2);

  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);

  std::cout << m << std::endl;

  return 0;
}
