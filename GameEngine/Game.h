#pragma once
#ifdef GAMEENGINE_EXPORTS
#define GAME_API __declspec(dllexport) 
#else
#define GAME_API __declspec(dllimport)
#endif
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "../Graphics/Sprite.h"
#include "../Graphics/Graphics.h"

class Game
{
public:
	GAME_API Game(Graphics *graphics);
	GAME_API ~Game();
	GAME_API void Update(float delta);
	GAME_API void Render(Graphics *graphics);
	GAME_API void OnKeyPress(int buttonID, bool isPressed);
	GAME_API void OnKeyRelease(int buttonID);
private:
	Graphics *graphics;
	template <typename T>
	void WriteBinaryValue(std::ofstream *output, T value);
	template <typename T>
	void ReadBinaryValue(uint8_t **buffer, T *value, uint32_t *offset);
	void SaveLayout(Graphics *graphics);
	void LoadLayout(const char *filePath);
	bool LoadFile(const char *fileName, bool binary, uint8_t **buffer, uint32_t *size);
	
};

