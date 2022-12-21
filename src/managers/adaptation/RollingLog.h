#ifndef ROLLINGLOG_H
#define ROLLINGLOG_H

#include <deque>

using namespace std;

template <class T> class RollingLog{
    public:
        RollingLog(int maxLogSize);
        deque<T> getHistory();
        void showHistory(deque<T> history);
        void addEntry(T entry);

    private:
        int maxLogSize;
        deque<T> history;
        
};

#endif // ROLLINGLONG_H