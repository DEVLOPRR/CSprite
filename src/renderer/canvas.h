#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../history.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LAYER_NAME_MAX 512

typedef struct {
	char         name[LAYER_NAME_MAX];
	SDL_Texture* texture;
	uint8_t*     pixels;
	History_T*   history;
} CanvasLayer_T;

typedef struct {
	int32_t size; // num of "slots" used
	int32_t capacity; // total num of "slots"
	CanvasLayer_T** layers;
} CanvasLayerArr_T;

int  Canvas_Init(int32_t w, int32_t h, SDL_Renderer* ren); // Initialize Canvas
void Canvas_Destroy(void); // Destroy Canvas
void Canvas_NewFrame(SDL_Renderer* ren); // Call Before All Of The Calls To Canvas_Layer();
void Canvas_Layer(CanvasLayer_T* c, bool UpdateTexture, SDL_Renderer* ren); // Specify What Layers To Render
void Canvas_FrameEnd(SDL_Renderer* ren, SDL_Rect* r); // Must be called after Canvas_NewFrame & Canvas_Layer calls are done.
void Canvas_Resize(int32_t w, int32_t h, SDL_Renderer* ren); // Resize Canvas

SDL_Texture*      Canvas_GetTex();
CanvasLayerArr_T* Canvas_CreateArr(int32_t capacity);
void              Canvas_DestroyArr(CanvasLayerArr_T* arr);
void              Canvas_ResizeArr(CanvasLayerArr_T* arr, int32_t newCapacity); // if newCapacity is less than arr's capacity, all the extra layers will be destroyed with "Canvas_DestroyLayer" and memory with newCapacity size will be allocated.
CanvasLayer_T*    Canvas_CreateLayer(SDL_Renderer* ren);
void              Canvas_UpdateLayerTexture(CanvasLayer_T* c); // you need to call this function after you update CanvasLayer_T's "pixel" member
void              Canvas_DestroyLayer(CanvasLayer_T* c);

#ifdef __cplusplus
}
#endif

