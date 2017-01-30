#ifndef H__NONCOPYABLE_300120170039__H
#define H__NONCOPYABLE_300120170039__H

///////////////////////////////////////////////////////////////////////////////
/// \brief Utility class thats prevents any derived class to be copyable
///////////////////////////////////////////////////////////////////////////////
class NonCopyable
{
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable&);
	const NonCopyable& operator = (const NonCopyable&);
};

#endif