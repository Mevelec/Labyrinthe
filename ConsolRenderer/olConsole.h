/*
OneLoneCoder.com - Command Line Game Engine
"Who needs a frame buffer?" - @Javidx9

The Original & Best :P

One Lone Coder License
~~~~~~~~~~~~~~~~~~~~~~
- This software is Copyright (C) 2018 Javidx9
- This is free software
- This software comes with absolutely no warranty
- The copyright holder is not liable or responsible for anything
  this software does or does not
- You use this software at your own risk
- You can distribute this software
- You can modify this software
- Redistribution of this software or a derivative of this software
  must attribute the Copyright holder named above, in a manner
  visible to the end user

License
~~~~~~~
One Lone Coder Console Game Engine  Copyright (C) 2018  Javidx9
This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it
under certain conditions; See license for details.

Original works located at:
	https://www.github.com/onelonecoder
	https://www.onelonecoder.com
	https://www.youtube.com/javidx9

GNU GPLv3
	https://github.com/OneLoneCoder/videos/blob/master/LICENSE

From Javidx9 :)
~~~~~~~~~~~~~~~
Hello! Ultimately I don't care what you use this for. It's intended to be
educational, and perhaps to the oddly minded - a little bit of fun.
Please hack this, change it and use it in any way you see fit. You acknowledge
that I am not responsible for anything bad that happens as a result of
your actions. However this code is protected by GNU GPLv3, see the license in the
github repo. This means you must attribute me if you use it. You can view this
license here: https://github.com/OneLoneCoder/videos/blob/master/LICENSE

Cheers!

Background
~~~~~~~~~~
If you've seen any of my videos - I like to do things using the windows console. It's quick
and easy, and allows you to focus on just the code that matters - ideal when you're
experimenting. Thing is, I have to keep doing the same initialisation and display code
each time, so this class wraps that up.

Author
~~~~~~
Twitter: @javidx9	http://twitter.com/javidx9
Blog:				http://www.onelonecoder.com
YouTube:			http://www.youtube.com/javidx9

Videos:
~~~~~~
Original:				https://youtu.be/cWc0hgYwZyc
Added mouse support:	https://youtu.be/tdqc9hZhHxM
Beginners Guide:		https://youtu.be/u5BhrA8ED0o

Shout Outs!
~~~~~~~~~~~
Thanks to cool people who helped with testing, bug-finding and fixing!
wowLinh, JavaJack59, idkwid, kingtatgi, Return Null, CPP Guy, MaGetzUb

Last Updated: 02/07/2018

Usage:
~~~~~~
This class is abstract, so you must inherit from it. Override the OnUserCreate() function
with all the stuff you need for your application (for thready reasons it's best to do
this in this function and not your class constructor). Override the OnUserUpdate(float fElapsedTime)
function with the good stuff, it gives you the elapsed time since the last call so you
can modify your stuff dynamically. Both functions should return true, unless you need
the application to close.

	int main()
	{
		// Use olcConsoleGameEngine derived app
		OneLoneCoder_Example game;

		// Create a console with resolution 160x100 characters
		// Each character occupies 8x8 pixels
		game.ConstructConsole(160, 100, 8, 8);

		// Start the engine!
		game.Start();

		return 0;
	}

Input is also handled for you - interrogate the m_keys[] array with the virtual
keycode you want to know about. bPressed is set for the frame the key is pressed down
in, bHeld is set if the key is held down, bReleased is set for the frame the key
is released in. The same applies to mouse! m_mousePosX and Y can be used to get
the current cursor position, and m_mouse[1..5] returns the mouse buttons.

The draw routines treat characters like pixels. By default they are set to white solid
blocks - but you can draw any unicode character, using any of the colours listed below.

There may be bugs!

See my other videos for examples!
http://www.youtube.com/javidx9

Lots of programs to try:
http://www.github.com/OneLoneCoder/videos

Chat on the Discord server:
https://discord.gg/WhwHUMV

Be bored by Twitch:
http://www.twitch.tv/javidx9

*/

