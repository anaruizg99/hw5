#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool backtrack(
		size_t slot, 
		size_t n, 
		size_t k, 
		size_t d,
		const AvailabilityMatrix& avail, 
		const size_t maxShifts,
		vector<size_t>& usedShifts,
		DailySchedule& sched)
		{
			if(slot == n*d)
			{
				return true;
			}
			size_t day = slot/d;
			size_t pos = slot%d;

			for(Worker_T w = 0; w < k; ++w)
			{
				if(!avail[day][w])
				{
					continue;
				}

				bool working = false;
				for(size_t j =0; j < pos; ++j)
				{
					if(sched[day][j] == w)
					{
						working = true;
						break;
					}
				}
				if(working)
				{
					continue;
				}
				if(usedShifts[w] >= maxShifts)
				{
					continue;
				}
				sched[day][pos] = w;
				++usedShifts[w];

				if(backtrack(slot +1, n, k, d, avail, maxShifts, usedShifts, sched))
				{
					return true;
				}

				--usedShifts[w];
				sched[day][pos] = INVALID_ID;
			}

			return false;
		}

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below

		size_t n = avail.size();
		size_t k = avail[0].size();
		size_t d = dailyNeed;

		sched = DailySchedule(n, vector<Worker_T>(d, INVALID_ID));

		vector<size_t> shiftsUsed(k, 0);
		return backtrack(0, n, k, d, avail, maxShifts, shiftsUsed, sched);
}

