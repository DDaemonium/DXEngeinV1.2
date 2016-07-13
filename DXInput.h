#pragma once
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include <dinput.h>
class DXInput
{
private:
	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;
	//DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;

	DIMOUSESTATE mouseCurrState;
	BYTE keyboardState[256];

public:
	DXInput();
	bool InitDirectInput(HINSTANCE &hInstance, HWND &hwnd);
	void UpdateState();
	BYTE *GetKeyboardState();
	DIMOUSESTATE *GetMouseState();
	~DXInput();
};

