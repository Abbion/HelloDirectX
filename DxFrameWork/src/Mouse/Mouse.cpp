#include "Mouse.h"

using namespace FW;
using namespace DirectX;

Mouse::Mouse() : m_mousePosition(0, 0), m_scroll(0)
{
    InitButtonMap();
}

bool Mouse::IsButtonPressed(Button button) const
{
    return m_buttonMap.at(button);
}

void Mouse::UpdateButtonMap(const ButtonState buttonState)
{
    if (buttonState.button == Button::NONE)
        m_buttonMap[buttonState.button] = buttonState.state;
}

void Mouse::InitButtonMap()
{
    m_buttonMap[Button::LEFT] = false;
    m_buttonMap[Button::RIGHT] = false;
    m_buttonMap[Button::MIDDLE] = false;
}

void Mouse::UpdatePosition(const XMINT2& position)
{
    static bool firstEnter = true;
    if (firstEnter)
    {
        m_mousePosition = position;
        firstEnter = false;
    }

    m_mousePositionDelta = XMINT2(position.x - m_mousePosition.x, position.y - m_mousePosition.y);
    m_mousePosition = position;
}