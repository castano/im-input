
#include "im-input.h"

#if IMI_USE_WIN32
// @@ Add lean and mean stuff.
#include <windows.h>
#endif

#if IMI_USE_SDL
#include <SDL/SDL.h>
#endif

#if IMI_USE_GLUT
// @@ Use proper header in OSX.
#include <GL/glut.h>
#endif


InputContext::InputContext() {
}


#if IMI_USE_WIN32

bool InputContext::processEventWin32() {
    // @@ TODO
}

void InputContext::setCursorWin32(int x, int y) {
    m_currentCursorX = x;
    m_currentCursorY = y;
    m_previousCursorX = x;
    m_previousCursorY = y;
    // @@ TODO
}

#endif // IMI_USE_WIN32

#if IMI_USE_SDL

bool InputContext::processEventSDL(const SDL_Event * event) {
    switch (event->type)
    {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            processKeyEventSDL(&event->key);
            break;
        case SDL_MOUSEMOTION:
            processMouseMotionEventSDL(&event->motion);
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            processMouseButtonEventSDL(&event->button);
            break;
        default:
            return false;
    };
    
    return true;
}

static int translateKeySDL(SDLKey key) {
    // @@ TODO
}
static int translateButtonSDL(Uint8 button) {
    switch (button) {
        case SDL_BUTTON_LEFT: return MouseButton_Left;
        case SDL_BUTTON_MIDDLE: return MouseButton_Middle;
        case SDL_BUTTON_RIGHT: return MouseButton_Right;
    };
}

void InputContext::processKeyEventSDL(const SDL_KeyboardEvent *event) {
    processMouseMotionEvent(event->x, event->y);
    processKeyEvent(translateKeySDL(event->key.sym), event->type == SDL_KEYDOWN);
}
void InputContext::processMouseMotionEventSDL(const SDL_MouseMotionEvent *event) {
    processMouseMotionEvent(event->x, event->y);
}
void InputContext::processMouseButtonEventSDL(const SDL_MouseButtonEvent *event) {
    processMouseMotionEvent(event->x, event->y);
    processMouseButtonEvent(translateButtonSDL(event->button), event->type == SDL_MOUSEBUTTONDOWN);
}

void InputContext::setCursorSDL(int x, int y) {
    m_currentCursorX = x; // Updated by SDL_WarpMouse too.
    m_currentCursorY = y;
    m_previousCursorX = x;
    m_previousCursorY = y;
    SDL_WarpMouse(x, y);
}

#endif // IMI_USE_SDL


#if IMI_USE_GLUT

void InputContext::processKeyEventGLUT(unsigned char key, int x, int y) {
    processMouseMotionEvent(x, y);
    processKeyEvent(translateKeyGLUT(key), true);
}

void InputContext::processSpecialEventGLUT(int key, int x, int y) {
    processMouseMotionEvent(x, y);
    processKeyEvent(translateSpecialKeyGLUT(key), true);
}
void InputContext::processKeyUpEventGLUT(unsigned char key, int x, int y) {
    processMouseMotionEvent(x, y);
    processKeyEvent(translateKeyGLUT(key), false);
}
void InputContext::processSpecialUpEventGLUT(int key, int x, int y) {
    processMouseMotionEvent(x, y);
    processKeyEvent(translateSpecialKeyGLUT(key), false);
}
void InputContext::processMouseFuncGLUT(int button, int state, int x, int y) {
    processMouseMotionEvent(x, y);
    processMouseButtonEvent(button, state == GLUT_DOWN);
}
void InputContext::processMotionFuncGLUT(int x, int y) {
    processMouseMotionEvent(x, y);
}
void InputContext::processPassiveMotionFuncGLUT(int x, int y) {
    processMouseMotionEvent(x, y);
}

void InputContext::setCursorGLUT(int x, int y) {
    m_currentCursorX = x;
    m_currentCursorY = y;
    m_previousCursorX = x;
    m_previousCursorY = y;
    // @@ TODO
}

#endif // IMI_USE_GLUT


void InputContext::processKeyEvent(int key, bool down) {
    // @@ TODO
    //ButtonState m_keyState[256];
    //unsigned char m_charBuffer[32];
    //int m_charCount;
}
void InputContext::processMouseMotionEvent(int x, int y) {
    m_currentCursorX = x;
    m_currentCursorY = y;
}
void InputContext::processMouseButtonEvent(int button, bool down) {
    // @@ TODO
    //ButtonState m_buttonState[5];
}



void InputContext::beginFrame() {
    m_previousCursorX = m_currentCursorX;
    m_previousCursorY = m_currentCursorY;
    m_charBuffer[0] = '\0';
    m_charCount = 0;
    // @@ TODO
}

void InputContext::endFrame() {
    // @@ TODO
};

