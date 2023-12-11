#include "Window.h"
#include "Graphics/Graphics.h"
#include "Keyboard/Keyboard.h"
#include "Mouse/Mouse.h"
#include <iostream>

using namespace FW;

Window::Window(unsigned width, unsigned height, const std::string& name) :
	m_windowDimensions{ width, height },
	m_windowName{ name },
    m_eventQueue{ std::make_shared<EventQueue>() }
{
	if (m_globalInit == false)
	{
		glfwSetErrorCallback([](int error, const char* description) {
			std::cout << "GLFW error id:" << error << " - " << description << std::endl;
		});

		if (!glfwInit())
			exit(EXIT_FAILURE);

		m_globalInit = true;
	}

	m_systemWindow = glfwCreateWindow(m_windowDimensions.x, m_windowDimensions.y, m_windowName.c_str(), NULL, NULL);

	if (!m_systemWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_systemWindow);
	glfwSwapInterval(1);

	m_graphics = std::make_unique<Graphics>(*this);

	InitCallBacks();

    m_windowPointerDataStruct.eventQueue = m_eventQueue;
    glfwSetWindowUserPointer(m_systemWindow, reinterpret_cast<void*>(&m_windowPointerDataStruct));
}

const bool Window::IsOpen() const
{
    return glfwWindowShouldClose(m_systemWindow) == false;
}

void Window::HandleInternalEvents()
{
    m_eventQueue->MakeEventUnique(EventType::WindowResize);

    Keyboard::KeyState keyState{};
    Mouse::ButtonState buttonState{};
    int scroll = 0;

    for (const auto& currentEvent : m_eventQueue->m_events)
    {
        switch (currentEvent->GetType())
        {
        case EventType::KeyDown:
            keyState.key = static_cast<KeyDownEvent*>(currentEvent.get())->GetVal();
            keyState.state = true;
            break;

        case EventType::KeyUp:
            keyState.key = static_cast<KeyUpEvent*>(currentEvent.get())->GetVal();
            keyState.state = false;
            break;

        case EventType::MouseDown:
            buttonState.button = static_cast<MouseDownEvent*>(currentEvent.get())->GetVal();
            buttonState.state = true;
            break;

        case EventType::MouseUp:
            buttonState.button = static_cast<MouseDownEvent*>(currentEvent.get())->GetVal();
            buttonState.state = false;
            break;

        case EventType::MouseMove:
            m_mouse.UpdatePosition(static_cast<MouseMoveEvent*>(currentEvent.get())->GetVal());
            break;

        case EventType::MouseScroll:
            scroll = static_cast<MouseScrollEvent*>(currentEvent.get())->GetVal();
            break;

        default:
            break;
        }
    }

    m_keyboard.UpdateKeyMap(keyState);
    m_mouse.UpdateButtonMap(buttonState);
    m_mouse.UpdateScroll(scroll);
}

void Window::PoolEvents()
{
	glfwPollEvents();
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_systemWindow, GLFW_TRUE);
}

void Window::Terminate()
{
	glfwTerminate();
}

void Window::InitCallBacks()
{
    glfwSetFramebufferSizeCallback(m_systemWindow, [](GLFWwindow* window, int width, int height) {
        auto eventQueue = reinterpret_cast<WindowPointerDataStruct*>(glfwGetWindowUserPointer(window))->eventQueue;
        eventQueue->PushEvent(std::make_shared<WindowResizeEvent>(EventType::WindowResize, DirectX::XMUINT2(width, height)));
    });

    glfwSetKeyCallback(m_systemWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto eventQueue = reinterpret_cast<WindowPointerDataStruct*>(glfwGetWindowUserPointer(window))->eventQueue;

        if (action == GLFW_PRESS)
            eventQueue->PushEvent(std::make_shared<KeyDownEvent>(EventType::KeyDown, static_cast<Keyboard::Key>(key)));
        else if (action == GLFW_RELEASE)
            eventQueue->PushEvent(std::make_shared<KeyUpEvent>(EventType::KeyUp, static_cast<Keyboard::Key>(key)));
    });

    glfwSetMouseButtonCallback(m_systemWindow, [](GLFWwindow* window, int button, int action, int mods) {
        auto eventQueue = reinterpret_cast<WindowPointerDataStruct*>(glfwGetWindowUserPointer(window))->eventQueue;

        if (action == GLFW_PRESS)
            eventQueue->PushEvent(std::make_shared<MouseDownEvent>(EventType::MouseDown, static_cast<Mouse::Button>(button)));
        else if (action == GLFW_RELEASE)
            eventQueue->PushEvent(std::make_shared<MouseUpEvent>(EventType::MouseUp, static_cast<Mouse::Button>(button)));
    });

    glfwSetCursorPosCallback(m_systemWindow, [](GLFWwindow* window, double xpos, double ypos) {
        auto eventQueue = reinterpret_cast<WindowPointerDataStruct*>(glfwGetWindowUserPointer(window))->eventQueue;
        eventQueue->PushEvent(std::make_shared<MouseMoveEvent>(EventType::MouseMove, DirectX::XMINT2(static_cast<int>(xpos), static_cast<int>(ypos))));
    });

    glfwSetScrollCallback(m_systemWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
        auto eventQueue = reinterpret_cast<WindowPointerDataStruct*>(glfwGetWindowUserPointer(window))->eventQueue;
        eventQueue->PushEvent(std::make_shared<MouseScrollEvent>(EventType::MouseScroll, static_cast<int>(yoffset)));
    });
}