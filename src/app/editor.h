#ifndef CSPRITE_SRC_APP_EDITOR_H_INCLUDED_
#define CSPRITE_SRC_APP_EDITOR_H_INCLUDED_
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "pixel.h"
#include "app/texture.h"
#include "image/image.h"

typedef struct {
	uint32_t min_x, min_y, max_x, max_y;
} mmRect_t;

typedef enum {
	TOOL_BRUSH,
	TOOL_ERASER,
	TOOL_PAN,
	TOOL_NONE
} tool_t;

typedef struct {
	struct {
		image_t image;
		texture_t texture;
	} canvas;
	struct {
		char* path;
		char* name; // Points to start of basename in `path`
	} file;
	struct {
		struct {
			bool rounded;
			uint32_t size;
			pixel_t color;
		} brush;
		struct {
			tool_t previous, current;
		} type;
	} tool;
	struct {
		float x, y, w, h, scale;
	} view;
	struct {
		struct {
			int32_t x, y;
		} down, last;
	} mouse;
} editor_t;

int EditorInit(editor_t* ed, uint32_t width, uint32_t height);
int EditorInitFrom(editor_t* ed, const char* filePath);
void EditorDestroy(editor_t* ed);

void EditorProcessInput(editor_t* ed);

mmRect_t EditorOnMouseDown(editor_t* ed, int32_t x, int32_t y);
mmRect_t EditorOnMouseMove(editor_t* ed, int32_t x, int32_t y);
mmRect_t EditorOnMouseUp(editor_t* ed, int32_t x, int32_t y);

void EditorZoomOut(editor_t* ed);
void EditorZoomIn(editor_t* ed);

void EditorUpdateView(editor_t* ed); // When ed.view.scale changes
int EditorSetFilePath(editor_t* ed, const char* filePath);

#endif
