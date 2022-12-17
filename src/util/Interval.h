//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef UTIL_INTERVAL_H_
#define UTIL_INTERVAL_H_

class Interval {
public:
    Interval(double start, double end);
    virtual ~Interval();

    // true if start <= value <= end
    bool containsIncl(double value);

    // true if start < value < end
    bool containsExcl(double value);

    double getStart();
    double getEnd();

private:
    double start;
    double end;
};

#endif /* UTIL_INTERVAL_H_ */
