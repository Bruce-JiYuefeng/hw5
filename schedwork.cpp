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
bool backtrack(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsAssigned, size_t day, size_t shift);

bool canAssignWorker(const AvailabilityMatrix& avail, vector<size_t>& shiftsAssigned, size_t worker, size_t maxShifts) {
    return (shiftsAssigned[worker] < maxShifts);
}

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t days = avail.size();
    size_t workers = avail[0].size();

    sched.resize(days, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> shiftsAssigned(workers, 0);

    return backtrack(avail, dailyNeed, maxShifts, sched, shiftsAssigned, 0, 0);
}

bool backtrack(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsAssigned, size_t day, size_t shift) {
    if (day == sched.size()) {
        return true; 
    }

    if (shift == dailyNeed) {
        return backtrack(avail, dailyNeed, maxShifts, sched, shiftsAssigned, day + 1, 0); 
    }

    for (size_t worker = 0; worker < avail[day].size(); ++worker) {
        if (avail[day][worker] && canAssignWorker(avail, shiftsAssigned, worker, maxShifts)) {
            sched[day][shift] = worker;
            shiftsAssigned[worker]++;

            if (backtrack(avail, dailyNeed, maxShifts, sched, shiftsAssigned, day, shift + 1)) {
                return true; 
            }

            shiftsAssigned[worker]--;
            sched[day][shift] = INVALID_ID;
        }
    }

    return false; 
}