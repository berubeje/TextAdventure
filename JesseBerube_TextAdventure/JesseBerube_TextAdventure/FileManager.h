#pragma once
#include <string>

class FileManager
{
private:
	std::string loadedFile;

public:
	inline static FileManager& Instance() {
		static FileManager instance;
		return instance;
	}


	bool LoadFile(bool loadSave);
	void SaveFile();

private:
	inline explicit FileManager()
	{
	}

	inline ~FileManager()
	{
	}

	inline explicit FileManager(FileManager const&)
	{
	}

	inline FileManager& operator=(FileManager const&)
	{
		return *this;
	}

};