/**
 cde récupéré afin de gérer :
	la gameLoop
	les inputs events

 */
#pragma once
#pragma comment(lib, "winmm.lib")

#ifndef UNICODE
#error Please enable UNICODE for your compiler! VS: Project Properties -> General -> \
Character Set -> Use Unicode. Thanks! - Javidx9
#endif

#ifdef linux
#error Windows Only 
#endif

#include <windows.h>
#include <wingdi.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>

enum COLOUR
{
	RED   = 0x000000FF,
	GREEN = 0x0000FF00,
	BLUE  = 0x00FF0000,
	BLACK = 0x00000000,
	GREY  = 0x00909090,
	WHITE = 0x00FFFFFF,
};

/**
 * consolRendering.
 * thank to @Javidx9 for the game loop and key input manager
 */
class olcConsoleGameEngine
{
	/**
	 * Update the data with the current window size.
	 */
	void updateConsoleSize() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		RECT    rcCli;
		GetClientRect(WindowFromDC(hdcConsole), &rcCli);
		// then you might have: 
		m_nScreenWidth = rcCli.right - rcCli.left;
		m_nScreenHeight = rcCli.bottom - rcCli.top;
	}
public:
	olcConsoleGameEngine()
	{
		m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

		std::memset(m_keyNewState, 0, 256 * sizeof(short));
		std::memset(m_keyOldState, 0, 256 * sizeof(short));
		std::memset(m_keys, 0, 256 * sizeof(sKeyState));
		m_mousePosX = 0;
		m_mousePosY = 0;

		m_sAppName = L"Default";

		myconsole = GetConsoleWindow();
	}
	/**
	 * beginpaint must be called before every paint.
	 * it create a buffer in which we draw
	 */
	void beginPaint() {
		hdcConsole = GetDC(myconsole);
		hdcMemoire = CreateCompatibleDC(hdcConsole);
		updateConsoleSize();

		bitmap = CreateCompatibleBitmap(hdcConsole, m_nScreenWidth*2, m_nScreenHeight*2);
		SelectObject(hdcMemoire, bitmap);
	}
	/**
	 * draw a rectangle from (x, y) to (mx, my) of given color.
	 * 
	 * \param x
	 * \param y
	 * \param xm
	 * \param ym
	 * \param color
	 */
	void drawRect(int x, int y, int xm, int ym, const COLORREF& color = WHITE)
	{
		RECT rect = { y, x, ym, xm };
		HBRUSH brush = CreateSolidBrush(color);
		FillRect(hdcMemoire, &rect, brush);
		DeleteObject(brush);
	}
	/**
	 * draw a circle in the rectangle from (x, y) to (mx, my) of given color.
	 *
	 * \param x
	 * \param y
	 * \param xm
	 * \param ym
	 * \param color
	 */
	void drawCircle(int x, int y, int xm, int ym, const COLORREF& color = WHITE)
	{
		RECT rect = { y, x, ym, xm };
		HBRUSH brush = CreateSolidBrush(color);
		Ellipse(hdcMemoire, x, y, xm, ym);
		DeleteObject(brush);
	}
	/**
	 * draw tex at position in given color.
	 * 
	 * \param pos
	 * \param str
	 * \param color
	 */
	void drawText(COORD pos, const LPCWSTR& str, const COLORREF& color = WHITE)
	{
		RECT rect = { pos.X, pos.Y, 1000, 1000 };
		SetTextColor(hdcMemoire, color);
		SetBkMode(hdcMemoire, TRANSPARENT);
		DrawText(hdcMemoire, str, -1, &rect, DT_LEFT);
	}
	/**
	 * draw text at given line and offset from left of given color.
	 * 
	 * \param line
	 * \param offset
	 * \param str
	 * \param color
	 */
	void drawText(size_t line, size_t offset, const LPCWSTR& str, const COLORREF& color = WHITE)
	{
		RECT rect = { offset, line*13, 1000, 1000 };
		SetTextColor(hdcMemoire, color);
		SetBkMode(hdcMemoire, TRANSPARENT);
		DrawText(hdcMemoire, str, -1, &rect, DT_LEFT);
	}
	/**
	 * endPaint must be called before every paint.
	 * it send the buffer to be rendered
	 */
	void endPaint() {
		BitBlt(hdcConsole, 0, 0, m_nScreenWidth*2, m_nScreenHeight*2, hdcMemoire, 0, 0, SRCCOPY);

		DeleteDC(hdcMemoire);
		ReleaseDC(NULL, hdcConsole);
		DeleteObject(bitmap);

	}

	~olcConsoleGameEngine()
	{
		SetConsoleActiveScreenBuffer(m_hOriginalConsole);
		DeleteDC(hdcMemoire);
		ReleaseDC(NULL, hdcConsole);
		delete[] m_bufScreen;
	}

