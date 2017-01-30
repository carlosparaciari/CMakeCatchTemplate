/*=============================================================================

  MyProject: A software package for whatever.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "mpMyFunctions.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

namespace mp {

//-----------------------------------------------------------------------------
double MyFirstFunction(int a)
{
  return 0;
}

//-----------------------------------------------------------------------------
bool MyPrimeChecker(int number)
{
  double number_sqrt;
  int reminder;
  int max_divider;
  int min_divider = 2;
  bool is_prime = true;

  if( number <= 0 or number >= 1001 ) {
  	throw std::domain_error("Number is not in the range [1;1000].");
  }

  if( number == 1 or number == 2 ) {
  	return is_prime;
  }

  number_sqrt = sqrt( double( number ) );
  max_divider = int( ceil( number_sqrt ) );

  for( int divider = min_divider ; divider <= max_divider ; divider++ ) {
  	reminder = number % divider;
  	if(reminder == 0) {
  		is_prime = false;
  		break;
  	}
  }

  return is_prime;
}

} // end namespace
