/*
	Magnus, a UCI chess playing engine.
*/

#include "BitBoardUtils.hpp"

double BitBoardUtils::measurePopcntSpeed(U64 testBB, unsigned int (*f)(U64))
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    // use function 10000 times to have an average value
    for (U64 i = 0; i < 10000; i++)
    {
        (*f)(testBB);
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    return time_span.count();
}

void BitBoardUtils::printBitBoard(const U64 &bitBoard)
{
	std::ostringstream strm;
	for(int rank = 7; rank >= 0 ; rank--)
	{
		strm << rank << "|  ";

		for(unsigned int file = 0; file < 8 ; file++)
		{
			char c = BitBoardUtils::isBitSet(bitBoard, file, rank) ? 'X' : '*';
			strm << c << " ";
		}

		strm << std::endl;
	}

	strm << "   ________________" << std::endl;
	strm << "    0 1 2 3 4 5 6 7" << std::endl;

	std::cout << strm.str() << std::endl;
}
