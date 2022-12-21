/*

#include "RollingLog.h"
#include <iostream>

template <class T>
RollingLog<T>::RollingLog(int maxLogSize) {
    this->maxLogSize = maxLogSize;
}

template <class T>
void RollingLog<T>::addEntry(T entry) {
    if(history.size() >= maxLogSize) {
        history.pop_back();
        history.push_front(entry);
    }
    else{
        history.push_front(entry);
    }
}

template <class T>
deque<T> RollingLog<T>::getHistory() {
    return history;
}

template <class T>
void RollingLog<T>::showHistory(deque<T> history){
    for(int i=0; i < history.size(); i++) {
        cout << history[i] << " ";
    }
    cout << endl;
}
*/