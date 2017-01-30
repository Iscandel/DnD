#ifndef H__KEYREPEATMANAGER_061120111723__H
#define H__KEYREPEATMANAGER_061120111723__H

#include "Gaia/Event.h"
#include "Gaia/tools/NonCopyable.h"

namespace gaia
{
class KeyRepeatManager : public NonCopyable
{
public:
	KeyRepeatManager();

	void newKeyboardEvent(gaia::KeyboardEvent& ev);

	void manageKeyRepeat(unsigned int elapsedTime);

protected:
	unsigned int myInitialKeyRepeatTime;
	unsigned int myKeyRepeatTime;
	bool myIsTextEnteredOk;
	bool myIsKeyPressedOk;
	KeyboardEvent myLastKeyPressedEvent;
	KeyboardEvent myLastTextEnteredEvent;

	const unsigned int TIME_OUT_REPEAT_FIRST;
	const unsigned int TIME_OUT_REPEAT;
};

} //end namespace

#endif