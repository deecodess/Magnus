#include <vector>
#include <memory>
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>

#include "Types.hpp"
#include "Eval.hpp"
#include "Search.hpp"
#include "Board.hpp"
#include "MoveGen.hpp"
#include "Move.hpp"
#include "MagicMoves.hpp"
#include "Utils.hpp"
#include "Uci.hpp"
#include "TT.hpp"

//#define PERFORMANCE_TEST


int main() {

    // Init engine parameters
	MagicMoves::initmagicmoves();
	Tables::init();
	ZK::initZobristKeys();
    
    Uci uci;
    uci.init();

	#ifdef PERFORMANCE_TEST

		Utils::getPerformanceIndicator();

	#else

		uci.loop();

	#endif

	return 0;
}
