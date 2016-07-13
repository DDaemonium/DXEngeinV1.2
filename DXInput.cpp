#include "DXInput.h"


DXInput::DXInput(){
}

bool DXInput::InitDirectInput(HINSTANCE &hInstance, HWND &hwnd) {
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&this->DirectInput, NULL);
	this->DirectInput->CreateDevice(GUID_SysKeyboard, &this->DIKeyboard, NULL);
	this->DirectInput->CreateDevice(GUID_SysMouse, &this->DIMouse, NULL);
	this->DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	this->DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	this->DIMouse->SetDataFormat(&c_dfDIMouse);
	this->DIMouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);//DISCL_EXCLUSIVE to hide cursor
	return true;
}

void DXInput::UpdateState() {

	this->DIKeyboard->Acquire();
	this->DIMouse->Acquire();//unaquire to show cursor if DISCL_EXCLUSIVE enabled
	this->DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &this->mouseCurrState);
	this->DIKeyboard->GetDeviceState(sizeof(this->keyboardState), (LPVOID)&this->keyboardState);
    
	return;
}

BYTE * DXInput::GetKeyboardState() {
	return this->keyboardState;
}

DIMOUSESTATE * DXInput::GetMouseState() {
	return &this->mouseCurrState;
}



DXInput::~DXInput(){
}
