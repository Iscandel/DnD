#ifndef H__NUMERICTEXTBOX_240920111727__H
#define H__NUMERICTEXTBOX_240920111727__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Config.h"
#include "Gaia/widgets/TextBox.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Specialization of the TextBox class to handle only numeric values.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL NumericTextBox : public TextBox
{
public:
	///Type of numbers
	enum TypeNumber
	{
		INTEGER, ///< Integer values
		DECIMAL  ///< Decimal values
	};

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
	NumericTextBox(const std::string& name = "", 
				   int x = 0, 
				   int y = 0, 
				   int width = 0, 
				   int height = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param dimensions: Rectangle defining the widget size (top left 
	/// position is relative to parent widget, or the screen if the widget is 
	/// the top level widget).
	///////////////////////////////////////////////////////////////////////////
	NumericTextBox(const std::string& name, const IntRect& dimensions);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Converts the TextBox string to a numeric value, and returns true
	/// if the conversion was succesful (false if it failed).
	///
	/// \param value : TextBox's value to get.
	///
	/// \return true if the conversion succeded, false if it failed.
	///////////////////////////////////////////////////////////////////////////
	bool getValue(double& value);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Defines the type of number handled by the numeric TextBox.
	///
	/// \param type : Type of number to set.
	///////////////////////////////////////////////////////////////////////////
	void setTypeONumber(TypeNumber m) {myTypeNumber = m;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the type of number handled by the widget.�
	///////////////////////////////////////////////////////////////////////////
	TypeNumber getTypeNumber() const {return myTypeNumber;}

	///Widget type
	//static const std::string myWidgetType;

protected:
	///////////////////////////////////////////////////////////////////////////////
	//A faire red�finir par les widgets enfants.
	//Traite de fa�on g�n�rique la r�ponse � un �v�nement de texte entr�
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleTextEntered_impl(KeyboardEvent& ev);

protected:
	///////////////////////////////////////////////////////////////////////////
	// Renvoie true si le caract�re pass� en param�tre est num�rique, false
	// sinon
	///////////////////////////////////////////////////////////////////////////
	bool isNumeric(int caractere);

	TypeNumber myTypeNumber;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static NumericTextBox type.
///////////////////////////////////////////////////////////////////////////////
GAIA_REGISTER_TYPE(NumericTextBox)

} //end namespace

#endif
