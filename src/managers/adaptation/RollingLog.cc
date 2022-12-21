#include "RollingLog.h"
#include <iostream>


RollingLog::RollingLog(int maxLogSize) {
    this->maxLogSize = maxLogSize;
}

RollingLog::history; 

RollingLog::addEntry(T entry) {
    if(history.size() >= maxLogSize) {
        history.pop_back();
        history.push_front(entry);
    }
    else{
        history.push_front(entry);
    }
}

RollingLog::getHistory() {
    return history;
}

RollingLog::showHistory(deque<T> history){
    for(int i=0; i < history.size(); i++) {
        cout << history[i] << " ";
    }
    cout << endl;
}