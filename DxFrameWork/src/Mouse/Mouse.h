#pragma once
#include "Core.h"
#include "GLFW/glfw3.h"

#include <DirectXMath.h>
#include <map>

namespace FW
{
    class Window;

    class DXFW_API Mouse
    {
    public:
        enum class Button : uint16_t
        {
            NONE = 404u,
            LEFT = GLFW_MOUSE_BUTTON_LEFT,
            RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
            MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
        };

        struct ButtonState
        {
            Button button = Button::NONE;
            bool state = false;
        };

    public:
        Mouse();

        bool IsButtonPressed(Button button) const;
        DirectX::XMINT2 GetMousePosition() const { return m_mousePosition; }
        DirectX::XMINT2 GetMousePositionDelta() const { return m_mousePositionDelta; }
        int GetScrollDelta() const { return m_scroll; }

    private:
        std::map<Button, bool> m_buttonMap;
        DirectX::XMINT2 m_mousePosition{ 0, 0 };
        DirectX::XMINT2 m_mousePositionDelta{ 0, 0 };
        int m_scroll;

    private:
        void UpdatePosition(const DirectX::XMINT2& position);
        void UpdateScroll(int scroll) { m_scroll = scroll; }
        void UpdateButtonMap(const ButtonState buttonState);
        void InitButtonMap();

        friend class Window;
    };
}