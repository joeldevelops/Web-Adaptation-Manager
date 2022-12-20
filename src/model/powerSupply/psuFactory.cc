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

#include <model/powerSupply/psuFactory.h>

psuFactory::psuFactory() {
    // TODO Auto-generated constructor stub

}

psuFactory::~psuFactory() {
    // TODO Auto-generated destructor stub
}

psuBase* psuFactory::get(std::string psuClass) {
    if (psuClass == "Gold") return new psuGold();
    if (psuClass == "Titanium") return new psuTitanium();
    if (psuClass == "Platinum") return new psuPlatinum();

    throw std::runtime_error("[psuBase.get()] Unknown psu class!");
}
