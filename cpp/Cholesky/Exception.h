//
// Copyright 2022 John I. Krassikoff
//
// This program is free software : you can redistribute itand /or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.
//
#ifndef Exception_H
#define Exception_H

#include <string>

class CholeskyException
{
public:
	CholeskyException(std::string str) : _msg(str) {}
	std::string getMessage() {
		return _msg;
	}
private:
	std::string _msg;
};

#endif /* Exception_H */
