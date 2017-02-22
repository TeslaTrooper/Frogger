#ifndef DIRECT3D_TEXTURE
#define DIRECT3D_TEXTURE

#include <d3d9.h>
#include <d3dx9.h>

class Direct3DTexture {
	IDirect3DTexture9* data;
	D3DXIMAGE_INFO srcInfo;

	int width, height;

public:

	/*
		Erzeugt eine neue Direct3DTexture.
		@param ist der Pfad zur textur.
		@param d3device ist das Ger�t, mit dem die Textur geladen wird.
	*/
	Direct3DTexture(char* fileName, LPDIRECT3DDEVICE9* d3dDevice);
	~Direct3DTexture();


	/*
		@return gibt den Pointer f�r die Texturdaten zur�ck.
	*/
	IDirect3DTexture9* getData();


	/*
		@return gibt die Breite der Textur zur�ck.
	*/
	int getWidth() { return (int) this->srcInfo.Width; };


	/*
		@return gibt die H�he der Textur zur�ck.
	*/
	int getHeight() { return (int) this->srcInfo.Height;};
};

#endif DIRECT3D_TEXTURE