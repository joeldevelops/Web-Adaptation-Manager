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

#include <model/powerSupply/psuBase.h>


psuBase::psuBase() {
    effIntervals = {};
}

psuBase::psuBase(std::vector<std::pair<Interval, double>> effIntervals = {}) {
    this->effIntervals = effIntervals;
}

psuBase::~psuBase() { }

double psuBase::getWallPower(double maxPower, double powerDraw) {
    double efficiency = 0;
    double utilization = powerDraw / maxPower;

    // Find the interval that contains the current usage
    for (auto const& i : effIntervals) {
        Interval interval = i.first;
        if (interval.containsIncl(utilization))
            efficiency = i.second;
    }

    if (efficiency == 0) {
        throw std::runtime_error("Internal power draw outside of known intervals.");
    }

    double wallPower = powerDraw / efficiency;
    return wallPower;
}


