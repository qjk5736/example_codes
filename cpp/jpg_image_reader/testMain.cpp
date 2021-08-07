//
// Copyright 2021 DMJ Software Innovations LLC
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
// This algorithm was uses calls to libjpeg-turbo https://github.com/libjpeg-turbo/libjpeg-turbo
//

#include "image_reader.h"
#include <string>
// #include <map>

int main(int, const char* const [])
{
  // Compiled and built using C++17 switches.
  std::string hiLevelDir = "E:/Dev/flower_photos/flower_photos"; // Local jpg directories.
  IRDR::image_reader* imgRdr = new IRDR::image_reader(hiLevelDir);
  // auto image_store = std::make_unique<std::map<std::string, std::vector<unsigned short>>>();
  imgRdr->run();
  delete imgRdr;
  return 0;
}