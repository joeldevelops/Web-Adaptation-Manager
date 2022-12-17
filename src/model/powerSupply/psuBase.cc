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
    psuBase(0, {});
}

psuBase::psuBase(double maxPower, std::vector<std::pair<Interval, double>> effIntervals = {}) {
    this->maxPower = maxPower;
    this->effIntervals = effIntervals;
}

psuBase::~psuBase() { }

double psuBase::getWallPower(double internalPowerDraw) {
    double usage = internalPowerDraw / maxPower;
    double efficiency = 0;

    // Find the interval that contains the current usage
    for (auto const& i : effIntervals) {
        Interval interval = i.first;
        if (interval.containsIncl(usage))
            efficiency = i.second;
    }

    if (efficiency == 0) {
        throw std::runtime_error("Internal power draw outside of known intervals.");
    }

    double wallPower = internalPowerDraw / efficiency;
    return wallPower;
}


