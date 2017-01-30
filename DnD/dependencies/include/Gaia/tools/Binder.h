#ifndef H__BINDER_040920111725__H
#define H__BINDER_040920111725__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include <boost/function.hpp>
#include <boost/function_equal.hpp>
#include <boost/bind.hpp>


///////////////////////////////////////////////////////////////////////////////
/// Fonctions providing an easier interface to bind the member function 
/// pointers to the widgets.
///////////////////////////////////////////////////////////////////////////////
namespace gaia
{
	///1 argument functions
	template<class T, class Class, class Instance>
	inline boost::function1<void, T> bind1(void (Class::*myFunction)(T), Instance myInstance)
	{
		return boost::bind(myFunction, myInstance, _1);
	}

	/////1 argument functions
	//template<class T, class Class>
	//inline boost::function1<void, T> bind1(void (Class::*myFunction)(T), Instance myInstance)
	//{
	//	return boost::bind(myFunction, myInstance, _1);
	//}

	///2 arguments functions
	template<class T1, class T2, class Class, class Instance>
	inline boost::function2<void, T1, T2> bind2(void (Class::*myFunction)(T1, T2), Instance myInstance)
	{
		return boost::bind(myFunction, myInstance, _1, _2);
	}

	///3 arguments functions
	template<class T1, class T2, class T3, class Class, class Instance>
	inline boost::function3<void, T1, T2, T3> bind3(void (Class::*myFunction)(T1, T2, T3), Instance myInstance)
	{
		return boost::bind(myFunction, myInstance, _1, _2, _3);
	}

	///4 arguments functions
	template<class T1, class T2, class T3, class T4, class Class, class Instance>
	inline boost::function4<void, T1, T2, T3, T4> bind4(void (Class::*myFunction)(T1, T2, T3, T4), Instance myInstance)
	{
		return boost::bind(myFunction, myInstance, _1, _2, _3, _4);
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Utility class providing an interface for function binding.
	///
	/// It encapsulates a boost::function.
	///////////////////////////////////////////////////////////////////////////
	template<class T>
	class FunctionHandler
	{
	public:
		FunctionHandler()
		{
		}

		template<class Class, class Instance>
		explicit FunctionHandler(void (Class::*function)(T), Instance instance)
		{
			myFunction = boost::bind(function, instance, _1);
		}

		explicit FunctionHandler(void (*function)(T))
		{
			myFunction = boost::bind(function,_1);
		}

		bool isDefined() const 
		{
			return !myFunction.empty();
		}

		void operator() (T ev)//(T ev)
		{
			myFunction(ev);
		}

		//void operator() (const T ev)
		//{
		//	myFunction(ev);
		//}

		operator bool () const { return isDefined(); }

	protected:
		boost::function1<void, T> myFunction;
	};

	////Specialization for references
	//template<class T>
	//class FunctionHandler<T&>
	//{
	//public:
	//	FunctionHandler()
	//	{
	//	}

	//	template<class Class, class Instance>
	//	FunctionHandler(void (Class::*function)(T&), Instance instance)
	//	{
	//		myFunction = boost::bind(function, instance, _1);
	//	}

	//	FunctionHandler(void (*function)(T&))
	//	{
	//		myFunction = boost::bind(function,_1);
	//	}

	//	bool isDefined() const 
	//	{
	//		return myFunction != NULL;
	//	}

	//	void operator() (T& ev)//(T ev)
	//	{
	//		myFunction(ev);
	//	}

	//	//void operator() (const T ev)
	//	//{
	//	//	myFunction(ev);
	//	//}

	//	operator bool () const { return !this->isDefined(); }

	//protected:
	//	boost::function1<void, T&> myFunction;
	//};

	template<class T, class Class, class Instance>
	FunctionHandler<T> my_bind(void (Class::*function)(T), Instance instance)
	{
		return FunctionHandler<T>(function, instance);
	}

	template<class T>
	FunctionHandler<T> my_bind(void (*function)(T))
	{
		return FunctionHandler<T>(function);
	}

} //end namespace

#endif