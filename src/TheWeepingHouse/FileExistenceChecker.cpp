

#include <TheWeepingHouse/FileExistenceChecker.hpp>

#include <filesystem>


namespace TheWeepingHouse
{


FileExistenceChecker::FileExistenceChecker(std::string filename)
   : filename(filename)
{
}


FileExistenceChecker::~FileExistenceChecker()
{
}


std::string FileExistenceChecker::get_filename() const
{
   return filename;
}


bool FileExistenceChecker::exists()
{
   return std::filesystem::exists(filename);
}


} // namespace TheWeepingHouse


