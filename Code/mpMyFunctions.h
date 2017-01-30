/*=============================================================================

  MyProject: A software package for whatever.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef mpMyFunctions_h
#define mpMyFunctions_h

#include "mpWin32ExportHeader.h"

/**
* \file mpMyFunctions.h
* \brief Various Utilities.
* \ingroup utilities
*/
namespace mp
{

/**
* \brief My first function, computes something.
*/
MYPROJECT_WINEXPORT double MyFirstFunction(int a);

/**
* \brief My Prime Checker, checks whether an integer between 0 and 1000 is prime.
*/
MYPROJECT_WINEXPORT bool MyPrimeChecker(int a);

} // end namespace

#endif
