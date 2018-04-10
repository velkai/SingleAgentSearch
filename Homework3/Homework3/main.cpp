//
//  main.cpp
//  HW1
//

#include <iostream>
#include "STP.h"
#include "Timer.h"

int main(int argc, const char * argv[]) {
	STPState s;
	STP stp;
	Timer t;

	std::cout << "Initial state:\n";
	std::cout << s;

	t.StartTimer();
	DoRandomWalkOperators(stp, s, 100000000);
	t.EndTimer();
	
    std::cout << "\n" ;
	std::cout << "After random walk (operators):\n";
	std::cout << s;
	printf("%1.2f seconds elapsed\n", t.GetElapsedTime());

	
	t.StartTimer();
	DoRandomWalkSuccessors(stp, s, 100000000);
	t.EndTimer();
	
	std::cout << "After random walk (successors):\n";
	std::cout << s;
	printf("%1.2f seconds elapsed\n", t.GetElapsedTime());
return 0;
}
