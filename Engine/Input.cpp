#include "pch.h"
#include "Input.h"


Input::Input()
{
}

Input::~Input()
{
}

void Input::Initialise(HWND window)
{
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_mouse = std::make_unique<DirectX::Mouse>();
	//³õÊ¼»¯Êó±ê
	//m_mouse->SetMode(DirectX::Mouse::MODE_RELATIVE);
	m_mouse->SetWindow(window);
	m_quitApp = false;

	m_GameInput.forward		= false;
	m_GameInput.back		= false;
	m_GameInput.right		= false;
	m_GameInput.left		= false;
	//m_GameInput.rotRight	= false;
	//m_GameInput.rotLeft		= false;
	m_GameInput.down		= false;

	m_GameInput.mouseLB = false;
	m_GameInput.mouseRB = false;
	m_GameInput.mouseMB = false;
	m_GameInput.mouseDX = 0.f;
	m_GameInput.mouseDY = 0.f;

	lastMouseX = m_GameInput.mouseDX;
	lastMouseY = m_GameInput.mouseDY;

	//m_mouse->SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void Input::Update()
{
	auto kb = m_keyboard->GetState();	//updates the basic keyboard state
	m_KeyboardTracker.Update(kb);		//updates the more feature filled state. Press / release etc. 
	auto mouse = m_mouse->GetState();   //updates the basic mouse state
	m_MouseTracker.Update(mouse);		//updates the more advanced mouse state. 

	if (kb.Escape)// check has escape been pressed.  if so, quit out. 
	{
		m_quitApp = true;
	}

	//A key
	if (kb.A)	m_GameInput.left = true;
	else		m_GameInput.left = false;
	
	//D key
	if (kb.D)	m_GameInput.right = true;
	else		m_GameInput.right = false;

	//W key
	if (kb.W)	m_GameInput.forward	 = true;
	else		m_GameInput.forward = false;

	//S key
	if (kb.S)	m_GameInput.back = true;
	else		m_GameInput.back = false;

	if(kb.C)	m_GameInput.down = true;
	else		m_GameInput.down = false;
	if (kb.Space)	m_GameInput.up = true;
	else			m_GameInput.up = false;

	//if (mouse.positionMode == DirectX::Mouse::MODE_RELATIVE)
	// 
	/*m_mouse->SetMode(mouse.leftButton ? DirectX::Mouse::MODE_RELATIVE : DirectX::Mouse::MODE_ABSOLUTE);
	DirectX::Mouse::State lastMouseState = m_MouseTracker.GetLastState();
	dx = mouse.x - lastMouseState.x;
	dy = mouse.y - lastMouseState.y;
	if (m_MouseTracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		m_mouse->SetMode(DirectX::Mouse::MODE_RELATIVE);
		m_GameInput.rotLeft = true;
	}
	else if (m_MouseTracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		m_mouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);
		m_GameInput.rotLeft = false;
	}*/
	//m_mouse->SetMode(mouse.leftButton ? DirectX::Mouse::MODE_RELATIVE : DirectX::Mouse::MODE_ABSOLUTE);
	//mouse.positionMode = DirectX::Mouse::MODE_ABSOLUTE;
	//m_mouse->SetMode(DirectX::Mouse::MODE_RELATIVE);
	m_GameInput.mouseLB = mouse.leftButton;
	m_GameInput.mouseRB = mouse.rightButton;
	m_GameInput.mouseMB = mouse.middleButton;
	m_GameInput.mouseDX = mouse.x - lastMouseX;
	m_GameInput.mouseDY = mouse.y - lastMouseY;

	lastMouseX = mouse.x;
	lastMouseY = mouse.y;
}

bool Input::Quit()
{
	return m_quitApp;
}

InputCommands Input::getGameInput()
{
	return m_GameInput;
}
