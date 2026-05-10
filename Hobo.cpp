#include <Hobo/Hobo.h>

#include <iostream>

bool Hobo::Debug::IsCrash = false;

void Hobo::Debug::Log(std::string value) {
	std::cout << "[LOG] " << value << std::endl;
}
void Hobo::Debug::Log(float value) {
	std::cout << "[LOG] " << value << std::endl;
}

void Hobo::Debug::LogError(std::string value) {
	IsCrash = true;
	std::cout << "\033[31m[ERROR] " << value << "\033[0m" << std::endl;
}
void Hobo::Debug::LogError(float value) {
	IsCrash = true;
	std::cout << "\033[31m[ERROR] " << value << "\033[0m" << std::endl;
}

#include <sstream>
#include <fstream>
#include <filesystem>

namespace fl = std::filesystem;

bool Hobo::FileManager::TestWriteTime(const char* pathFile, const char* pathFileTwo) {
	std::error_code ec1, ec2;

	auto one = std::filesystem::last_write_time(pathFile, ec1);
	auto two = std::filesystem::last_write_time(pathFileTwo, ec2);

	if (ec1 || ec2) {
		return false;
	}

	return one > two;
}

bool Hobo::FileManager::ExistFile(const char* pathFile) {
	return fl::exists(pathFile);
}

void Hobo::FileManager::CreateDirectory(const char* pathCreate) {
	fl::create_directories(pathCreate);
}

void Hobo::FileManager::TestDirectory(const char* pathFile) {
	if (!ExistFile(pathFile)) CreateDirectory(pathFile);
}

std::string Hobo::FileManager::ReadFile(std::string pathFile) {
	std::ifstream file(pathFile);
	
	if (file.is_open()) {
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		return buffer.str();
	}
	else {
		return "";
	}
}