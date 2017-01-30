#ifndef H__LAYOUTINFOS_201020112236_H
#define H__LAYOUTINFOS_201020112236_H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>

#include "Gaia/tools/NonCopyable.h"
#include "Gaia/tools/Tools.h"
#include "Gaia/Rectangle.h"
#include "Gaia/Point.h"

#include <boost/smart_ptr.hpp>

namespace gaia
{
class BaseWidget;

//////////////////////////////////////////////////////////////////////////////
/// \brief Class managing layout informations about widget.
//////////////////////////////////////////////////////////////////////////////
struct GAIA_DLL LayoutInfos
{
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///////////////////////////////////////////////////////////////////////////
	LayoutInfos();

	///////////////////////////////////////////////////////////////////////////
	/// Defines the type of layout used to place the widget.
	///
	/// FIXED : The widget has fixed coordinates.
	///
	/// RELATIVE : The widget has relative coordinates related to its parent
	///			   (0 to 1).
	///
	/// UNIFORM : Complex layout. Can use scripted formulas.
	///////////////////////////////////////////////////////////////////////////
	enum PositionType
	{
		FIXED,
		RELATIVE,
		UNIFORM
	};

	//enum Anchor
	//{
	//	LEFT,
	//	TOP,
	//	RIGHT,
	//	BOTTOM
	//};

	//////////////////////////////////////////////////////////////////////////////
	/// \brief Internal class for internal use. Stores layout informations.
	//////////////////////////////////////////////////////////////////////////////
	struct Infos
	{
		Infos()
		:myIsScreenDependent(false)
		,myPositionType(FIXED)
		{
		}

		PositionType myPositionType; ///< Type of layout
		//Anchor myAnchor;
		bool myIsScreenDependent; ///< Resize with any resolution changes ?
		std::string myRawPos; ///< Position or size stored under a string form
	};

	////template<class T>
	//void setPosInfos(PositionType type, const T& value)
	//{
	//	myPosition.myPositionType = type;
	//	
	//	myPosition.myRawPos
	//}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Set position informations.
	/// 
	/// \param type : Type of layout.
	/// \param value : Position under a string form.
	/// \param screenDependent : Position changes according to a screen resolution change.
	/// \see void setPosInfos(const Point& value, bool screenDependent = false);
	/// \see void setPosInfos(const std::pair<double, double>& value);
	/// \see void setPosInfos(const std::string& value, bool screenDependent = false);
	///////////////////////////////////////////////////////////////////////////
	void setPosInfos(PositionType type, const std::string& value, bool screenDependent = false);
	//template<>
	void setPosInfos(const Point& value, bool screenDependent = false);
	void setPosInfos(const std::pair<double, double>& value);
	void setPosInfos(const std::string& value, bool screenDependent = false);
	void setWidthInfos(PositionType type, const std::string& value, bool screenDependent = false);
	void setWidthInfos(int value,bool screenDependent = false);
	void setWidthInfos(double value);
	void setWidthInfos(const std::string& value, bool screenDependent = false);
	void setHeightInfos(PositionType type, const std::string& value, bool screenDependent = false);
	void setHeightInfos(int value, bool screenDependent = false);
	void setHeightInfos(double value);
	void setHeightInfos(const std::string& value, bool screenDependent = false);

	IntRect getComputedDimensions(BaseWidget* widget);

	std::pair<double, double> parsePos(BaseWidget* widget);

	double parseWidth(BaseWidget* widget);

	double parseHeight(BaseWidget* widget);

	void setLayoutTypeIsArea(bool isArea) {myIsArea = isArea;}

protected:
	std::pair<double, double> getAndCheckValues(const std::string& string);

	std::pair<double, double> parsePosLayout(BaseWidget* widget, const std::string& string, const Infos& infos);

	double parseLayout(BaseWidget* widget, const std::string& string, const Infos& infos);

	double convertToken(BaseWidget* widget, const std::string& token, const Infos& infos);

	double computeResult(double v1, double v2, const std::string& op);

	//double getValueFromFunction(const std::string& token, BaseWidget* widget);

	BaseWidget* extractTarget(BaseWidget* widget, const std::string& token);

protected:
	Infos myPosition;
	Infos myWidthType;
	Infos myHeightType;

	bool myPositionIsUpdated;
	bool myWidthIsUpdated;
	bool myHeightIsUpdated;

	std::pair<double, double> myCachePos;
	double myCacheWidth;
	double myCacheHeight;

	bool myIsArea;
};

typedef boost::shared_ptr<LayoutInfos> PtrLayoutInfos;


class GAIA_DLL RawParser : public NonCopyable
{
public:
	enum TokenValue {
		NUMBER,		
		PLUS='+',	MINUS='-',	MUL='*',	DIV='/',
		PRINT=';',	ASSIGN='=',	LP='(',		RP=')',  END
	};
public:
	RawParser(BaseWidget* widget, const std::string& string, const gaia::LayoutInfos::Infos& infos);

	double eval();

	double convertToken(BaseWidget* widget, const std::string& token, const LayoutInfos::Infos& infos);

	//=============================================================================
	///////////////////////////////////////////////////////////////////////////////
	BaseWidget* extractTarget(BaseWidget* widget, const std::string& token);

	TokenValue get_token();

	double prim(bool get);		// handle primaries

	double term(bool get);		// multiply and divide

	double expr(bool get);		// add and subtract

public:
	TokenValue myCurrentToken;// = PRINT;
	double number_value;
	std::string string_value;
	const std::string& myString;
	std::vector<std::string> myTokens;
	int myCurrentTokenIndex;
	BaseWidget* myWidget;
	const gaia::LayoutInfos::Infos& myInfos;
};

} //end namespace

#endif