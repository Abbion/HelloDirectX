#pragma once
#include <string>

#include <DirectXMath.h>

#include "Keyboard/Keyboard.h"
#include "Mouse/Mouse.h"

namespace FW
{
    enum class DXFW_API EventType
    {
        WindowResize,

        KeyDown,
        KeyUp,

        MouseDown,
        MouseUp,
        MouseScroll,
        MouseMove
    };

    //==================================================================
    class DXFW_API Event
    {
    public:
        Event(EventType eventType) : m_type(eventType) {}
        virtual ~Event() { /*ULOGD("event " << (int)m_type << " terminated");*/ }

        void MarkHandeled(bool handeled) { m_handeled = handeled; }

        EventType GetType() const { return m_type; }
        bool IsHandeled() const { return m_handeled; }

    private:
        EventType m_type;
        bool m_handeled{ false };
    };

    //==================================================================
    template<typename T>
    class ValueEvent : public Event
    {
    public:
        ValueEvent(EventType eventType, T val) : Event(eventType), m_val(val) {}

        T GetVal() const { return m_val; }

    private:
        T m_val;
    };

    //==================================================================
    typedef ValueEvent<DirectX::XMUINT2> WindowResizeEvent;

    typedef ValueEvent<Keyboard::Key> KeyDownEvent;
    typedef ValueEvent<Keyboard::Key> KeyUpEvent;

    typedef ValueEvent<Mouse::Button> MouseDownEvent;
    typedef ValueEvent<Mouse::Button> MouseUpEvent;
    typedef ValueEvent<int> MouseScrollEvent;
    typedef ValueEvent<DirectX::XMINT2> MouseMoveEvent;
};