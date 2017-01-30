#ifndef H__WIDGETRENDERER__130620112059__H
#define H__WIDGETRENDERER__130620112059__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Config.h"
#include "Gaia/Image.h"
#include "Gaia/Rectangle.h"
#include "Gaia/widgets/BaseWidget.h"

#include <string>
#include <map>

namespace gaia
{
class BaseWidget;

///////////////////////////////////////////////////////////////////////////////
/// \brief Base class for widget renderer.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL IWidgetRenderer
{
public:
	typedef std::map<std::string, Image> ImageList;
	typedef std::map<std::string, LayoutInfos> LayoutAreaList;
	//typedef std::map<std::string, Rect<double> > AreaList;
	typedef std::map<std::string, IntRect> AreaList;
	typedef std::map<std::string, properties::PtrProperty> PropertyList;

public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///////////////////////////////////////////////////////////////////////////
	IWidgetRenderer();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Virtual destructor
	///////////////////////////////////////////////////////////////////////////
	virtual ~IWidgetRenderer(void);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds an image identified by its state name.
	///
	/// \param stateName : A name identifying the image.
	/// \param image : Image to add.
	///////////////////////////////////////////////////////////////////////////
	void addImage(const std::string& stateName, const Image& image);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes an image previously added
	///
	/// \param stateName : name identifying the image.
	///////////////////////////////////////////////////////////////////////////
	void deleteImage(const std::string& stateName);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Checks whether the image is present in this widget renderer, or not.
	///
	/// \param stateName : name identifying the image.
	///
	/// \return true if the image was found, false if it was not found.
	///////////////////////////////////////////////////////////////////////////
	bool imageExists(const std::string& etat);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the image identified by its state name.
	///
	/// Throws an exception if the image was not found.
	///
	/// \param stateName : A name identifying the image.
	/// \param A reference to the image.
	///////////////////////////////////////////////////////////////////////////
	Image& getImage(const std::string& stateName);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Converts the given widget into the specified type.
	///
	/// If the widget cannot be casted, an exception is thrown.
	///
	/// \param widget : The widget to cas
	/// \return The converted wigets, into the template type.
	///////////////////////////////////////////////////////////////////////////
	template<class W>
	W* convertWidget(PtrWidget widget);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Assigns the given widget to the renderer
	///
	/// If the widget cannot be casted, an exception is thrown.
	///
	/// \param widget : A smart pointer to the widget.
	///////////////////////////////////////////////////////////////////////////
	virtual void setWidget(PtrWidget widget) = 0;

	//template<class T>
	//void draw(T& cible, int x = 0, int y = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Updates the widget renderer. Should be overriden in derived
	/// classes if necessary.
	///
	/// \param elapsedTime : Elapsed time since the last frame.
	///////////////////////////////////////////////////////////////////////////
	virtual void update(unsigned int) {}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws the widget. 
	/// 
	/// Don't override this function, unless you know what you are doing.
	///
	/// \param x : X component of the parent widget.
	/// \param y : Y component of the parent widget.
	///////////////////////////////////////////////////////////////////////////
	virtual void draw(int x = 0, int y = 0) = 0;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds an area identified by its name, and used as information
	/// during the rendering of the widget.
	///
	/// \param areaName : Name of the area.
	/// \param rect : Area (top left corner + size).
	///////////////////////////////////////////////////////////////////////////
	//void addArea(const std::string& areaName, const Rect<double>& rect);

	void addLayoutArea(const std::string& areaName, const LayoutInfos& infos);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes an area previously added.
	///
	/// \param areaName : Name of the area.
	///////////////////////////////////////////////////////////////////////////
	void deleteArea(const std::string& areaName);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Enables the clipping for the renderer. 
	///
	/// The default clipping size if the widget bounding rect.
	///
	/// \param clipping : true to enable clipping, false to disable it.
	///////////////////////////////////////////////////////////////////////////
	void setClipping(bool clipping) {myMustClip = clipping;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether the widget is clipped by the renderer.
	///
	/// \return true if the renderer is performing clipping, false if it is not.
	///////////////////////////////////////////////////////////////////////////
	bool isClipping() const {return myMustClip;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Makes the clipping area fixed, even if the widget owning the
	/// renderer is resized.
	///
	/// \param fixe : true if the clipping area should never be automatically
	/// resized, false if it should be.
	///////////////////////////////////////////////////////////////////////////
	void setFixedClippingArea(bool fixed) {myFixedClippingArea = fixed;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether the clipping area is fixed, even if the widget
	/// owning the renderer is resized.
	///
	/// \return true if the clipping area should never be automatically resized, 
	/// false if it should be	///////////////////////////////////////////////////////////////////////////
	bool isFixedClippingArea() const {return myFixedClippingArea;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the current clipping area.
	///
	/// \return A rectangle defining the current clipping area.
	///
	/// \see setClipping
	/// \see setFixedClippingArea
	///////////////////////////////////////////////////////////////////////////
	const IntRect& getClippingArea() const {return myClippingArea;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the current clipping area.
	///
	/// Never call this function during the drawing step. You could face to leaks.
	///
	/// \param area : A rectangle defining the current clipping area.
	///
	/// \see setFixedClippingArea
	///////////////////////////////////////////////////////////////////////////
	void setClippingArea(const IntRect& zone) {myClippingArea = zone;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a property to the renderer.
	///
	/// \param prop : The property to add.
	///////////////////////////////////////////////////////////////////////////
	virtual void addProperty(properties::PtrProperty prop) = 0;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes a property.
	///
	/// \param prop : A smart pointer to the property to delete
	///////////////////////////////////////////////////////////////////////////
	virtual void deleteProperty(properties::PtrProperty prop) = 0;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when the renderer was assigned to a widget.
	/// 
	/// Copies the renderer properties.
	///
	/// \param w : The widget owning the renderer.
	///////////////////////////////////////////////////////////////////////////
	virtual void onAssignedToWidget(PtrWidget w)
	{
		PropertyList::iterator it = myProperties.begin();

		for(it; it != myProperties.end(); ++it)
		{
			w->addProperty(it->second);
		}

		//if(E_onAssignedToWidget != NULL)
		//{
		//	Event ev(w.get());
		//	E_onAssignedToWidget(ev);
		//}
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when the renderer was released from a widget.
	/// 
	/// deletes the renderer properties from the widget.
	///
	/// \param w : The widget which was owning the renderer.
	///////////////////////////////////////////////////////////////////////////
	virtual void onReleasedFromWidget(PtrWidget w)
	{
		PropertyList::iterator it = myProperties.begin();

		for(it; it != myProperties.end(); ++it)
		{
			w->deleteProperty(it->first);
		}
	}

	virtual void resizeAreas() = 0;

protected:
	ImageList myImages; ///< Image map used by the renderer.
	LayoutAreaList myLayoutAreas;
	AreaList myAreas; ///< Area map used by the renderer

	PropertyList myProperties; ///< Property map used by the renderer
 
	///Indicates whether we should clip to the defined area during the rendering
	bool myMustClip; 
	///Indicates whether we should adjust the clipping area after a resize of the owning widget
	bool myFixedClippingArea; 
	///The clipping area
	IntRect myClippingArea;
};

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// \brief Inherited renderer class to handle a particular widget. 
///
/// Renderers should derive from this class.
///////////////////////////////////////////////////////////////////////////////
template<class T>
class TplWidgetRenderer : public IWidgetRenderer
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param widget : A pointer to the widget owning the renderer.
	///////////////////////////////////////////////////////////////////////////
	TplWidgetRenderer(PtrWidget widget)
	{
		setWidget(widget);
	}

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Assigns the widget to the renderer.
	///
	/// \param widget : A pointer to the widget owing the renderer.
	///////////////////////////////////////////////////////////////////////////
	void setWidget(PtrWidget widget)
	{
		if(widget == NULL)
			myWidget = NULL;
		else
		{
			myWidget = convertWidget<T>(widget);
			myClippingArea = widget->getScreenCoordinates();
			onAssignedToWidget(widget);
		}
	}

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a property to the renderer and to the associated widget.
	///
	/// \param prop : The property to add.
	///////////////////////////////////////////////////////////////////////////
	void addProperty(properties::PtrProperty prop)
	{
		//onReleasedFromWidget(PtrWidget w);
		myProperties.insert(std::make_pair(prop->getName(), prop));
		myWidget->addProperty(prop);
	}

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes a property from the renderer and to the associated widget.
	///
	/// \param prop : The property to delete.
	///////////////////////////////////////////////////////////////////////////
	void deleteProperty(properties::PtrProperty prop)
	{
		if(myProperties.find(prop->getName()) == myProperties.end()) 
			myProperties.erase(prop->getName());
		myWidget->deleteProperty(prop->getName());
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws the widget.
	///
	/// \param x : X component of the parent widget.
	/// \param y : Y component of the parent widget.
	///////////////////////////////////////////////////////////////////////////
	virtual void draw(int x = 0, int y = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws the widget. 
	///
	/// Should be overriden by derived class to perform the drawing.
	///
	/// \param Gfx : Pointer the graphics engine.
	///////////////////////////////////////////////////////////////////////////
	virtual void draw_impl(BaseGraphics* Gfx) = 0;

	virtual void resizeAreas();

protected:
	T* myWidget; ///<Template type of the widget
};

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class W>
W* IWidgetRenderer::convertWidget(PtrWidget widget) 
{
	W* castedWidget = dynamic_cast<W*>(widget.get());
	if(!castedWidget)
	{
		throw GuiException("Widget " + widget->getName() + 
			" cannot be casted in the WidgetRenderer");
	}

	return castedWidget;
}



///////////////////////////////////////////////////////////////////////////////
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T>
void TplWidgetRenderer<T>::draw(int x, int y)
{
	BaseGraphics* Gfx = myWidget->getGraphics();

	//start clipping
	if(myMustClip)
		Gfx->pushClippingArea(myClippingArea);

	const Point& prevCoords = Gfx->getOrigin();
	Gfx->setOrigin(x + myWidget->getX(), y + myWidget->getY());

	draw_impl(Gfx);
	
	Gfx->setOrigin(prevCoords.x, prevCoords.y);
	//cible.(BaseWidget::draw();
	//myWidget->drawChildren(x, y);

	//Reset the previous clipping state
	if(myMustClip)
		Gfx->popClippingArea();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T>
void TplWidgetRenderer<T>::resizeAreas()
{
	assert(myWidget && "resize renderer areas : no widget set.");

	//AreaList::iterator it = myAreas.begin();
	LayoutAreaList::iterator layoutIt = myLayoutAreas.begin();
	for(; layoutIt != myLayoutAreas.end(); ++layoutIt)
	{
		IntRect rect = layoutIt->second.getComputedDimensions(myWidget);
		myAreas[layoutIt->first] = rect;
	}
}

} //end namespace

#endif