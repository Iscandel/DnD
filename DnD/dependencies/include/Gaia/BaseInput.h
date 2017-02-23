#ifndef H__ENTREE_020520111927__H
#define H__ENTREE_020520111927__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include <queue>

#include "Gaia/Config.h"
#include "Gaia/Event.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////
/// \brief Base class for processing input events.
///
/// This class is intended to be inherited to convert inputs from external
/// APIs to GUI input.
///////////////////////////////////////////////////////////////////////////
class GAIA_DLL BaseInput
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Default Constructor.
	///////////////////////////////////////////////////////////////////////////
	BaseInput(void) {}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Virtual destructor.
	///////////////////////////////////////////////////////////////////////////
	virtual ~BaseInput(void) {}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Must be overriden in derived classes.
	/// 
	/// Should convert an external input into a corresponding GAIA's event.
	///////////////////////////////////////////////////////////////////////////
	virtual void process() = 0;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Return the pending queue of keyboard events.
	///
	///	\return the queue of keyboard events not processed yet.
	///////////////////////////////////////////////////////////////////////////
	static std::queue<KeyboardEvent>& getKeyboardEv() {return myKeyboardEv;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Return the pending queue of keyboard events.
	///
	///	\return The queue of mouse events not processed yet.
	///////////////////////////////////////////////////////////////////////////
	static std::queue<MouseEvent>& getMouseEv() {return myMouseEv;}

protected:
	static std::queue<KeyboardEvent> myKeyboardEv; ///< Keyboard events queue
	static std::queue<MouseEvent> myMouseEv; ///< Mouse events queue
};
};

#endif