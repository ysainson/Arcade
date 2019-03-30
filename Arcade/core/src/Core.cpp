/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Core
*/

#include <dlfcn.h>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <chrono>

#include "Core.hpp"

Core::~Core()
{
	if (this->_graphic._currentLib != nullptr)
		dlclose(this->_graphic._currentLib);
	if (this->_game._currentLib != nullptr)
		dlclose(this->_game._currentLib);
}

Core::Core(const std::string &libName)
{
	const auto libPath = realpath(libName.c_str(), nullptr);

	if (libPath == nullptr) {
		this->_error = libName + ": " + "File does not exist.";
		throw std::runtime_error(this->_error);
	}
	addGameLib("./games/lib_arcade_nibbler.so");
	addGraphicLib("./lib/lib_arcade_ncurses.so");
}

void Core::addGraphicLib(const std::string &libName)
{
	const auto libPath = realpath(libName.c_str(), nullptr);

	if (libPath == nullptr) {
		this->_error = libName + ":" + " Library unknown.";
		throw std::runtime_error(this->_error);
	}
	if (std::find(this->_graphic._listLib.begin(), this->_graphic._listLib.end(), libPath) == this->_graphic._listLib.end())
		this->_graphic._listLib.push_back(libPath);
}

void Core::addGameLib(const std::string &libName)
{
	const auto libPath = realpath(libName.c_str(), nullptr);

	if (libPath == nullptr) {
		this->_error = libName + ":" + " Library unknown.";
		throw std::runtime_error(this->_error);
	}
	if (std::find(this->_game._listLib.begin(), this->_game._listLib.end(), libPath) == this->_game._listLib.end())
		this->_game._listLib.push_back(libPath);
}

IGraphicLib *Core::getGraphicLibInstance() const
{
	using getInstance = IGraphicLib *();
	getInstance *f;

	if (this->_graphic._currentLib == nullptr)
		return nullptr;
	f = reinterpret_cast<getInstance *>(dlsym(this->_graphic._currentLib, "getGraphicalInstance"));
	if (f == nullptr)
		return nullptr;
	return f();
}

IGame *Core::getGameInstance() const
{
	using getInstance = IGame *();
	getInstance *f;

	if (this->_game._currentLib == nullptr)
		return nullptr;
	f = reinterpret_cast<getInstance*>(dlsym(this->_game._currentLib, "getGameInstance"));
	if (f == nullptr)
		return nullptr;
	return f();
}

void Core::nextGraphicLib()
{
	if (this->_graphic._listLib.size() == 1)
		return;
	if (this->_graphic._currentLib != nullptr)
		dlclose(this->_graphic._currentLib);
	auto it = std::find(this->_graphic._listLib.begin(), this->_graphic._listLib.end(), this->_graphic._currentPath);
	if (it + 1 == this->_graphic._listLib.end())
		loadGraphic(this->_graphic._listLib.front());
	else
		loadGraphic(*(it + 1));
	this->_graphic._currentObject = getGraphicLibInstance();
	if (this->_graphic._currentObject == nullptr)
		throw std::runtime_error("Can't load graphic lib");
}

void Core::nextGameLib()
{
	if (this->_game._listLib.size() == 1)
		return;
	if (this->_game._currentLib != nullptr)
		dlclose(this->_game._currentLib);
	auto it = std::find(this->_game._listLib.begin(), this->_game._listLib.end(), this->_game._currentPath);
	if (it + 1 == this->_game._listLib.end())
		loadGraphic(this->_game._listLib.front());
	else
		loadGraphic(*(it + 1));
	this->_game._currentObject = getGameInstance();
	if (this->_graphic._currentObject == nullptr)
		throw std::runtime_error("Can't load game lib");
}

void Core::loadGraphic(const std::string &libPath)
{
	this->_graphic._currentLib = dlopen(libPath.c_str(), RTLD_LAZY);
	if (this->_graphic._currentLib == nullptr)
		throw std::runtime_error(dlerror());
	this->_graphic._currentPath = libPath;
}

void Core::loadGame(const std::string &libPath)
{
	this->_game._currentLib = dlopen(libPath.c_str(), RTLD_LAZY);
	if (this->_game._currentLib == nullptr)
		throw std::runtime_error(dlerror());
	this->_game._currentPath = libPath;
}

IGraphicLib *Core::getGraphicObject() const
{
	return static_cast<IGraphicLib*>(this->_graphic._currentObject);
}

IGame *Core::getGameObject() const
{
	return static_cast<IGame*>(this->_game._currentObject);
}

void Core::mainLoop()
{
	loadGraphic(this->_graphic._listLib.front());
	loadGame(this->_game._listLib.front());
	this->_graphic._currentObject = getGraphicLibInstance();
	this->_game._currentObject = getGameInstance();
	if (this->_graphic._currentObject == nullptr)
		throw std::runtime_error("Graphic null");
	if (this->_game._currentObject == nullptr)
		throw std::runtime_error("Game null");
	
	getGameObject()->init(getGraphicObject());
	while (!getGraphicObject()->isCloseRequested() && !getGameObject()->isCloseRequested()) {
		auto start = std::chrono::system_clock::now();
		getGraphicObject()->pollEvents();
		getGameObject()->tick(getGraphicObject(), this->_deltaTime);
		getGameObject()->render(getGraphicObject());
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		this->_deltaTime = elapsed.count();
	}
}