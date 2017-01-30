#ifndef H__FOCUSWIDGETMANAGER_010920110254__H
#define H__FOCUSWIDGETMANAGER_010920110254__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include <deque>

#include "Gaia/Config.h"
#include "Gaia/widgets/BaseWidget.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Focus manager.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL FocusWidgetManager
{
public:
	void setWidgetCatchInputs(PtrWidget w);

	PtrWidget getWidgetCaughtInput();

	PtrWidget getWidgetModal();

	void addModalWidget(PtrWidget w);

	void releaseModalWidget(PtrWidget w);

	void update();

	void clean();

protected:
	typedef boost::weak_ptr<BaseWidget> WeakPtrWidget;

	//PtrWidget monWidgetCaptureEntrees;
	WeakPtrWidget myWidgetCaughtInputs;

	std::deque<PtrWidget> mesWidgetsModaux;
	std::deque<WeakPtrWidget> myModalWidgets;

};

}//end namespace

#endif