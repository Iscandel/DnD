#ifndef H__TEXTBOX__H
#define H__TEXTBOX__H

//#include "Gaia/BaseWidget.h"
//#include "Gaia/IRetrait.h"
//#include "Gaia/IText.h"
//#include "Gaia/IFonte.h"
//#include "Gaia/ICaret.h"
//#include "Gaia/tools/Observer.h"

#include "Gaia/widgets/BaseTextWidget.h"
#include "Gaia/Rectangle.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Widget enabling the user to insert or delete text. A TextBox only
/// handle a single line text.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL TextBox : public BaseTextWidget//public BaseWidget, public IText, public Observable, public ICaret
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
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
	TextBox(const std::string& name = "", 
			int x = 0, 
			int y = 0, 
			int width = 0, 
			int height = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param dimensions: Rectangle defining the widget size (top left 
	/// position is relative to parent widget, or the screen if the widget is 
	/// the top level widget).
	///////////////////////////////////////////////////////////////////////////
	TextBox(const std::string& name, const IntRect& dimensions);

	///////////////////////////////////////////////////////////////////////////
	// Héritée. Donne ou retire le focus au widget
	///////////////////////////////////////////////////////////////////////////
	//virtual void setFocus(bool b);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when the widget has just lost the focus.
	///////////////////////////////////////////////////////////////////////////
	virtual void onLostFocus();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Updates the widget.
	///
	/// \param elapsedTime :elapsed time since the last call to update(). Could
	/// be the frame time.
	///////////////////////////////////////////////////////////////////////////
	virtual void update(unsigned int elapsedTime);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the TextBox's text.
	///
	/// \param text : The text to set.
	///////////////////////////////////////////////////////////////////////////
	void setText(const std::string& text);
	//const std::string& getText() const {return myText;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes text.
	///
	/// \param startingPos : Text index defining the begining of the suppression.
	/// \param endingPos : Text index defining the ending of the suppression.
	///////////////////////////////////////////////////////////////////////////
	void deleteTextRange(unsigned int startingPos, unsigned int endingPos);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes text.
	///
	/// \param startingPos : Text index defining the begining of the suppression.
	/// \param amount : Amount of characters to deletes.
	///////////////////////////////////////////////////////////////////////////
	void deleteText(unsigned int startingPos, unsigned int amount);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes a section of text, from startingPos to endingPos, and
	/// replaces it by the given string
	///
	/// \param text : Text to insert in replacement.
	/// \param startingPos : Text index defining the begining of the suppression.
	/// \param endingPos : Text index defining the ending of the suppression.
	///////////////////////////////////////////////////////////////////////////
	void replaceTextRange(const std::string& text, unsigned int startingPos, unsigned int endingPos);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes a section of text, from startingPos, and replaces it by
	/// the given string.
	///
	/// \param text : Text to insert in replacement.
	/// \param startingPos : Text index defining the begining of the replacement.
	/// \param amount : Text index defining the ending of the replacement.
	///////////////////////////////////////////////////////////////////////////
	void replaceText(const std::string& text, unsigned int startingPos, unsigned int amount);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Inserts the given string at the given position. Position must be 
	/// a valid one.
	///
	/// \param text : Text to insert.
	/// \param pos : Position of insertion.
	///////////////////////////////////////////////////////////////////////////
	void insertText(const std::string& text, unsigned int pos);

	//@override
	//virtual void setWidgetRenderer(IWidgetRenderer* mr);
	//const sf::Color& getTextColor2() {return MaChaineAffichage.GetColor();}

	//const Color& getTextColor() {return maFonte->getCouleur();}
	
	//void setTextColor(const Color& c) {maFonte->setColor(c);}
	//void setTextColor(const sf::Color& c) {MaChaineAffichage.SetColor(c);}

	//void setFontSize(float f) {maFonte->setFontSize(f);}//MaChaineAffichage.SetSize(f);}
	//void setFont2(const sf::Font& f) {MaChaineAffichage.SetFont(f);}

	//void setFont(IFonte* fonte) {maFonte = fonte;}
	//IFonte* getFont() {return maFonte;}

	//int getCaretPosition() const {return myCaret;}

	////@override
	//void setCaretPosition(unsigned int pos);
	//void setFontSize(float taille) {maFonte->setFontSize(taille);}

	//@override
	//virtual void setGraphics(BaseGraphics* Gfx);

	void assignToModel(Observer* rendu);

	//int getSelectionStart() const {return std::min(myFirstSelection, myLastSelection);} //monDebutSelection -> monSelectionPremier

	//int getSelectionEnd() const {return std::max(myFirstSelection, myLastSelection);}

	//void setSelectionStart(int pos)
	//{
	//	if(pos >= 0 && pos <= getSelectionEnd()) 
	//	{
	//		if(myFirstSelection == getSelectionStart())
	//			myFirstSelection = pos;
	//		else
	//			myLastSelection = pos;
	//	}
	//}

	//void setSelectionEnd(int pos)
	//{
	//	if(pos >= 0 && pos >= getSelectionStart()) 
	//	{
	//		if(myFirstSelection == getSelectionEnd())
	//			myFirstSelection = pos;
	//		else
	//			myLastSelection = pos;
	//	}
	//}

	//void onTextChanged();

	std::string getSelectedText() {return myText.substr(getSelectionStart(), getSelectionEnd() - getSelectionStart());}

	//Nom du type de widget
	//static const std::string myWidgetType;
	
protected:
	/////////////////////////////////////////////////////////////////////////////////
	////A faire redéfinir par les widgets enfants.
	////Traite de façon générique la réponse à un évènement de souris pressée
	/////////////////////////////////////////////////////////////////////////////////
	//virtual bool handleMousePressed_impl(MouseEvent& ev);

	/////////////////////////////////////////////////////////////////////////////////
	////A faire redéfinir par les widgets enfants.
	////Traite de façon générique la réponse à un évènement de souris relachee
	/////////////////////////////////////////////////////////////////////////////////
	//virtual bool handleMouseReleased_impl(MouseEvent& ev);

	/////////////////////////////////////////////////////////////////////////////////
	////A faire redéfinir par les widgets enfants.
	////Traite de façon générique la réponse à un évènement de souris en déplacement
	/////////////////////////////////////////////////////////////////////////////////
	//virtual bool handleMouseHover_impl(MouseEvent& ev);

	/////////////////////////////////////////////////////////////////////////////////
	////A faire redéfinir par les widgets enfants.
	////Traite de façon générique la réponse à un évènement de touche pressée
	/////////////////////////////////////////////////////////////////////////////////
	//virtual bool handleKeyPressed_impl(KeyboardEvent& ev);

	/////////////////////////////////////////////////////////////////////////////////
	////A faire redéfinir par les widgets enfants.
	////Traite de façon générique la réponse à un évènement de texte entré
	/////////////////////////////////////////////////////////////////////////////////
	//virtual bool handleTextEntered_impl(KeyboardEvent& ev);

	//void handleDeleting();

	//void resetSelection();

	//void moveSelection(int quantite);

	//template<class T, class Class, class Instance>
	//void subscribeTextChanged(void (Class::*fonction)(T), Instance instance)
	//{E_onTextChanged = bind1(fonction, instance);}

protected:
	//unsigned int monPremierCaractereVisible;
	////int myCaret;
	//std::string myText;

	//GenericFunction E_onTextChanged;

	//bool myIsDragging;
	//int myFirstSelection;
	//int myLastSelection;

	//Point myMousePos;

	//PtrFont maFonte;
};


///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static TextBox type.
///////////////////////////////////////////////////////////////////////////////
GAIA_REGISTER_TYPE(TextBox)


//class TextBox : public BaseWidget, public IText, public Observable, public IRetrait
//{
//public:
//	///////////////////////////////////////////////////////////////////////////
//	// Constructeur 1
//	// Params : nom		-> Le nom du widget
//	//			x		-> La position x
//	//			y		-> La position y
//	//			largeur -> La largeur du widget
//	//			hauteur -> La hauteur du widget
//	///////////////////////////////////////////////////////////////////////////
//	TextBox(const std::string& nom = "", int x = 0, int y = 0, int largeur = 0, int hauteur = 0);
//
//	///////////////////////////////////////////////////////////////////////////
//	// Constructeur 2
//	// Params : nom		   -> Le nom du widget
//	//			dimensions -> Rectangle définissant les dimensions du widget
//	///////////////////////////////////////////////////////////////////////////
//	TextBox(const std::string& nom, const IntRect& dimensions);
//
//	///////////////////////////////////////////////////////////////////////////
//	// Destructeur
//	///////////////////////////////////////////////////////////////////////////
//	virtual ~TextBox(void);
//
//	///////////////////////////////////////////////////////////////////////////
//	// Héritée. Traite l'évènement
//	///////////////////////////////////////////////////////////////////////////
//	//virtual bool traiterEvenement(const sf::Event& ev, const Point& posSouris);
//
//	///////////////////////////////////////////////////////////////////////////
//	// Héritée. Affiche le widget et ses enfants
//	///////////////////////////////////////////////////////////////////////////
//	//virtual void dessiner(sf::RenderWindow& Fenetre, int x, int y);
//
//	///////////////////////////////////////////////////////////////////////////
//	// Héritée. Donne ou retire le focus au widget
//	///////////////////////////////////////////////////////////////////////////
//	virtual void setFocus(bool b);
//
//	///////////////////////////////////////////////////////////////////////////
//	// Héritée. Met à jour
//	///////////////////////////////////////////////////////////////////////////
//	virtual void update(unsigned int elapsedTime);
//
//	void setText(const std::string& texte);
//	const std::string& getText() const {return myText;}
//	//const sf::Color& getTextColor2() {return MaChaineAffichage.GetColor();}
//
//	//const Color& getTextColor() {return maFonte->getCouleur();}
//
//
//	///////////////////////////////////////////////////////////////////////////
//	// Héritée. Renvoie la couleur de fond de la textbox
//	///////////////////////////////////////////////////////////////////////////
//	const sf::Color& getCouleurFond() const {return myBackgroundColor;}
//	
//	void setTextColor(const Color& c) {maFonte->setColor(c);}
//	//void setTextColor(const sf::Color& c) {MaChaineAffichage.SetColor(c);}
//
//	//void setFontSize(float f) {maFonte->setFontSize(f);}//MaChaineAffichage.SetSize(f);}
//	void setFont2(const sf::Font& f) {MaChaineAffichage.SetFont(f);}
//
//	//void setFont(IFonte* fonte) {maFonte = fonte;}
//	//IFonte* getFont() {return maFonte;}
//
//	int getCaretPosition() const {return maPosBarreVerticale;}
//	void setCaretPosition(unsigned int pos);
//	//void setFontSize(float taille) {maFonte->setFontSize(taille);}
//
//	//@override
//	virtual void setGraphics(BaseGraphics* Gfx);
//
//	void assignToModel(TextboxRendu* rendu);
//
//	int getSelectionStart() const {return std::min(myFirstSelection, myLastSelection);} //monDebutSelection -> monSelectionPremier
//
//	int getSelectionEnd() const {return std::max(myFirstSelection, myLastSelection);}
//
//	void setSelectionStart(int pos)
//	{
//		if(pos >= 0 && pos <= getSelectionEnd()) 
//		{
//			if(myFirstSelection == getSelectionStart())
//				myFirstSelection = pos;
//			else
//				myLastSelection = pos;
//		}
//	}
//
//	void setSelectionEnd(int pos)
//	{
//		if(pos >= 0 && pos >= getSelectionStart()) 
//		{
//			if(myFirstSelection == getSelectionEnd())
//				myFirstSelection = pos;
//			else
//				myLastSelection = pos;
//		}
//	}
//
//
//	std::string getSelectedText() {return myText.substr(getSelectionStart(), getSelectionEnd() - getSelectionStart());}
//
//	//Nom du type de widget
//	static const std::string myWidgetType;
//	
//protected:
//	///////////////////////////////////////////////////////////////////////////////
//	//A faire redéfinir par les widgets enfants.
//	//Traite de façon générique la réponse à un évènement de souris pressée
//	///////////////////////////////////////////////////////////////////////////////
//	virtual bool handleMousePressed_impl(MouseEvent& ev);
//
//	///////////////////////////////////////////////////////////////////////////////
//	//A faire redéfinir par les widgets enfants.
//	//Traite de façon générique la réponse à un évènement de souris relachee
//	///////////////////////////////////////////////////////////////////////////////
//	virtual bool handleMouseReleased_impl(MouseEvent& ev);
//
//	///////////////////////////////////////////////////////////////////////////////
//	//A faire redéfinir par les widgets enfants.
//	//Traite de façon générique la réponse à un évènement de souris en déplacement
//	///////////////////////////////////////////////////////////////////////////////
//	virtual bool handleMouseHover_impl(MouseEvent& ev);
//
//	///////////////////////////////////////////////////////////////////////////////
//	//A faire redéfinir par les widgets enfants.
//	//Traite de façon générique la réponse à un évènement de touche pressée
//	///////////////////////////////////////////////////////////////////////////////
//	virtual bool handleKeyPressed_impl(KeyboardEvent& ev);
//
//	///////////////////////////////////////////////////////////////////////////////
//	//A faire redéfinir par les widgets enfants.
//	//Traite de façon générique la réponse à un évènement de texte entré
//	///////////////////////////////////////////////////////////////////////////////
//	virtual bool handleTextEntered_impl(KeyboardEvent& ev);
//
//	///////////////////////////////////////////////////////////////////////////
//	// Calcule la partie visible du texte dans la textbox
//	///////////////////////////////////////////////////////////////////////////
//	void mettreAJourTexte();
//
//	void resetSelection();
//
//	void moveSelection(int quantite);
//
//protected:
//	unsigned int monPremierCaractereVisible;
//	bool monDessinerCurseur;
//	int maPosBarreVerticale;
//	std::string myText;
//
//	bool myIsDragging;
//	int myFirstSelection;
//	int myLastSelection;
//
//	Point myMousePos;
//
//	//PtrFont maFonte;
//
//};

}; //Fin namespace

#endif