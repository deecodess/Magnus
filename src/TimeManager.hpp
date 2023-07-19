#ifndef TIMEMANAGER_HPP_
#define TIMEMANAGER_HPP_

#include <vector>
#include <iostream>
#include <math.h>


namespace TimeManager
{
	unsigned int divider = 50; //this value is set by the timeDivider Option

	//Note all values are in ms
	unsigned int getTimeAllocatedMiliSec(const unsigned int wtime, const unsigned int btime, const unsigned int winc, const unsigned int binc, const unsigned int movestogo, const Color colorToPlay)
	{

		unsigned int allocatedTimeMiliSec;

		if(movestogo == 0)
		{
			if(colorToPlay == WHITE)
			{
				allocatedTimeMiliSec = winc+(wtime - wtime/divider)/divider;
			}
			else
			{
				allocatedTimeMiliSec = binc+(btime - btime/divider)/divider;
			}
		}
		else
		{
			if(colorToPlay == WHITE)
			{
				allocatedTimeMiliSec = winc+(wtime - wtime/(movestogo+3))/(0.7*movestogo+3);
			}
			else
			{
				allocatedTimeMiliSec = binc+(btime - btime/(movestogo+3))/(0.7*movestogo+3);
			}	
		}

		return allocatedTimeMiliSec;
	}
};


#endif /* TIMEMANAGER_HPP_ */
