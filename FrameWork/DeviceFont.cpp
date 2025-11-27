/*
□ Device 클래스의 용도 □

1. Direct3D(Device9)와의 연결 및 설정 
Device9에 Direct3D 디바이스 포인터를 저장한다
2D 렌더링을 위한 Sprite 객체 생성(D3DXCreateSprite)
텍스트 출력을 위한 폰트(Font) 생성 및 관리(D3DXCreateFontIndirect)

2. DrawString 함수로 텍스트 출력 지원
DrawString은 원하는 위치(x, y)와 색상(color)으로 문자열(msg)을 화면에 출력한다
내부적으로 Sprite의 Begin/End로 알파 블렌딩 상태에서 DrawText를 호출한다
RECT 설정 시 문자열 길이와 폰트 높이로 영역을 산출한다 
현재 색상 부분은 고정값(D3DCOLOR_XRGB(255, 0, 255))으로 되어 있지만, 
인자 color를 활용하면 다양한 색을 사용 가능하다

□ 전역 객체 DV □

Device DV 
다른 클래스에서 DV.DrawString 형식으로 텍스트, 디버그 메시지, UI 요소를 쉽게 그릴 수 있게 한다

□ 실제 용도 □

디버그 박스 및 충돌 박스 표시
게임 내 텍스트 UI, 점수판, 안내 메시지, 디버그 출력
폰트 스타일 관리
등 다양한 2D 텍스트 출력에 사용된다 
*/
#pragma once
#include "Include.h"

g_DeviceFont dv_font;

g_DeviceFont::g_DeviceFont(void)
{
}

g_DeviceFont::~g_DeviceFont(void)
{
}

bool g_DeviceFont::Create( HWND g_hWnd )
{

	Direct3D = Direct3DCreate9( D3D_SDK_VERSION );

	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;												// 전체 화면 모드로 생성
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							// 가장 효율적인 SWAP 효과
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				            // 현재 바탕화면 모드에 맞춰 후면 버퍼를 생성
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE ;
	d3dpp.BackBufferWidth = SCREEN_WITH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	Direct3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &Device9 );



	D3DXCreateSprite( Device9 , &Sprite ) ;

	ZeroMemory( &fdesc , sizeof(fdesc) ) ;
	fdesc.Height = 40 ;
	fdesc.Width = 22 ;
	fdesc.Weight = 2000 ;
	fdesc.Italic = FALSE ;
	fdesc.CharSet = DEFAULT_CHARSET ;
	strcpy( fdesc.FaceName , "돋움" ) ;

	D3DXCreateFontIndirect( Device9 , &fdesc , &Fonts ) ;

	return true;

}

bool g_DeviceFont::DrawString( const char* msg , int x , int y , D3DCOLOR color)
{
	RECT rect = { x , y , fdesc.Width*strlen(msg) , fdesc.Height } ;

	Sprite->Begin( D3DXSPRITE_ALPHABLEND ) ;
	//Fonts->DrawText( Sprite , msg , strlen( msg ) , &rect , DT_NOCLIP , D3DCOLOR_XRGB(250,250,250) ) ;
	Fonts->DrawText( Sprite , msg , strlen( msg ) , &rect , DT_NOCLIP , color ) ;
	Sprite->End() ;
	
	return true;
}