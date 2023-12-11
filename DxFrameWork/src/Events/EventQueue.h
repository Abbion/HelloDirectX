#pragma once
#include "Event.h"
#include <deque>
#include <memory>

namespace FW
{
    class Window;

    class DXFW_API EventQueue
    {
    public:
        EventQueue();
        ~EventQueue();

        void PushEvent(const std::shared_ptr<Event>& newEvent);
        std::shared_ptr<Event> PopEvent();

        bool HasPenddingEvents() const;

        unsigned int GetSize() const;

        void MakeEventUnique(EventType eventType);
        void ClearEventQueue();

    private:
        std::deque<std::shared_ptr<Event>> m_events;

        friend Window;
    };
};
