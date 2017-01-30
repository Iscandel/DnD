#ifndef H__WIDGETSTATICTYPE_270920112138__H
#define H__WIDGETSTATICTYPE_270920112138__H

#include "Gaia/tools/Exceptions.h"

#include <list>

namespace gaia
{
namespace priv
{
	//We could also use a simple std::map<string, string> that stands for 
	//widgetType <-> parent
	class GAIA_DLL WidgetNode
	{
	public:
		WidgetNode(const std::string& name);
	
		void addParent(WidgetNode* parent);
	
		void addChild(const WidgetNode& node);

		const WidgetNode* getParent() const;

		const std::string& getName() const;

		std::list<WidgetNode>& getChildren();

		static WidgetNode& getRoot();

	protected:
		std::list<WidgetNode> myChildren;
		std::string myName;
		WidgetNode* myParent;

		//static WidgetNode myBase;
	};

	GAIA_DLL WidgetNode* findNode(const std::string& type, WidgetNode& base = WidgetNode::getRoot());

	GAIA_DLL std::string getParentType(const std::string& type);

	GAIA_DLL void addWidgetNode(const std::string& widgetType, const std::string& parentType);

} //end namespace priv

	//Should we define template<class T> struct WidgetStaticType; instead
	//and get an error during the compilation if the class hasn't been
	//registered ?
	template<class T>
	struct WidgetStaticType
	{
		static const char* get() {throw GuiException("Missing widget static type. "
			"Did you forget to register your class type ?");}
	};

	//template<class T, class U = int>
	//struct WidgetStaticType
	//{
	//	static const char* get() {throw GuiException("Missing widget static type. "
	//		"Did you forget to register your class type ?");}

	//	static const char* getParent() {return "";}
	//};
	//Parent->giveWidgetRenderer()

	//#define GAIA_REGISTER_TYPE(widgetType, ParentType) \
	//template<> \
	//struct WidgetStaticType<widgetType, ParentType> \
	//{ \
	//	static const char* get() {return #widgetType;} \
	//	T dummy;
	// std::map<string, boost<shared_ptr<T> > association;
	//
	//};
	//template<class T, class U = int>
	//struct WidgetStaticType
	//{
	//	static const char* get() {throw GuiException("Missing widget static type. "
	//		"Did you forget to register your class type ?");}

	//	static const char* getParent() {return "";}
	//};

	///////////////////////////////////////////////////////////////////////////
	/// \brief Enables to converts the widget static type into a string.
	/// 
	/// Each class inherited from BaseWidget, and intended to be instancied
	/// by a Widget factory, should be registered, by calling this macro.
	///
	/// \param widgetType : Class name to register.
	///////////////////////////////////////////////////////////////////////////
#define GAIA_REGISTER_TYPE(widgetType) \
	template<> \
	struct WidgetStaticType<widgetType> \
	{ \
		static const char* get() {return #widgetType;} \
	};

#define GAIA_REGISTER_FULL_TYPE(widgetType, parentType) \
	template<> \
	struct WidgetStaticType<widgetType> \
	{ \
		static const char* get() \
		{ \
			static bool first = true; \
			if(first) \
			{ \
				gaia::priv::addWidgetNode(#widgetType, #parentType); \
				first = false; \
			} \
			return #widgetType; \
		} \
	}; 
	
		//static const std::string& get() {return myType;} \
	//private: \
	//	static std::string myType; \
	//}; \
	//WidgetStaticType<widgetType>::myType = #widgetType;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the widget static type under a string form.
	///
	/// \return A string containing the type name of the given widget T.
	///////////////////////////////////////////////////////////////////////////
	template<class T>
	const char* getStaticType()
	{
		return WidgetStaticType<T>::get();
	}
}

#endif