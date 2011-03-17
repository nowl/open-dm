bin_PROGRAMS = open-dm

open_dm_SOURCES = \
	SlabRenderer.cpp \
	BlockRenderer.cpp \
	StepCamera.cpp \
	PlaneRenderer.cpp \
	UniqueName.cpp \
	DataReader.cpp \
	test.cpp

open_dm_CXXFLAGS = @SDL_CFLAGS@ -I../../black/black/include 
open_dm_LDFLAGS = @SDL_LIBS@ @SDL_MIXER_LIBS@ @SDL_IMAGE_LIBS@ @SDL_TTF_LIBS@ @GL_LIBS@ -L../../black/black/src/ -lblack
