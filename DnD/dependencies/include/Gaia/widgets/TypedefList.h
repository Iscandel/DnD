#ifndef H__TYPEDEFLIST_240920111726__H
#define H__TYPEDEFLIST_240920111726__H

#include <boost/smart_ptr.hpp>

namespace gaia
{
class BaseListBoxItem;
class BaseWidget;
class Button;
class CheckBox;
class ComboBox;
class ComboListBox;
class DefaultContainer;
class Label;
class LinkedLabels;
class ListBox;
class ImageBox;
class NumericTextBox;
class ProgressBar;
class RadioButton;
class ScrollBar;
class Slider;
class TextBox;
class TextField;
class TextListBoxItem;
class Window;
class TitleBar;

typedef boost::shared_ptr<BaseListBoxItem> PtrBaseListBoxItem;
typedef boost::shared_ptr<BaseWidget> PtrWidget;
typedef boost::shared_ptr<Button> PtrButton;
typedef boost::shared_ptr<CheckBox> PtrCheckBox;
typedef boost::shared_ptr<ComboBox> PtrComboBox;
typedef boost::shared_ptr<ComboListBox> PtrComboListBox;
typedef boost::shared_ptr<DefaultContainer> PtrDefaultContainer;
typedef boost::shared_ptr<ImageBox> PtrImageBox;
typedef boost::shared_ptr<Label> PtrLabel;
typedef boost::shared_ptr<ListBox> PtrListBox;
typedef boost::shared_ptr<LinkedLabels> PtrLinkedLabels;
typedef boost::shared_ptr<NumericTextBox> PtrNumericTextBox;
typedef boost::shared_ptr<ProgressBar> PtrProgressBar;
typedef boost::shared_ptr<RadioButton> PtrRadioButton;
typedef boost::shared_ptr<ScrollBar> PtrScrollBar;
typedef boost::shared_ptr<Slider> PtrSlider;
typedef boost::shared_ptr<TextBox> PtrTextBox;
typedef boost::shared_ptr<TextField> PtrTextField;
typedef boost::shared_ptr<TextListBoxItem> PtrTextListBoxItem;
typedef boost::shared_ptr<Window> PtrWindow;
typedef boost::shared_ptr<TitleBar> PtrTitleBar;

}
#endif