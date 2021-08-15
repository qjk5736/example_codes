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
// This algorithm uses calls to libjpeg-turbo https://github.com/libjpeg-turbo/libjpeg-turbo
//

#include "image_reader.h"
#include <jpeglib.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <chrono>

#define RUN_TIMING

namespace IRDR {

  image_reader::image_reader(std::string path)
    : _path(path)
  {

  }

  void image_reader::initialize()
  {
  }

  void image_reader::run()
  {
    std::string tmpDir;
    std::string tmpFil;
    try 
    {
      for (const auto& folder : fs::directory_iterator(_path))
      {
        tmpDir = folder.path().u8string();
        std::cout << tmpDir << std::endl;
        for (const auto& file : fs::directory_iterator(tmpDir))
        {
          tmpFil = file.path().u8string();
          if (tmpFil.rfind(".jpg") != std::string::npos)
          {
            select_image(tmpFil);
          }
          else
          {
            std::cout << std::string::npos << std::endl;
          }
        }
      }
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  }

  void image_reader::update_map()
  {
    // To be added.
  }

  int image_reader::dir_exists(const fs::path& p, fs::file_status s)
  {
    std::cout << p;
    if (fs::status_known(s) ? fs::exists(s) : fs::exists(p)) {
      std::cout << " exists." << std::endl;
      return 1;
    }
    else
      std::cout << " does not exist." << std::endl;
    return 0;
  }

  void image_reader::load_jpeg_jpg_image(const char* filnam)
  {
    unsigned char r, g, b;
    int width, height, stride;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr err;
    JSAMPARRAY buffer;
    int version = 1;
#ifdef _WIN32
    FILE* fid;
    errno_t err1 = fopen_s(&fid, filnam, "rb");
#else
    FILE* fid = fopen(filnam, "rb");
#endif
    if (fid == NULL)
    {
      std::cerr << "Unable to open file " << filnam << std::endl;
    }
    else
    {
      cinfo.err = jpeg_std_error(&err);
      //jpeg_create_decompress(&cinfo, 62, (size_t)sizeof(struct jpeg_decompress_struct));
      jpeg_create_decompress(&cinfo);
      jpeg_stdio_src(&cinfo, fid);
      (void)jpeg_read_header(&cinfo, TRUE);
      (void)jpeg_start_decompress(&cinfo);
      width = cinfo.output_width;
      height = cinfo.output_height;
      stride = width * cinfo.output_components;
      buffer = (*cinfo.mem->alloc_sarray)
        ((j_common_ptr)&cinfo, JPOOL_IMAGE, stride, 1);
      unsigned char* ptrTemp = new unsigned char[(size_t)width * (size_t)height * (size_t)4];
      unsigned char* ptrUint8 = ptrTemp;
      while (cinfo.output_scanline < cinfo.image_height)
      {
        // This read is very memory intensive over time.
        (void)jpeg_read_scanlines(&cinfo, buffer, 1);
        for (int x = 0; x < width; x++)
        {
          r = buffer[0][cinfo.output_components * x];
          if (cinfo.output_components > 2)
          {
            g = buffer[0][cinfo.output_components * x + 1];
            b = buffer[0][cinfo.output_components * x + 2];
          }
          else
          {
            g = r;
            b = r;
          }
          *(ptrTemp++) = b;
          *(ptrTemp++) = g;
          *(ptrTemp++) = r;
          *(ptrTemp++) = 0; // alpha == 0 for jpg images.
        }
      }
      fclose(fid);
      (void)jpeg_finish_decompress(&cinfo);
      jpeg_destroy_decompress(&cinfo);
      int* tMap = reinterpret_cast<int*>(ptrUint8);
      for (int i = 0; i < (height * width); ++i)
      {
        _testImage.push_back(((unsigned short)tMap[i]) / 256);
      }
      if (ptrTemp) ptrTemp = 0x0;
      if (ptrUint8) ptrUint8 = 0x0;
    }
  }

  void image_reader::select_image(std::string filNam)
  {
#ifdef RUN_TIMING
    auto t1 = std::chrono::high_resolution_clock::now();
#endif
    load_jpeg_jpg_image(filNam.c_str());
#ifdef RUN_TIMING
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> mus_double = t2 - t1;
    std::cout << filNam << " is processed in " << mus_double.count() << " milliseconds." << std::endl;
#endif
    update_map();
    _testImage.clear();
  }

}
