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
cplusplus {{
    #include "SimpleAddress.h"
}}

class LAddress::L3Type extends void;


packet FormPkt 
{
    LAddress::L3Type destAddr = LAddress::L3BROADCAST; // destination address
    LAddress::L3Type srcAddr  = LAddress::L3BROADCAST; // source address
    double positionX = 0.00; // source x_position 
    double positionY = 0.00; // source y_position
    double speedX = 0.00; // source x_speed 
    double speedY = 0.00; // source y_speed
    double accelerationX = 0.00; // source x_acceleration 
    double accelerationY = 0.00; // source y_acceleration
    }
