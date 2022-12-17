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

#include <model/powerSupply/psuTitanium.h>


psuTitanium::psuTitanium(double maxPower) {
    effIntervals = {
            {Interval(0.0, 0.1), 0.9},
            {Interval(0.1, 0.2), 0.94},
            {Interval(0.2, 0.3), 0.9466},
            {Interval(0.3, 0.4), 0.9532},
            {Interval(0.4, 0.5), 0.96},
            {Interval(0.5, 0.6), 0.95},
            {Interval(0.6, 0.7), 0.94},
            {Interval(0.7, 0.8), 0.93},
            {Interval(0.8, 0.9), 0.92},
            {Interval(0.9, 1.0), 0.91},
    };

    this->maxPower = maxPower;
}

psuTitanium::~psuTitanium() {
    // TODO Auto-generated destructor stub
}

