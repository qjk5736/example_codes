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

#ifndef image_reader_H_
#define image_reader_H_

#include <vector>
#include <filesystem>
#include <string>
#include <string>
#include <memory>

namespace IRDR {

  namespace fs = std::filesystem;

  class image_reader
  {
  public:
    // default constructor (rule of zero)
    image_reader(std::string path);

    void run();
    void initialize();

  private:

    int dir_exists(const fs::path& p, fs::file_status s = fs::file_status{});
    void load_jpeg_jpg_image(const char* Name);
    void select_image(std::string dirNam);
    void update_map();
    std::vector<unsigned short> _testImage;
    std::string _path;
  };

}

#endif /* image_reader_H_ */
