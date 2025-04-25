#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void build(size_t pos, std::string& working, std::string& pool, const std::string& pattern, std::set<std::string>& out, const std::set<std::string>& dict)
{
    if(pos == working.size()){
        if(pool.empty() && dict.find(working) != dict.end())
        {
            out.insert(working);
        }
        return;
    }
    if(pattern[pos] != '-'){
        build(pos +1,working, pool, pattern, out, dict);
        return;
    }
    size_t blanksRemaining = 0;
    for(size_t i = pos; i < pattern.size(); ++i)
    {
        if(pattern[i] == '-')
        {
            blanksRemaining++;
        }
    }

    bool tried[26] = {false};
    for(size_t idx = 0; idx < pool.size(); ++idx)
    {
        char c = pool[idx];
        if(tried[c - 'a'])
        {
            continue;
        }
        tried[c - 'a'] = true;

        working[pos] = c;
        char saved = c;
        pool.erase(idx, 1);
        build(pos + 1, working, pool, pattern, out, dict);
        pool.insert(pool.begin() + idx, saved);
    }

    if(blanksRemaining > pool.size())
    {
        for(char c = 'a'; c <= 'z'; ++c)
        {
            if(std::find(pool.begin(), pool.end(), c) != pool.end())
            {
                continue;
            }
            working[pos] = c;
            build(pos+1, working, pool, pattern, out, dict);
        }
    }
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> out;
    std::string working = in;
    std::string pool = floating;
    build(0, working, pool, in, out, dict);
    return out;
    // for(size_t i = 0; i < floating.size(); ++i)
    // {
    //     pool.insert(floating[i]);
    // }


}

// Define any helper functions here
