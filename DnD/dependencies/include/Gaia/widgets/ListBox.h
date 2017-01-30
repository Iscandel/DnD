#ifndef H__LISTBOX_210920110157__H
#define H__LISTBOX_210920110157__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/BaseWidget.h"
#include "Gaia/widgets/TypedefList.h"
#include "Gaia/widgets/IText.h"

#include <list>

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Widget managing an item list (often strings tems) and enabling to
/// to select one or more items.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL ListBox :
	public gaia::BaseWidget, public IText
{
public:
	///Selection Type
	enum TypeSelection
	{
		SIMPLE_SELECTION, ///< items, 1 by 1
		MULTILINES		  ///< Several items can be selected at the same tme.
	};

	///The collection containing all items.
	typedef std::vector<PtrBaseListBoxItem> ItemList; 
	///List containing all selected indices
	typedef std::vector<unsigned int> SelectedIndicesList;

public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param x: X position relatively to the parent widget (or the window if
	/// it is the top level widget).
	///
	/// \param y: Y position relatively to the parent widget (or the window if
	/// it is the top level widget).
	///
	/// \param width: Width of the widget.
	///
	/// \param height: Height of the widget.
	///////////////////////////////////////////////////////////////////////////
	ListBox(const std::string& name = "", int x = 0, int y = 0, int width = 0, int height = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param dimensions: Rectangle defining the widget size (top left 
	/// position is relative to parent widget, or the screen if the widget is 
	/// the top level widget).
	///////////////////////////////////////////////////////////////////////////
	ListBox(const std::string& name, const IntRect& dimensions);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a new item to the collection.
	///
	/// \param item : A smart pointer to the item to add
	///////////////////////////////////////////////////////////////////////////
	void addItem(PtrBaseListBoxItem item);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes an item from the collection.
	///
	/// \param item : A smart pointer to the item to remove.
	///////////////////////////////////////////////////////////////////////////
	void removeItem(PtrBaseListBoxItem item);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes an item from the collection.
	///
	/// \param item : Index of the item to remove.
	///////////////////////////////////////////////////////////////////////////
	void removeItem(unsigned int index);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the selected item, a null pointer if no item is selected.
	///
	/// \return A smart pointer to the item selected item.
	///////////////////////////////////////////////////////////////////////////
	PtrBaseListBoxItem getSelectedItem() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the selected item, a null pointer if no item is selected.
	///
	/// \return A smart pointer to the item selected item.
	///////////////////////////////////////////////////////////////////////////
	template<class T>
	T getSelectedItem() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns all selected items, an empty list if no item is selected.
	///
	/// \return An item list, containing the selected ones.
	///////////////////////////////////////////////////////////////////////////
	ItemList getSelectedItems() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Return the index of the selected item. Returns -1 if no item is
	/// selected.
	///
	/// \return The selected item index, -1 if no item is selected.
	///////////////////////////////////////////////////////////////////////////
	int getSelectedIndex() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the indices of all selected items. Returns an empty list
	/// if no item is selected.
	///
	/// \return A selected indices list.
	///////////////////////////////////////////////////////////////////////////
	const SelectedIndicesList& getSelectedIndices() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the value corresponding to the selected item. 
	///
	/// A value is a representation of what is contained in the item. For 
	/// example, text items would return a string value. Nothing is done is no 
	/// item is selected.
	///
	///////////////////////////////////////////////////////////////////////////
	template<class T>
	void getSelectedValue(T& value)
	{
		PtrBaseListBoxItem item = getSelectedItem();
		if(item)
		{
			//value = item->getValue();
		}

		//return T();
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the values corresponding to the selected items. 
	///
	/// A value is a representation of what is contained in the item. For 
	/// example, text items would return a string value. Nothing is done is no 
	/// item is selected.
	///
	///////////////////////////////////////////////////////////////////////////
	//template<class T>
	//void getSelectedValues(std::vector<T>& res)
	//{
	//	//std::vector<T> res;

	//	std::vector<PtrBaseListBoxItem> items = getSelectedItems();
	//	for(unsigned int i = 0; i < items.size(); i++)
	//	{
	//		//res.push_back(items->getValue());
	//	}

	//	return res;
	//}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the value corresponding to the selected item. 
	///
	/// A value is a representation of what is contained in the item. For 
	/// example, text items would return a string value. Nothing is done is no 
	/// item is selected.
	///
	///////////////////////////////////////////////////////////////////////////
	std::string getSelectedValue() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the values corresponding to the selected items. 
	///
	/// A value is a representation of what is contained in the item. For 
	/// example, text items would return a string value. Nothing is done is no 
	/// item is selected.
	///
	///////////////////////////////////////////////////////////////////////////
	std::vector<std::string>  getSelectedValues() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the item located in the given position.
	///
	/// \param pos : The position to test.
	///
	 /// \return A smart pointer to item (if one was found). Otherwise, null.
	///////////////////////////////////////////////////////////////////////////
	PtrBaseListBoxItem getItemAt(const Point& pos) const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the item located in the given position.
	///
	/// \param pos : The position to test.
	///
	 /// \return A smart pointer to item (if one was found). Otherwise, null.
	///////////////////////////////////////////////////////////////////////////
	//template<class T>
	//T getItemAt(const Point& pos) const
	//{
	//	return boost::static_pointer_cast<T>(getItemAt(pos);//////////////////////////////////////////////
	//}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the item index located in the given position.
	///
	/// \param pos : The position to test.
	///
	 /// \return Item index (if one was found). Otherwise, -1.
	///////////////////////////////////////////////////////////////////////////
	int getIndexAt(const Point& pos) const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns all items.
	///
	/// \return The items.
	///////////////////////////////////////////////////////////////////////////
	const ItemList& getItemList() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds an interval for the selection. 
	///
	/// It doesen't replace the existing one.
	///
	/// \param min : First selection index.
	/// \param max : Last selection index
	///////////////////////////////////////////////////////////////////////////
	void addSelectionInterval(unsigned int minIndex, unsigned int maxIndex);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Selects a given item by index.
	///
	/// \param pos : The position to test.
	///
	 /// \return Item index (if one was found). Otherwise, -1.
	///////////////////////////////////////////////////////////////////////////
	void selectItem(unsigned int index);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Selects all given items
	///
	/// \param indices : indices to be selected.
	///////////////////////////////////////////////////////////////////////////
	void selectItems(const std::vector<unsigned int>& indices);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns whether the item index is selected.
	///
	/// \param index : index to test.
	///
	/// \return true if the item is selected, false if it not selecte.
	///////////////////////////////////////////////////////////////////////////
	bool isSelected(unsigned int index);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns vertical ScrollBar.
	///
	/// \return A smart pointer to the vertical ScrollBar.
	///////////////////////////////////////////////////////////////////////////
	PtrScrollBar getScrollBarV();

	//void setSelectionColor(const sf::Color& coul) {mySelectionColor = coul;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Defines the type of selection.
	///
	/// \param type : Type to set.
	///////////////////////////////////////////////////////////////////////////
	void setSelectionType(TypeSelection type) {mySelectionType = type;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the current type of selection.
	///
	/// \return The type of selection
	///////////////////////////////////////////////////////////////////////////
	TypeSelection getSelectionType() const {return mySelectionType;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the row height of items. Put 0 not to let the ListBox 
	/// resize the item newly added.
	///
	/// \param height : Item height. 0
	///////////////////////////////////////////////////////////////////////////
	void setFixedRowHeight(int height) {myRowHeight = height;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the row height of items.
	///
	/// \return Item height. If it is 0, the height is decided by the item itself
	///////////////////////////////////////////////////////////////////////////
	int getFixedRowHeight() const {return myRowHeight;}

	bool handleMouseWheel_impl(MouseEvent& ev);

	void configureScrollBars();

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Called when the selected item(s) changed
	///
	/// \param ev : Triggered event.
	///////////////////////////////////////////////////////////////////////////////
	void onSelectedIndexChanged(Event& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeSelectedIndexChanged(GenericFunction f)//void (Class::*function)(T), Instance instance)
	{E_onSelectedIndexChanged = f;}//bind1(function, instance);}

	const std::string PREFIX_SCROLLBARV;
	const std::string PREFIX_SCROLLBARH;
	//const std::string SUFFIX;

	///Widget type
	//static const std::string myWidgetType;

protected:
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Updates the item list.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	void updateItems();

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Adds an index to the selected index list.
	///
	/// \param index : Index to add.
	///////////////////////////////////////////////////////////////////////////////
	void addIndex(unsigned int index);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Removes an index from the selected index list.
	///
	/// \param index : index to remove.
	///
	/// \return true if the index was successfully remove, false if not.
	///////////////////////////////////////////////////////////////////////////////
	bool removeIndex(unsigned int index);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Removes all indices.
	///////////////////////////////////////////////////////////////////////////////
	void resetIndices();

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse pressed event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMousePressed_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse released event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseReleased_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse hover event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseHover_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a key pressed event.
	///
	/// \param ev: The Keyboard event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleKeyPressed_impl(KeyboardEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a keyboard event.
	///
	/// \param ev: The Keyboard event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleKeyReleased_impl(KeyboardEvent& ev);

protected:
	SelectedIndicesList mySelectedIndices;
	ItemList myItems;
	int myRowHeight;

	//int mySelectedIndex;
	bool myIsDragging;
	bool myIsControlPressed;
	bool myIsShiftPressed;

	TypeSelection mySelectionType;

	GenericFunction E_onSelectedIndexChanged;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static ListBox type.
///////////////////////////////////////////////////////////////////////////////
//GAIA_REGISTER_TYPE(ListBox)
GAIA_REGISTER_FULL_TYPE(ListBox, BaseWidget)

} //end namespace

#endif