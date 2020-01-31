// ==================================================================================
// = NAS2D
// = Copyright © 2008 - 2019 New Age Software
// ==================================================================================
// = NAS2D is distributed under the terms of the zlib license. You are free to copy,
// = modify and distribute the software under the terms of the zlib license.
// =
// = Acknowledgement of your use of NAS2D is appriciated but is not required.
// ==================================================================================

#include "NAS2D/Filesystem.h"
#include "NAS2D/Exception.h"

#include <physfs.h>

#include <climits>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>

using namespace NAS2D;
using namespace NAS2D::Exception;


static bool closeFile(void* file)
{
	if (!file) { return false; }

	if (PHYSFS_close(static_cast<PHYSFS_File*>(file)) != 0) { return true; }

	throw filesystem_file_handle_still_open(PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
}



enum MountPosition
{
	MOUNT_PREPEND = 0,
	MOUNT_APPEND = 1,
};


NAS2D::Filesystem::Filesystem(const std::string& argv_0, const std::string& appName, const std::string& organizationName, const std::string& dataPath)
{
	if (PHYSFS_isInit()) { throw filesystem_already_initialized(); }

	if (PHYSFS_init(argv_0.c_str()) == 0)
	{
		throw filesystem_backend_init_failure(PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}

	if (PHYSFS_setSaneConfig(organizationName.c_str(), appName.c_str(), nullptr, false, false) == 0)
	{
		throw filesystem_backend_init_failure(std::string("Unable to set a sane configuration: ") + PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}

	mDataPath = dataPath;
	if (PHYSFS_mount(mDataPath.c_str(), "/", MountPosition::MOUNT_PREPEND) == 0)
	{
		throw filesystem_backend_init_failure(std::string("Couldn't find data path: ") + PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}
}


/**
 * Shuts down PhysFS and cleans up.
 */
Filesystem::~Filesystem()
{
	PHYSFS_deinit();
}


/**
 * Adds a directory or supported archive to the Search Path.
 *
 * \param path	File path to add.
 */
void Filesystem::mount(const std::string& path) const
{
	std::string searchPath(mDataPath + "/" + path);

	if (PHYSFS_mount(searchPath.c_str(), "/", MountPosition::MOUNT_APPEND) == 0)
	{
		throw std::runtime_error(std::string("Couldn't add '") + path + "' to search path: " + PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}
}


/**
 * Removes a directory or supported archive from the Search Path.
 *
 * \param path	File path to remove.
 */
void Filesystem::unmount(const std::string& path) const
{
	std::string searchPath(mDataPath + "/" + path);

	if (PHYSFS_unmount(searchPath.c_str()) == 0)
	{
		throw std::runtime_error(std::string("Couldn't remove '") + path + "' from search path : " + PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}
}


/**
 * Returns a list of directories in the Search Path.
 */
StringList Filesystem::searchPath() const
{
	StringList searchPath;

	auto searchPathList = PHYSFS_getSearchPath();
	for (char **i = searchPathList; *i != nullptr; ++i)
	{
		searchPath.push_back(*i);
	}
	PHYSFS_freeList(searchPathList);

	return searchPath;
}


/**
 * Returns a list of files within a given directory.
 *
 * \param	dir	Directory to search within the searchpath.
 * \param	filter		Optional extension filter. Only use the extension without a wildcard (*) character or period (e.g., 'png' vs '*.png' or '.png').
 *
 * \note	This function will also return the names of any directories in a specified search path
 */
StringList Filesystem::directoryList(const std::string& dir, const std::string& filter) const
{
	char **rc = PHYSFS_enumerateFiles(dir.c_str());

	StringList fileList;
	if (filter.empty())
	{
		for (char **i = rc; *i != nullptr; i++)
		{
			fileList.push_back(*i);
		}
	}
	else
	{
		size_t filterLen = filter.size();
		for (char **i = rc; *i != nullptr; i++)
		{
			std::string tmpStr = *i;
			if (tmpStr.rfind(filter, strlen(*i) - filterLen) != std::string::npos)
			{
				fileList.push_back(*i);
			}
		}
	}

	PHYSFS_freeList(rc);

	return fileList;
}


/**
 * Deletes a specified file.
 *
 * \param	filename	Path of the file to delete relative to the Filesystem root directory.
 */
void Filesystem::del(const std::string& filename) const
{
	if (PHYSFS_delete(filename.c_str()) == 0)
	{
		throw std::runtime_error(std::string("Unable to delete '") + filename + "':" + PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}
}


/**
 * Opens a file.
 *
 * \param filename	Path of the file to load.
 *
 * \return Returns a File.
 */
File Filesystem::open(const std::string& filename) const
{
	PHYSFS_file* myFile = PHYSFS_openRead(filename.c_str());
	if (!myFile)
	{
		closeFile(myFile);
		throw std::runtime_error(std::string("Unable to load '") + filename + "': " + PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}

	// Ensure that the file size is greater than zero and can fit in a 32-bit integer.
	PHYSFS_sint64 len = PHYSFS_fileLength(myFile);
	if (len < 0 || len > UINT_MAX)
	{
		closeFile(myFile);
		throw std::runtime_error(std::string("File '") + filename + "' is too large or size could not be determined");
	}

	// Create a char* buffer large enough to hold the entire file.
	PHYSFS_uint32 fileLength = static_cast<PHYSFS_uint32>(len);
	char* fileBuffer = new char[std::size_t{fileLength} + std::size_t{1}];

	// If we read less then the file length, return an empty File object, log a message and free any used memory.
	if (PHYSFS_readBytes(myFile, fileBuffer, fileLength) < fileLength)
	{
		delete[] fileBuffer;
		closeFile(myFile);
		throw std::runtime_error(std::string("Unable to load '") + filename + "': " + PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}

	File file(std::string(fileBuffer, fileLength), filename);
	closeFile(myFile);
	delete[] fileBuffer;

	return file;
}


/**
 * Creates a new directory within the primary search path.
 *
 * \param path	Path of the directory to create.
 */
void Filesystem::makeDirectory(const std::string& path) const
{
	if (PHYSFS_mkdir(path.c_str()) == 0)
	{
		throw std::runtime_error(std::string("Unable to create directory '" + path + "': ") + PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}
}


/**
 * Determines if a given path is a directory rather than a file.
 *
 * \param path	Path to check.
 */
bool Filesystem::isDirectory(const std::string& path) const
{
	PHYSFS_Stat stat;
	return (PHYSFS_stat(path.c_str(), &stat) != 0) && (stat.filetype == PHYSFS_FILETYPE_DIRECTORY);
}


/**
 * Checks for the existence of a file.
 *
 * \param	filename	File path to check.
 *
 * Returns Returns \c true if the specified file exists. Otherwise, returns \c false.
 */
bool Filesystem::exists(const std::string& filename) const
{
	return PHYSFS_exists(filename.c_str()) != 0;
}


/**
 * Writes a file to disk.
 *
 * \param	file		A reference to a \c const \c File object.
 * \param	overwrite	Flag indicating if a file should be overwritten if it already exists. Default is true.
 */
void Filesystem::write(const File& file, bool overwrite) const
{
	if (!overwrite && exists(file.filename()))
	{
		throw std::runtime_error(std::string("File exists: ") + file.filename());
	}

	PHYSFS_file* myFile = PHYSFS_openWrite(file.filename().c_str());
	if (!myFile)
	{
		throw std::runtime_error(std::string("Couldn't open '") + file.filename() + "' for writing: " + PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}

	if (PHYSFS_writeBytes(myFile, file.bytes().c_str(), static_cast<PHYSFS_uint32>(file.size())) < static_cast<PHYSFS_sint64>(file.size()))
	{
		closeFile(myFile);
		throw std::runtime_error(std::string("Error occured while writing to file '") + file.filename() + "': " + PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}

	closeFile(myFile);
}


/**
 * Gets the base data path.
 */
std::string Filesystem::dataPath() const
{
	return mDataPath;
}


/**
 * Convenience function to get the working directory of a file.
 *
 * \param filename	A file path.
 *
 * \note	File paths should not have any trailing '/' characters.
 */
std::string Filesystem::workingPath(const std::string& filename) const
{
	if (!filename.empty())
	{
		std::string tmpStr(filename);
		size_t pos = tmpStr.rfind("/");
		tmpStr = tmpStr.substr(0, pos + 1);
		return tmpStr;
	}
	else
	{
		return std::string();
	}
}


/**
 * Gets the extension of a given file path.
 *
 * \param	path	Path to check for an extension.
 *
 * \return	Returns a string containing the file extension, including the dot (".").
 *			An empty string will be returned if the file has no extension.
 */
std::string Filesystem::extension(const std::string& path)
{
	// This is a naive approach but works for most cases.
	size_t pos = path.find_last_of(".");

	if (pos != std::string::npos)
	{
		return path.substr(pos);
	}
	return std::string();
}
