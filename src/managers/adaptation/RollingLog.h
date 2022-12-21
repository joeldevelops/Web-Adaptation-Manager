#ifndef ROLLINGLOG_H
#define ROLLINGLOG_H

#include <deque>

using namespace std;

class RollingLog<T>{
    public:
        RollingLog(int maxLogSize);
        deque getHistory();
        void showHistory(deque<T> history);
        void addEntry(T entry);

    private:
        int maxLogSize;
        deque<T> history;
        
}
