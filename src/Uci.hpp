#ifndef UCI_HPP_
#define UCI_HPP_

#include <vector>
#include <iostream>
#include <math.h>
#include <memory>
#include <chrono>
#include <ctime>
#include <ratio>
#include <map>
#include <thread>


namespace thrd = std;

#include "Board.hpp"
#include "Move.hpp"
#include "UciOption.hpp"
#include "TT.hpp"
#include "Types.hpp"
#include "Search.hpp"

//Uci documentation:
//http://wbec-ridderkerk.nl/html/UCIProtocol.html
typedef std::map<std::string, UciOption> OptionsMap;



class Uci
{
public :

	Uci() : wtime(10000), btime(10000), winc(0), binc(0), movestogo(0),
	myBoardPtr(std::shared_ptr<Board>(new Board())), mySearch(Search(myBoardPtr)), myOptionsMap()
	{
		//Init Options map
		// myOptionsMap["timeDivider"] = UciOption("50", "spin",1,1000);
		// myOptionsMap["positionnalGain"] = UciOption("100", "spin",1,1000);
		// myOptionsMap["mobilityGain"] = UciOption("100", "spin",1,1000);
		// myOptionsMap["pawnGain"] = UciOption("100", "spin",1,1000);
		myOptionsMap["hash"] = UciOption("256", "spin",1,2048); //hash size in MB, default 256 MB
	}

	void loop();
	void init();
    void setoption(std::istringstream& is);
    void printOptions() const;
    void initSearch();
    void newGame();
    std::string getOption(const std::string str) const;

    // get methods    
    inline Search getUciSearch() const {return mySearch;}

private:

	unsigned int wtime;
	unsigned int btime;
	unsigned int winc;
	unsigned int binc;
	unsigned int movestogo;
	std::shared_ptr<Board> myBoardPtr;
	Search mySearch;
	thrd::thread myThread;


	void updatePosition(std::istringstream& is);
	Move strToMove(std::string str);
	void search();

	OptionsMap myOptionsMap;

};


#endif /* UCI_HPP_ */
