#ifndef H__PROPRIETERENDUTEXTBOX__H
#define H__PROPRIETERENDUTEXTBOX__H

#include "Gaia/Property.h"

namespace gaia
{
namespace properties
{
class GAIA_DLL ProprietesRenduTextBox : public Property
{
public:
	ProprietesRenduTextBox(const std::string& nom);

	virtual std::string getProperty(const std::string& nom);

	virtual void setProperty(BaseWidget& Cible, const std::string& valeur); 

protected:
	std::string myTextDisplayed;
};

};
};

#endif