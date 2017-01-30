#ifndef H__TEXTWIDGETBASERENDERER_300820110031__H
#define H__TEXTWIDGETBASERENDERER_300820110031__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/WidgetRenderer.h"
#include "Gaia/tools/Observer.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Interface class for text widget renderer.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL TextWidgetBase :
	/*public gaia::TplWidgetRenderer<T>,*/ public gaia::Observer
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Default constructor.
	///////////////////////////////////////////////////////////////////////////
	TextWidgetBase();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Computes the caret position of the model, from the given pixel
	/// position relative to the widget coordinate system.
	///
	/// \param pos : Mouse position, in the widget coordinate system.
	///////////////////////////////////////////////////////////////////////////
	virtual int computeCaretPosition(const Point& pos) = 0;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Computes the caret position of the model, in the case it is
	/// moved using the keyboard.
	///
	/// \param isNewLineSup : if true, the caret is moved up. If false, the
	/// caret is moved down.
	///////////////////////////////////////////////////////////////////////////
	virtual int computeCaretPosition(bool isNewLineSup) = 0;
};

///////////////////////////////////////////////////////////////////////////////
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// \brief Base template class for text widget renderer.
///////////////////////////////////////////////////////////////////////////////
template<class T>
class TplTextWidgetRenderer : public TextWidgetBase, public gaia::TplWidgetRenderer<T>
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param w : The widgets set to the renderer. Must be a a derived class
	/// from BaseTextWidget.
	/////////////////////////////////////////////////////////////////////
	TplTextWidgetRenderer(PtrWidget w = PtrWidget());

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the rectangle defining the text area.
	///
	/// \param w : The widgets set to the renderer. Must be a a derived class
	/// from BaseTextWidget.
	/////////////////////////////////////////////////////////////////////
	IntRect getTextArea();
	//Rect<double> getTextArea();

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Computes whether the caret should be displayed.
	///
	/// \param elapsedTime : Shoudl be the application frame time, or the time
	/// elapsed since the last call to update.
	///////////////////////////////////////////////////////////////////////////
	virtual void update(unsigned int elapsedTime);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when the renderer was assigned to a widget.
	/// 
	/// Copies the renderer properties.
	///
	/// \param w : The widget owning the renderer.
	///////////////////////////////////////////////////////////////////////////
	virtual void onAssignedToWidget(PtrWidget w);

	virtual void onReleasedFromWidget(PtrWidget w);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Set the text selection color.
	///
	/// \param col : Text selection color.
	///////////////////////////////////////////////////////////////////////////
	void setSelectionColor(const Color& col) {mySelectionColor = col;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the text selection color.
	///
	/// \return The selection color.
	///////////////////////////////////////////////////////////////////////////
	const Color& getSelectionColor() const {return mySelectionColor;}

protected:
	///Indicates whether the caret should be displayed
	bool myMustDisplayCaret;

	///Some accumulator to record elapsed time.
	float myElapsedTime;

	///Text selection color
	Color mySelectionColor;
};

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T>
TplTextWidgetRenderer<T>::TplTextWidgetRenderer(PtrWidget w)
:TplWidgetRenderer(w)
,myMustDisplayCaret(false)
,myElapsedTime(0.f)
,mySelectionColor(0, 0, 255)
{
	//myWidget->assignToModel(this);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T>
//Rect<double> TplTextWidgetRenderer<T>::getTextArea()
IntRect TplTextWidgetRenderer<T>::getTextArea()
{
	const std::string areaName = "text";

	//Rect<double> rect(0, 0, myWidget->getWidth(), myWidget->getHeight());
	IntRect rect(0, 0, this->myWidget->getWidth(), this->myWidget->getHeight());
	if(IWidgetRenderer::myAreas.find(areaName) != IWidgetRenderer::myAreas.end())
	{
		rect = IWidgetRenderer::myAreas[areaName];
		//rect = myAreas[areaName];

		////If relative coordinates
		//rect.x = myAreas[areaName].x * myWidget->getWidth();

		////If relative coordinates
		//rect.y = myAreas[areaName].y * myWidget->getHeight();

		////If relative coordinates
		//rect.width = myAreas[areaName].width * myWidget->getWidth();

		////If relative coordinates
		//rect.height = myAreas[areaName].height * myWidget->getHeight();
	}

	return rect;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T>
void TplTextWidgetRenderer<T>::update(unsigned int elapsedTime)
{	
	myElapsedTime += elapsedTime;
	if(this->myWidget->isEnabled() && this->myWidget->hasFocus() && ((int)(myElapsedTime * 2 / 1000.f) % 2 == 0) )
	{
		myMustDisplayCaret = true;
	}
	else
	{
		myMustDisplayCaret = false;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T>
void TplTextWidgetRenderer<T>::onAssignedToWidget(PtrWidget w)
{
	IWidgetRenderer::onAssignedToWidget(w);
	//myWidget->notifyObservers(); //not perfect
	//this->update((Observable*)myWidget);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T>
void TplTextWidgetRenderer<T>::onReleasedFromWidget(PtrWidget w)
{
	IWidgetRenderer::onReleasedFromWidget(w);
	this->myWidget->removeObserver(this);
	//this->update((Observable*)myWidget);
}

}//end namespace

#endif
