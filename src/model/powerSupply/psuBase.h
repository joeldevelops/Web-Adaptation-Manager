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

#ifndef MODEL_POWERSUPPLY_PSUBASE_H_
#define MODEL_POWERSUPPLY_PSUBASE_H_

#include <string>
#include <map>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <util/Interval.h>

class psuBase {

public:
    psuBase();
    psuBase(double maxPower, std::vector<std::pair<Interval, double>> effIntervals);
    virtual ~psuBase();
    psuBase get(std::string efficiencyClass);
    double getWallPower(double internalPowerDraw);

protected:
    std::vector<std::pair<Interval, double>> effIntervals;
    double maxPower;    // maximum power for the PSU
};

#endif /* MODEL_POWERSUPPLY_PSUBASE_H_ */
