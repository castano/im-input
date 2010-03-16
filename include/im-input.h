
#pragma once
#ifndef IM_INPUT_H
#define IM_INPUT_H

#if IMI_USE_SDL
// Forward declarations for SDL.
union SDL_Event;
struct SDL_KeyboardEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
#endif





enum ButtonFlags
{
    ButtonFlags_Off = 0x0,
    ButtonFlags_On = 0x1,
    ButtonFlags_Begin = 0x2,
    ButtonFlags_End = 0x4,
    ButtonFlags_Shift = 0x8,
    ButtonFlags_Alt = 0x10,
    ButtonFlags_Ctrl = 0x20,
};

enum MouseButton
{
    MouseButton_Left = 0,
    MouseButton_Right = 1,
    MouseButton_Middle = 2,
};

class ButtonState {
    int flags;
    int time_down, time_up;
    int x_down, y_down, x_up, y_up;
};



/*
    // InputContext::update();
    // Process events
    // Poll input
*/

class InputContext {
public:
    
    InputContext();

#if IMI_USE_WIN32
    bool processEventWin32();
    void setCursorWin32(int x, int y);
#endif

#if IMI_USE_SDL
    bool processEventSDL(const SDL_Event *event);
    void processKeyEventSDL(const SDL_KeyboardEvent *event);
    void processMouseMotionEventSDL(const SDL_MouseMotionEvent *event);
    void processMouseButtonEventSDL(const SDL_MouseButtonEvent *event);
    void setCursorSDL(int x, int y);
#endif

#if IMI_USE_GLUT
    void processKeyEventGLUT(unsigned char key, int x, int y);
    void processSpecialEventGLUT(int key, int x, int y);
    void processKeyUpEventGLUT(unsigned char key, int x, int y);
    void processSpecialUpEventGLUT(int key, int x, int y);
    void processMouseFuncGLUT(int button, int state, int x, int y);
    void processMotionFuncGLUT(int x, int y);
    void processPassiveMotionFuncGLUT(int x, int y);
    void setCursorGLUT(int x, int y);
#endif

    // @@ Add support for DirectInput and XInput?

    // Generic event handlers:
    void processKeyEvent(int key);
    void processMouseMotionEvent(int x, int y);
    void processMouseButtonEvent(int button, int state);

    // Generic methods:
    void beginFrame();
    void endFrame();

    int cursorX() const { return m_currentCursorX;}
    int cursorY() const { return m_currentCursorY;}

    int cursorDeltaX() const { return m_cursorDeltaX - m_previousCursorX;}
    int cursorDeltaY() const { return m_cursorDeltaY - m_previousCursorY;}

    const ButtonState & buttonState(int button) const { assert(button >= 0 && button < 5); return m_buttonState[button]; }
    const ButtonState & keyState(int key) const { assert(button >= 0 && button < 256); return m_keyState[key]; }

    const char * charBuffer() const { return m_charBuffer; }

private:

    int m_currentCursorX;
    int m_currentCursorY;
    int m_previousCursorX;
    int m_previousCursorY;

    ButtonState m_buttonState[5];
    ButtonState m_keyState[256];

    unsigned char m_charBuffer[32];
    int m_charCount;

};


#endif // IM_INPUT_H
