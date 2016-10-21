// Library for Creating tests
// Test classes have all functions of regular classes, 
// but they return dummy values (and don't access stuff like I2C,
// so you can run basic tests from just the Arduino itself

// Imports all necessary libraries

/* How to use:
include CSTests.h
Change all your object declarations to their test equivalent, ex:
	CSMag -> CSMagTest
	CSimu -> CSimuTest
That should be it! Should now run no problem!
*/

#include "Tests/CSMagTest.h"
#include "Tests/CSimuTest.h"
