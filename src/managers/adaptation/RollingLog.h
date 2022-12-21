#ifndef ROLLINGLOG_H
#define ROLLINGLOG_H

#include <deque>
#include <vector>

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

        T predictNext() {
            std::deque<T> slopes;
            const std::vector<double> weights = {0.1, 0.15, 0.25, 0.5};
            double trend = 0.0;

            // calculate slopes over the past periods
            for (unsigned int i = 1; i < history.size(); i++) {
                slopes.push_front(history.at(i-1) - history.at(i));
            }

            // if the history is too short so far, just make a rudimentary prediction
            // only really occurs right when the system is starting so not a massive issue
            if (slopes.size() < weights.size()) return history.front();

            // calculate the weighted sum of the slopes
            for (unsigned int i = 0; i < weights.size() && i < slopes.size(); i++) {
                trend += slopes.at(i) * weights.at(i);
            }
            return history.front() + trend;
            return 0;
        }

    private:
        int maxLogSize;
        deque<T> history;
        
};




#endif // ROLLINGLONG_H