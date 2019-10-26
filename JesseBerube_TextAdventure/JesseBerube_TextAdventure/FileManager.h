#pragma once

class FileManager
{
private:


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

