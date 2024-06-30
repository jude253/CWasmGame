/*
TO DO:
  - Get rid of the need for  `-sLEGACY_GL_EMULATION` in compiler
    - Cut out starter code and replace it with simple SDL2 things
  - Move something around the screen with mouse or keypresses
  - Simplify code (input and otherwise)
  - Ensure assets can be loaded in webpage
  - Maybe break out code into different files
*/

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <emscripten.h>
#include <emscripten/key_codes.h>
#include <emscripten/html5.h>
#include <stdio.h>

SDL_Window *window;

// GL_ARB_shading_language_100, GL_ARB_shader_objects, GL_ARB_fragment_shader, GL_ARB_vertex_shader
PFNGLCREATEPROGRAMOBJECTARBPROC       glCreateProgramObject_      = NULL;
PFNGLDELETEOBJECTARBPROC              glDeleteObject_             = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC          glUseProgramObject_         = NULL; 
PFNGLCREATESHADEROBJECTARBPROC        glCreateShaderObject_       = NULL;
PFNGLSHADERSOURCEARBPROC              glShaderSource_             = NULL;
PFNGLCOMPILESHADERARBPROC             glCompileShader_            = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC      glGetObjectParameteriv_     = NULL;
PFNGLATTACHOBJECTARBPROC              glAttachObject_             = NULL;
PFNGLGETINFOLOGARBPROC                glGetInfoLog_               = NULL;
PFNGLLINKPROGRAMARBPROC               glLinkProgram_              = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC        glGetUniformLocation_       = NULL;
PFNGLUNIFORM1FARBPROC                 glUniform1f_                = NULL;
PFNGLUNIFORM2FARBPROC                 glUniform2f_                = NULL;
PFNGLUNIFORM3FARBPROC                 glUniform3f_                = NULL;
PFNGLUNIFORM4FARBPROC                 glUniform4f_                = NULL;
PFNGLUNIFORM1FVARBPROC                glUniform1fv_               = NULL;
PFNGLUNIFORM2FVARBPROC                glUniform2fv_               = NULL;
PFNGLUNIFORM3FVARBPROC                glUniform3fv_               = NULL;
PFNGLUNIFORM4FVARBPROC                glUniform4fv_               = NULL;
PFNGLUNIFORM1IARBPROC                 glUniform1i_                = NULL;
PFNGLBINDATTRIBLOCATIONARBPROC        glBindAttribLocation_       = NULL;
PFNGLGETACTIVEUNIFORMARBPROC          glGetActiveUniform_         = NULL;

void initARB() {
  glCreateProgramObject_ =        (PFNGLCREATEPROGRAMOBJECTARBPROC)     SDL_GL_GetProcAddress("glCreateProgramObjectARB");
  glDeleteObject_ =               (PFNGLDELETEOBJECTARBPROC)            SDL_GL_GetProcAddress("glDeleteObjectARB");
  glUseProgramObject_ =           (PFNGLUSEPROGRAMOBJECTARBPROC)        SDL_GL_GetProcAddress("glUseProgramObjectARB");
  glCreateShaderObject_ =         (PFNGLCREATESHADEROBJECTARBPROC)      SDL_GL_GetProcAddress("glCreateShaderObjectARB");
  glShaderSource_ =               (PFNGLSHADERSOURCEARBPROC)            SDL_GL_GetProcAddress("glShaderSourceARB");
  glCompileShader_ =              (PFNGLCOMPILESHADERARBPROC)           SDL_GL_GetProcAddress("glCompileShaderARB");
  glGetObjectParameteriv_ =       (PFNGLGETOBJECTPARAMETERIVARBPROC)    SDL_GL_GetProcAddress("glGetObjectParameterivARB");
  glAttachObject_ =               (PFNGLATTACHOBJECTARBPROC)            SDL_GL_GetProcAddress("glAttachObjectARB");
  glGetInfoLog_ =                 (PFNGLGETINFOLOGARBPROC)              SDL_GL_GetProcAddress("glGetInfoLogARB");
  glLinkProgram_ =                (PFNGLLINKPROGRAMARBPROC)             SDL_GL_GetProcAddress("glLinkProgramARB");
  glGetUniformLocation_ =         (PFNGLGETUNIFORMLOCATIONARBPROC)      SDL_GL_GetProcAddress("glGetUniformLocationARB");
  glUniform1f_ =                  (PFNGLUNIFORM1FARBPROC)               SDL_GL_GetProcAddress("glUniform1fARB");
  glUniform2f_ =                  (PFNGLUNIFORM2FARBPROC)               SDL_GL_GetProcAddress("glUniform2fARB");
  glUniform3f_ =                  (PFNGLUNIFORM3FARBPROC)               SDL_GL_GetProcAddress("glUniform3fARB");
  glUniform4f_ =                  (PFNGLUNIFORM4FARBPROC)               SDL_GL_GetProcAddress("glUniform4fARB");
  glUniform1fv_ =                 (PFNGLUNIFORM1FVARBPROC)              SDL_GL_GetProcAddress("glUniform1fvARB");
  glUniform2fv_ =                 (PFNGLUNIFORM2FVARBPROC)              SDL_GL_GetProcAddress("glUniform2fvARB");
  glUniform3fv_ =                 (PFNGLUNIFORM3FVARBPROC)              SDL_GL_GetProcAddress("glUniform3fvARB");
  glUniform4fv_ =                 (PFNGLUNIFORM4FVARBPROC)              SDL_GL_GetProcAddress("glUniform4fvARB");
  glUniform1i_ =                  (PFNGLUNIFORM1IARBPROC)               SDL_GL_GetProcAddress("glUniform1iARB");
  glBindAttribLocation_ =         (PFNGLBINDATTRIBLOCATIONARBPROC)      SDL_GL_GetProcAddress("glBindAttribLocationARB");
  glGetActiveUniform_ =           (PFNGLGETACTIVEUNIFORMARBPROC)        SDL_GL_GetProcAddress("glGetActiveUniformARB");
}

