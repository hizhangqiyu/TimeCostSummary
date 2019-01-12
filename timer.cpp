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
#include "timer.hpp"

namespace TimeCost
{
    TimeCostSummary* TimeCostSummary::m_instance = NULL;

    void Summary::report()
    {
        std::cout << "(" << m_threadId << ") Time cost summary:" << std::endl;
        for(std::map<std::string, Data>::iterator iter = m_data.begin();
                    iter != m_data.end(); ++iter)
        {
            if((iter->second).timecost != 0)
            {
                std::cout << "(" << m_threadId << ") " << iter->first << " : " << (iter->second).timecost << " seconds "
                    << (iter->second).count << " called." << std::endl;
            }
            else
            {
                std::cout << "(" << m_threadId << ") " << iter->first << " : " << 
            }
        }
        std::cout << "(" << m_threadId << ") -----------------" << std::endl;
    }

        void Summary::start(std::string name)
        {
            if(m_data.find(name) == m_data.end())
                m_data[name] = Data();
            else
                m_data[name].timer.resetStart();
            m_data[name].count ++;
        }

        void Summary::end(std::string name, bool verbose)
        {
            if(started())
            {
                double duration = m_data[name].timer.durationFromStart();

                if(verbose)
                {
                    std::cout << "(" << m_threadId << ") " << name << " cost " << duration << " seconds for one call." << std::endl;
                }

                m_data[name].timecost += duration; 

                //if (m_data[name].count % 2000 == 0)
                //    report();
            }
            else
            {
                std::string info = "Timer " + name + " has not started!!!";
                throw info;
            }
        }

    bool Summary::started(std::string name)
    {
        return !(m_data.find(name) == m_data.end());
    }

}