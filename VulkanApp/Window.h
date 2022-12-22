#pragma once

#include "Disposable.h"
#include <stdexcept>
#include <string>
#include <SDL/SDL.h>

class Window : public Disposable {
private:
	SDL_Window* window = nullptr;

	int width = 0;
	int height = 0;
	std::string title = "";

	bool closed = false;
	bool minimized = false;
public:
	Window(int width, int height, std::string title) {
		this->width = width;
		this->height = height;
		this->title = title;

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			throw std::runtime_error("failed to initialize sdl: " + *SDL_GetError());
		}

		this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_VULKAN);
		if (this->window == NULL) {
			throw std::runtime_error("failed to create window: " + *SDL_GetError());
		}
	}

	void processEvents() {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_WINDOWEVENT) {
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_SHOWN:
					//minimized = false;
					break;
				case SDL_WINDOWEVENT_HIDDEN:
					//minimized = true;
					break;
				case SDL_WINDOWEVENT_MINIMIZED:
					minimized = true;
					break;
				case SDL_WINDOWEVENT_RESTORED:
					minimized = false;
					break;
				case SDL_WINDOWEVENT_CLOSE:
					closed = true;
					break;
				default:
					break;
				}
			}
		}
	}

	bool IsClosed() { return closed; }
	bool IsMinimized() { return minimized; }

	SDL_Window* GetSDLWindow() {
		return window;
	}

	void Dispose() override {
		SDL_DestroyWindow(window);
		SDL_Quit();
		Dispose();
	}
};