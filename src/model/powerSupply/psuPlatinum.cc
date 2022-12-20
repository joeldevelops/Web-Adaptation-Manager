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

#include <model/powerSupply/psuPlatinum.h>

psuPlatinum::psuPlatinum() {
    effIntervals = {
            {Interval(0.0, 0.1), 0.88},
            {Interval(0.1, 0.2), 0.90},
            {Interval(0.2, 0.3), 0.913},
            {Interval(0.3, 0.4), 0.926},
            {Interval(0.4, 0.5), 0.94},
            {Interval(0.5, 0.6), 0.934},
            {Interval(0.6, 0.7), 0.928},
            {Interval(0.7, 0.8), 0.922},
            {Interval(0.8, 0.9), 0.916},
            {Interval(0.9, 1.0), 0.91},
    };
}

psuPlatinum::~psuPlatinum() {
    // TODO Auto-generated destructor stub
}


