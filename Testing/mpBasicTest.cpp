/*=============================================================================

  MyProject: A software package for whatever.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "mpCatchMain.h"
#include "mpMyFunctions.h"
#include <stdexcept>
#include <iostream>
#include <vector>

TEST_CASE( "My first test", "[some group identifier]" ) {
  int a = 5;
  REQUIRE( a < 6 );
}

TEST_CASE( "My second test", "[some group identifier]" ) {
  std::vector<int> a;
  REQUIRE( a.size() == 0 );
}

TEST_CASE( "Check consistency of MyPrimeChecker", "[Prime]" ) {
  REQUIRE( mp::MyPrimeChecker( 1 ) == true );
  REQUIRE( mp::MyPrimeChecker( 2 ) == true );
  REQUIRE( mp::MyPrimeChecker( 3 ) == true );
  REQUIRE( mp::MyPrimeChecker( 4 ) == false );
  REQUIRE( mp::MyPrimeChecker( 29 ) == true );
  REQUIRE( mp::MyPrimeChecker( 125 ) == false );
  REQUIRE( mp::MyPrimeChecker( 1000 ) == false );
}

TEST_CASE( "Check that MyPrimeChecker throws exception when number is not in [1;1000]", "[Prime]" ) {
  REQUIRE_THROWS_AS( mp::MyPrimeChecker( 0 ) , std::domain_error );
  REQUIRE_THROWS_AS( mp::MyPrimeChecker( 1001 ) , std::domain_error );
}