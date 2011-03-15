bin_PROGRAMS = open-dungeons

open_dungeons_SOURCES = \
	SlabRenderer.cpp \
	BlockRenderer.cpp \
	StepCamera.cpp \
	PlaneRenderer.cpp \
	UniqueName.cpp \
	DataReader.cpp \
	test.cpp

open_dungeons_CXXFLAGS = @SDL_CFLAGS@ -I../../black/black/include 
open_dungeons_LDFLAGS = @SDL_LIBS@ @SDL_MIXER_LIBS@ @SDL_IMAGE_LIBS@ @SDL_TTF_LIBS@ @GL_LIBS@ -L../../black/black/src/ -lblack
