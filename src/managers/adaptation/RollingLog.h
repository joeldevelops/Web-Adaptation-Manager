#ifndef ROLLINGLOG_H
#define ROLLINGLOG_H

#include <deque>

using namespace std;

template <class T> class RollingLog{
    public:
        RollingLog(int maxLogSize) {
            this->maxLogSize = maxLogSize;
        }

        deque<T> getHistory() {
            return history;
        }

        void showHistory(deque<T> history) {
            for(int i=0; i < history.size(); i++) {
                std::cout << history[i] << " ";
            }
            std::cout << std::endl;            
        }

        void addEntry(T entry) {
            if(history.size() >= maxLogSize) {
                history.pop_back();
                history.push_front(entry);
            }
            else{
                history.push_front(entry);
            }
        }

    private:
        int maxLogSize;
        deque<T> history;
        
};




#endif // ROLLINGLONG_H