#pragma once


#include <string>


namespace TheWeepingHouse
{
   class FileExistenceChecker
   {
   private:
      std::string filename;

   public:
      FileExistenceChecker(std::string filename="");
      ~FileExistenceChecker();

      std::string get_filename();
      bool exists();
   };
}



