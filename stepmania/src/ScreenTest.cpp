#include "global.h"
/*
-----------------------------------------------------------------------------
 File: ScreenTest.h

 Desc: Area for testing.

 Copyright (c) 2001-2002 by the person(s) listed below.  All rights reserved.
	Chris Danford, Glenn Maynard, Lance Gilbert
-----------------------------------------------------------------------------
*/

#include "global.h"
#include "ScreenTest.h"
#include "ScreenSandbox.h"
#include "ScreenTestSound.h"
#include "ScreenTestFonts.h"
#include "ScreenManager.h"
#include "RageSounds.h"


ScreenTest::~ScreenTest()
{
	delete current;
}

void ScreenTest::SetScreen(int num)
{
	cur_screen = num;
	delete current;
	if(num > 2) num = 0;
	if(num == 0)
		current=new ScreenSandbox("ScreenSandbox");
	else if(num == 1)
		current=new ScreenTestSound("ScreenTestSound");
	else if(num == 2)
		current=new ScreenTestFonts("ScreenTestFonts");
}

ScreenTest::ScreenTest( CString sClassName ) : Screen( sClassName )
{
	current = NULL;
	cur_screen = -1;

	SOUND->StopMusic();

	SetScreen(0);
}

void ScreenTest::Update(float f) { current->Update(f); Screen::Update(f); }
void ScreenTest::HandleScreenMessage( const ScreenMessage SM ) { current->HandleScreenMessage(SM); }
void ScreenTest::Draw() { current->Draw(); }

void ScreenTest::Input( const DeviceInput& DeviceI, const InputEventType type, const GameInput &GameI, const MenuInput &MenuI, const StyleInput &StyleI )
{
	if(DeviceI.device == DEVICE_KEYBOARD)
	{
		if(DeviceI.button >= SDLK_F9 && DeviceI.button <= SDLK_F12)
		{
			if( type != IET_FIRST_PRESS ) return;
			SetScreen(DeviceI.button - SDLK_F9);
			return;
		}
		if(DeviceI.button == SDLK_ESCAPE)
		{
			if( type != IET_FIRST_PRESS ) return;
			SCREENMAN->SetNewScreen( "ScreenTitleMenu" );
			return;
		}
	}
	
	current->Input( DeviceI, type, GameI, MenuI, StyleI );
}

/*
 * (c) 2003 Chris Danford, Glenn Maynard, Lance Gilbert
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
