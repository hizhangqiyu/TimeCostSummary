/*MIT License

Copyright (c) 2019 QiYu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
============================================================================*/

#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <map>

#ifndef __TIMER_H__
#define __TIMER_H__

#define TIMECOST_START(n) TimeCost::Summary::getInstance()->start(n)
#define TIMECOST_END(n) TimeCost::Summary::getInstance()->end(n)
#define TIMECOST_VERBOSE_END(n) TimeCost::Summary::getInstance()->end(n, true)

#define TIMECOST_RAII(n) TimeCost::SummaryRAII(n)
#define TIMECOST_VERBOSE_RAII(n) TimeCost::SummaryRAII(n, true)

namespace TimeCost
{
    class Timer
    {
    public:
        Timer(){ resetStart(); }
        void resetStart() { m_start = wallClock(); }
        double durationFromStart() { return wallClock() - m_start; }

     private:
        double wallClock()
        {
            struct timeval time;
            if (gettimeofday(&time, NULL))
            {
                throw "Failed to get wall clock!!!";
            }
            return (double)time.tv_sec + (double)time.tv_usec * .000001;
        }

        double m_start;
    };

    struct Data
    {
        uint32_t count;
        Timer timer;
        double timecost;
    
        Data() : count(0), timer(Timer()), timecost(0) {}
    };
    
    class Summary
    {
    public:
        static Summary * getInstance();
        void start(std::string name);
        void end(std::string name, bool verbose=false);
        void report();
        ~Summary() { report(); delete m_instance; m_instance = nullptr; }
    
    private:
        Summary() : m_threadId(pthread_self()) {}
        Summary(const Summary& another) {}
        
        bool started();
        pthread_t m_threadId;
        std::map<std::string, Data> m_data;
        static Summary* m_instance;
    }; // end of Summary
    
    class SummaryRAII
    {
    public:
        SummaryRAII(std::string name, bool verbose = false) : m_verbose(verbose) { Summary::getInstance()->start(name); }
        ~SummaryRAII() { Summary::getInstance()->end(name, m_verbose); }
    
    private:
        bool m_verbose;
    }; // end of SummaryRAII

} // end of TimeCost

#endif // __TIMER_H__