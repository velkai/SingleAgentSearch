//
//  STP.h
//  HW1
//

#ifndef STP_h
#define STP_h

#include <stdio.h>
#include <vector>

const int kMaxWidth = 3;
const int kMaxHeight = 5;


// ENUM Slide operators
enum STPSlideDir  {

    kUp,
	kDown,
	kRight,
	kLeft
};

class STPState {

public:
	
    STPState();   // Init to goal state - default constructor will copy
	void Reset(); // Reset to goal state
	int tiles[kMaxWidth][kMaxHeight];
	int blankx, blanky;
};

std::ostream& operator<<(std::ostream& out, const STPState& s);
bool operator==(const STPState &s1, const STPState &s2);

class STP {
public:
	void GetSuccessors(STPState &s, std::vector<STPState> &states);
	void GetOperators(STPState &s, std::vector<STPSlideDir> &operators);
	void ApplyOperator(STPState &s, STPSlideDir o);
	void UndoOperator(STPState &s, STPSlideDir o);
};

void DoRandomWalkSuccessors(STP &puzzle, STPState &s, int length);
void DoRandomWalkOperators(STP &puzzle, STPState &s, int length);

#endif /* STP_hpp */