public:
	/**
	 * start the game loop.
	 * 
	 */
	void Start()
	{
		// Start the thread
		m_bAtomActive = true;
		std::thread t = std::thread(&olcConsoleGameEngine::GameThread, this);

		// Wait for thread to be exited
		t.join();
	}
private:
	void GameThread()
	{
		// Create user resources as part of this thread
		if (!OnUserCreate())
			m_bAtomActive = false;

		auto tp1 = std::chrono::system_clock::now();
		auto tp2 = std::chrono::system_clock::now();

		while (m_bAtomActive)
		{
			// Run as fast as possible
			while (m_bAtomActive)
			{
				// Handle Timing
				tp2 = std::chrono::system_clock::now();
				std::chrono::duration<float> elapsedTime = tp2 - tp1;
				tp1 = tp2;
				float fElapsedTime = elapsedTime.count();

				// Handle Keyboard Input
				for (int i = 0; i < 256; i++)
				{
					m_keyNewState[i] = GetAsyncKeyState(i);

					m_keys[i].bPressed = false;
					m_keys[i].bReleased = false;

					if (m_keyNewState[i] != m_keyOldState[i])
					{
						if (m_keyNewState[i] & 0x8000)
						{
							m_keys[i].bPressed = !m_keys[i].bHeld;
							m_keys[i].bHeld = true;
						}
						else
						{
							m_keys[i].bReleased = true;
							m_keys[i].bHeld = false;
						}
					}

					m_keyOldState[i] = m_keyNewState[i];
				}

				// Handle Mouse Input - Check for window events
				INPUT_RECORD inBuf[32];
				DWORD events = 0;
				GetNumberOfConsoleInputEvents(m_hConsoleIn, &events);
				if (events > 0)
					ReadConsoleInput(m_hConsoleIn, inBuf, events, &events);

				// Handle events - we only care about mouse clicks and movement
				// for now
				for (DWORD i = 0; i < events; i++)
				{
					switch (inBuf[i].EventType)
					{
					case FOCUS_EVENT:
					{
						m_bConsoleInFocus = inBuf[i].Event.FocusEvent.bSetFocus;
					}
					break;

					case MOUSE_EVENT:
					{
						switch (inBuf[i].Event.MouseEvent.dwEventFlags)
						{
						case MOUSE_MOVED:
						{
							m_mousePosX = inBuf[i].Event.MouseEvent.dwMousePosition.X;
							m_mousePosY = inBuf[i].Event.MouseEvent.dwMousePosition.Y;
						}
						break;

						case 0:
						{
							for (int m = 0; m < 5; m++)
								m_mouseNewState[m] = (inBuf[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;

						}
						break;

						default:
							break;
						}
					}
					break;

					default:
						break;
						// We don't care just at the moment
					}
				}

				for (int m = 0; m < 5; m++)
				{
					m_mouse[m].bPressed = false;
					m_mouse[m].bReleased = false;

					if (m_mouseNewState[m] != m_mouseOldState[m])
					{
						if (m_mouseNewState[m])
						{
							m_mouse[m].bPressed = true;
							m_mouse[m].bHeld = true;
						}
						else
						{
							m_mouse[m].bReleased = true;
							m_mouse[m].bHeld = false;
						}
					}

					m_mouseOldState[m] = m_mouseNewState[m];
				}


				// Handle Frame Update
				if (!OnUserUpdate(fElapsedTime))
					m_bAtomActive = false;

				// Update Title & Present Screen Buffer
				wchar_t s[256];
				swprintf_s(s, 256, L"OneLoneCoder.com - Console Game Engine - %s - FPS: %3.2f", m_sAppName.c_str(), 1.0f / fElapsedTime);
				SetConsoleTitle(s);
			}

			// Allow the user to free resources if they have overrided the destroy function
			if (OnUserDestroy())
			{
				// User has permitted destroy, so exit and clean up
				delete[] m_bufScreen;
				SetConsoleActiveScreenBuffer(m_hOriginalConsole);
				m_cvGameFinished.notify_one();
			}
			else
			{
				// User denied destroy for some reason, so continue running
				m_bAtomActive = true;
			}
		}
	}

public:
	/**
	 * must implement .
	 * the user can add onCreate procedures
	 * \return 
	 */
	virtual bool OnUserCreate() = 0;
	/**
	 *  must implement.
	 * the user can add onUpdate procedures
	 * \param fElapsedTime is the time elapsed since last call
	 * \return 
	 */
	virtual bool OnUserUpdate(float fElapsedTime) = 0;

	/**
	 * must implement .
	 * the user can add onDelete procedures
	 * \return true if did finish
	 */
	virtual bool OnUserDestroy() { return true; }

protected:


	struct sKeyState
	{
		bool bPressed;
		bool bReleased;
		bool bHeld;
	} m_keys[256], m_mouse[5];

	int m_mousePosX;
	int m_mousePosY;

public:
	sKeyState GetKey(int nKeyID) { return m_keys[nKeyID]; }
	int GetMouseX() { return m_mousePosX; }
	int GetMouseY() { return m_mousePosY; }
	sKeyState GetMouse(int nMouseButtonID) { return m_mouse[nMouseButtonID]; }
	bool IsFocused() { return m_bConsoleInFocus; }


protected:
	int Error(const wchar_t* msg)
	{
		wchar_t buf[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
		SetConsoleActiveScreenBuffer(m_hOriginalConsole);
		wprintf(L"ERROR: %s\n\t%s\n", msg, buf);
		return 0;
	}

	static BOOL CloseHandler(DWORD evt)
	{
		// Note this gets called in a seperate OS thread, so it must
		// only exit when the game has finished cleaning up, or else
		// the process will be killed before OnUserDestroy() has finished
		if (evt == CTRL_CLOSE_EVENT)
		{
			m_bAtomActive = false;

			// Wait for thread to be exited
			std::unique_lock<std::mutex> ul(m_muxGame);
			m_cvGameFinished.wait(ul);
		}
		return true;
	}

protected:
	int m_nScreenWidth;
	int m_nScreenHeight;
	CHAR_INFO* m_bufScreen;
	std::wstring m_sAppName;
	HANDLE m_hOriginalConsole;
	CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;
	HANDLE m_hConsole;
	HANDLE m_hConsoleIn;
	SMALL_RECT m_rectWindow;
	short m_keyOldState[256] = { 0 };
	short m_keyNewState[256] = { 0 };
	bool m_mouseOldState[5] = { 0 };
	bool m_mouseNewState[5] = { 0 };
	bool m_bConsoleInFocus = true;
	bool m_bEnableSound = false;

	// These need to be static because of the OnDestroy call the OS may make. The OS
	// spawns a special thread just for that
	static std::atomic<bool> m_bAtomActive;
	static std::condition_variable m_cvGameFinished;
	static std::mutex m_muxGame;


	HWND myconsole;
	HDC hdcConsole;
	HDC hdcMemoire;
	HBITMAP  bitmap;
	PAINTSTRUCT ps;
};

// Define our static variables
std::atomic<bool> olcConsoleGameEngine::m_bAtomActive(false);
std::condition_variable olcConsoleGameEngine::m_cvGameFinished;
std::mutex olcConsoleGameEngine::m_muxGame;
