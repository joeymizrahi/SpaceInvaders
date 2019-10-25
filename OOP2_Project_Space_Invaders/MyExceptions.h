#pragma once
#include <exception>

class FileException :public std::exception
{
public:
	FileException() = default;
	~FileException() = default;
	virtual char const* what() const override { return "Error opening File\n"; }
};