void setShaders() {
  GLuint v, f, p;
  GLint ok;

	const char *vv = "void main()                   \n"
                   "{                             \n"
	                 "  gl_Position = ftransform() + vec4(0.1, -0.25, 0, 0); \n"
                   "}";
  const char *ff = "void main()                \n"
                   "{	                         \n"
	                 "  gl_FragColor = vec4(gl_FragCoord.y/480.0, gl_FragCoord.x/640.0, 0.66, 1.0); \n"
                   "}";

	v = glCreateShaderObject_(GL_VERTEX_SHADER);
	f = glCreateShaderObject_(GL_FRAGMENT_SHADER);

	glShaderSource_(v, 1, &vv,NULL);
	glShaderSource_(f, 1, &ff,NULL);

	glCompileShader_(v);
  glGetObjectParameteriv_(v, GL_OBJECT_COMPILE_STATUS_ARB, &ok);
  if (!ok) {
    char msg[512];
    glGetInfoLog_(v, sizeof msg, NULL, msg);
    printf("shader compilation issue: %s\n", msg);
  }
  assert(ok);

	glCompileShader_(f);
  glGetObjectParameteriv_(f, GL_OBJECT_COMPILE_STATUS_ARB, &ok);
  assert(ok);

	p = glCreateProgramObject_();
	glAttachObject_(p,f);
	glAttachObject_(p,v);

	glLinkProgram_(p);
  glGetObjectParameteriv_(p, GL_OBJECT_LINK_STATUS_ARB, &ok);
  assert(ok);

	glUseProgramObject_(p);
}

static inline const char *emscripten_event_type_to_string(int eventType) {
  const char *events[] = { "(invalid)", "(none)", "keypress", "keydown", "keyup", "click", "mousedown", "mouseup", "dblclick", "mousemove", "wheel", "resize", 
    "scroll", "blur", "focus", "focusin", "focusout", "deviceorientation", "devicemotion", "orientationchange", "fullscreenchange", "pointerlockchange", 
    "visibilitychange", "touchstart", "touchend", "touchmove", "touchcancel", "gamepadconnected", "gamepaddisconnected", "beforeunload", 
    "batterychargingchange", "batterylevelchange", "webglcontextlost", "webglcontextrestored", "mouseenter", "mouseleave", "mouseover", "mouseout", "(invalid)" };
  ++eventType;
  if (eventType < 0) eventType = 0;
  if (eventType >= sizeof(events)/sizeof(events[0])) eventType = sizeof(events)/sizeof(events[0])-1;
  return events[eventType];
}

EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData) {
  printf("%s, screen: (%d,%d), client: (%d,%d),%s%s%s%s button: %hu, buttons: %hu, movement: (%d,%d), target: (%d, %d)\n",
    emscripten_event_type_to_string(eventType), e->screenX, e->screenY, e->clientX, e->clientY,
    e->ctrlKey ? " CTRL" : "", e->shiftKey ? " SHIFT" : "", e->altKey ? " ALT" : "", e->metaKey ? " META" : "", 
    e->button, e->buttons, e->movementX, e->movementY, e->targetX, e->targetY);

  if (e->screenX != 0 && e->screenY != 0 && e->clientX != 0 && e->clientY != 0 && e->targetX != 0 && e->targetY != 0) {
    if (eventType == EMSCRIPTEN_EVENT_CLICK) printf("gotClick = 1\n");
    if (eventType == EMSCRIPTEN_EVENT_MOUSEDOWN && e->buttons != 0) printf("gotClick = 1\n");
    if (eventType == EMSCRIPTEN_EVENT_DBLCLICK) printf("gotClick = 1\n");
    if (eventType == EMSCRIPTEN_EVENT_MOUSEUP) printf("gotClick = 1\n");
    if (eventType == EMSCRIPTEN_EVENT_MOUSEMOVE && (e->movementX != 0 || e->movementY != 0)) printf("gotMouseMove = 1\n");
  }
  // draw();

  return 0;
}


EM_BOOL key_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
  int dom_pk_code = emscripten_compute_dom_pk_code(e->code);

  printf("%s, key: \"%s\" \n",
    emscripten_event_type_to_string(eventType), 
    e->key
  );
  if (eventType == EMSCRIPTEN_EVENT_KEYUP) printf("\n"); // Visual cue

  // draw();
  // Return true for events we want to suppress default web browser handling for.
  // For testing purposes, want to return false here on most KeyDown messages so that they get transformed to KeyPress messages.
  return e->keyCode == DOM_VK_BACK_SPACE // Don't navigate away from this test page on backspace.
    || e->keyCode == DOM_VK_TAB // Don't change keyboard focus to different browser UI elements while testing.
    || (e->keyCode >= DOM_VK_F1 && e->keyCode <= DOM_VK_F24) // Don't F5 refresh the test page to reload.
    || e->ctrlKey // Don't trigger e.g. Ctrl-B to open bookmarks
    || e->altKey // Don't trigger any alt-X based shortcuts either (Alt-F4 is not overrideable though)
    || eventType == EMSCRIPTEN_EVENT_KEYPRESS || eventType == EMSCRIPTEN_EVENT_KEYUP; // Don't perform any default actions on these.
}


// Our "main loop" function. This callback receives the current time as
// reported by the browser, and the user data we provide in the call to
// emscripten_request_animation_frame_loop().
EM_BOOL one_iter(double time, void* userData) {
  // Can render to the screen here, etc.
  puts("one iteration");
    glColor3f(0, 1, 1); // is overridden by the shader, useful for debugging native builds
    glBegin( GL_TRIANGLES );
      glTexCoord2i(0, 0); glVertex3f( 10,  10,  0);
      glTexCoord2i(1, 0); glVertex3f( 300, 10,  0);
      glTexCoord2i(1, 1); glVertex3f( 300, 328, 0);
    glEnd();

    glColor3f(1, 1, 0); // is overridden by the shader, useful for debugging native builds
    glBegin( GL_TRIANGLES );
        glTexCoord2f(0, 0.5); glVertex3f(410, 10,  0);
        glTexCoord2f(1, 0.5); glVertex3f(600, 10,  0);
        glTexCoord2f(1, 1  ); glVertex3f(630, 400, 0);
    glEnd();

    SDL_GL_SwapWindow(window);

  // Return true to keep the loop running.
  return EM_TRUE;
}

int main() {
      //SDL_Surface *screen;
    
    SDL_GLContext context;
    emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, key_callback);
    emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, mouse_callback);


    assert(SDL_Init(SDL_INIT_VIDEO) == 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //screen = SDL_SetVideoMode( 640, 480, 16, SDL_OPENGL );
    //assert(screen);

    window = SDL_CreateWindow("sdlglshader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
    assert(window);

    context = SDL_GL_CreateContext(window);

    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    initARB();
    setShaders();
#ifdef __EMSCRIPTEN__
  // Receives a function to call and some user data to provide it.
  emscripten_request_animation_frame_loop(one_iter, 0);

// Not sure how to make this run at the moment:
// #else   
//   while (1) {
//     one_iter();
//     // Delay to keep frame rate constant (using SDL).
//     SDL_Delay(time_to_next_frame());
//   }
#endif
}