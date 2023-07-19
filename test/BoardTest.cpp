
#include "catch.hpp"
#include "Board.hpp"
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "Tables.hpp"
#include "MoveGen.hpp"


TEST_CASE( "is bit Set method" )
{
	//whitePawnStartingPosition
	U64 whitePawns(0LL | 0xFFLL << 8 );

	REQUIRE(BitBoardUtils::isBitSet(0, 5, 5) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 0, 0) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 5, 0) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 5, 5) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 7, 5) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 1, 5) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 5, 1) == true);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 0, 1) == true);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 7, 1) == true);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 2, 1) == true);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 2, 2) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 2, 7) == false);
}

TEST_CASE( "EP squares" )
{
	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("rnbqkb1r/pp1ppppp/5n2/2pP4/8/8/PPP1PPPP/RNBQKBNR w KQkq c6 0 3"));
    REQUIRE(sp->getLastEpSquare() == SQ_C6);

    Move move1(SQ_E2,SQ_E3,Move::QUIET_FLAG,Piece::PAWN);
    Move move2(SQ_E2, SQ_E4, Move::DOUBLE_PAWN_PUSH_FLAG, Piece::PAWN);

	sp->executeMove(move1);
    REQUIRE(sp->getLastEpSquare() == SQ_NONE);

    sp->undoMove(move1);
    REQUIRE(sp->getLastEpSquare() == SQ_C6);

	sp->executeMove(move2);
    REQUIRE(sp->getLastEpSquare() == SQ_E3);

    sp->undoMove(move2);
    REQUIRE(sp->getLastEpSquare() == SQ_C6);
}

TEST_CASE("pop count")
{
  U64 testBoard = 0b1000000000001000000000100000000000000000000;
  unsigned int count = __builtin_popcountll(testBoard);
  REQUIRE(popcount64swar(testBoard) == count);
  REQUIRE(popcount64sparse(testBoard) == count);
  // TODO test the fastest
}

#ifdef NO_POPCNT

TEST_CASE("Test popcount speed")
{
    U64 testBoard = 0b1000000000001000000000100000000000000000000;
    std::cout << "Test 1 : sparse bitboard" << std::endl;
    double t1 = BitBoardUtils::measurePopcntSpeed(testBoard, popcount);
    std::cout << "builtin = " << t1 << std::endl;
    std::cout << "swar = " << BitBoardUtils::measurePopcntSpeed(testBoard, popcount64swar) << std::endl;
    std::cout << "sparse = " << BitBoardUtils::measurePopcntSpeed(testBoard, popcount64sparse) << std::endl;
    
    testBoard = 0b1000010010001000011000101000010001011011000;
    std::cout << "Test 2 : half-sparse bitboard" << std::endl;
    std::cout << "builtin = " << BitBoardUtils::measurePopcntSpeed(testBoard, popcount) << std::endl;
    std::cout << "swar = " << BitBoardUtils::measurePopcntSpeed(testBoard, popcount64swar) << std::endl;
    std::cout << "sparse = " << BitBoardUtils::measurePopcntSpeed(testBoard, popcount64sparse) << std::endl;
}

#endif



