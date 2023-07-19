
#include "catch.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "knight check" )
{
	Tables::init();
	Board fb = Board("8/8/k7/2N5/8/8/4K3/1n6 b - -");
	fb.updateKingAttackers();

	REQUIRE(fb.isCheck() == true);
	fb = Board("8/8/k7/2N5/8/8/4K3/1n6 w - -");
	REQUIRE(fb.isCheck() == false);
}

TEST_CASE( "rook check" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	Board fb = Board("7n/8/k2R4/3r4/8/8/4K3/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);

	fb = Board("7n/8/k2R4/3r4/8/8/4K3/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);
}

TEST_CASE( "bishop check" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	Board fb = Board("2B3Rn/1r6/k7/8/2b5/8/4K3/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);

	fb = Board("2B3Rn/1r6/k7/8/2b5/8/4K3/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);
}

TEST_CASE( "queen check" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	Board fb = Board("6q1/6q1/6q1/6q1/8/2k2K2/8/Q7 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);

	fb = Board("6q1/6q1/6q1/6q1/8/2k2K2/8/Q7 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);
}

TEST_CASE( "king check" )
{
	Tables::init();
	Board fb = Board("8/8/1k6/8/8/3K4/8/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);

	fb = Board("8/8/1k6/8/8/3K4/8/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);

	fb = Board("8/8/8/8/2k5/3K4/8/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);

	fb = Board("8/8/8/8/2k5/3K4/8/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);
}

TEST_CASE( "pawn check" )
{
	Tables::init();

	Board fb = Board("8/8/8/8/2k2p2/6K1/2P5/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);

	fb = Board("8/8/8/8/2k2p2/6K1/2P5/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);

	fb = Board("2k5/3P3p/6K1/8/8/8/8/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);

	fb = Board("2k5/3P3p/6K1/8/8/8/8/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);
}

